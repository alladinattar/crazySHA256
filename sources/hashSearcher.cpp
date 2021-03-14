// Copyright 2020 Your Name <your_email>
#include <iostream>
#include "../third-party/PicoSHA2/picosha2.h"
#include <string>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include "hashSearcher.hpp"

crazySHA::crazySHA(int num, std::string file) {
  boost::log::add_common_attributes();
  boost::log::add_console_log(std::clog, boost::log::keywords::format = "[%Severity%] %TimeStamp%: %Message%");
  maxThreadNum = std::thread::hardware_concurrency();
  numOfThreads = num;
  nameOfFile = file;
  if (numOfThreads > maxThreadNum) {
    throw std::invalid_argument("Only " + std::to_string(maxThreadNum) +
                                " streams available");
  }
  boost::log::add_file_log
      (
          boost::log::keywords::file_name = "sample_%N.log",
          boost::log::keywords::rotation_size = 10 * 1024 * 1024,
          boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
          boost::log::keywords::format = "[%Severity%][%TimeStamp%]: %Message%"
      );
  for(int i = 0; i < numOfThreads; ++i){
    thrArray.emplace_back(std::thread([&](){
      startSearch();
    }));
  }
}

void crazySHA::startSearch() {
  srand(static_cast<size_t>(time(0)));
  auto start = std::chrono::high_resolution_clock::now();
  while (true) {
    mutex.lock();
    std::string hash_hex_str;
    std::string proimage = std::to_string(rand());
    picosha2::hash256_hex_string((proimage), hash_hex_str);
    if (hash_hex_str.substr(60, 4) == "0000") {
      auto stop = std::chrono::high_resolution_clock::now();
      double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
          stop - start)
          .count();
      start = stop;
      BOOST_LOG_SEV(slg, boost::log::trivial::info) << std::endl
                               << "source: " << std::hex << std::stol(proimage) << std::dec
                               << " hash: " << hash_hex_str
                               << " duration: " << duration
                               << " thread: " << std::this_thread::get_id() << std::endl;
      nlohmann::json j = {
          {"source", proimage},
          {"hash_hex", hash_hex_str},
          {"duration", duration}
      };
      goodHashes.push_back(j);

    } else {
      BOOST_LOG_SEV(slg, boost::log::trivial::trace)
                                << "source: " << std::hex << std::stol(proimage) << std::dec
                                << " hash: " << hash_hex_str
                                << " thread: " << std::this_thread::get_id() << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    mutex.unlock();
  }
}

crazySHA::~crazySHA() {
  for( int i = 0; i < numOfThreads; ++i) {
    thrArray[i].join();
  }
}

std::vector<nlohmann::json> crazySHA::goodHashes;
std::string  crazySHA::nameOfFile = "logs.txt";
