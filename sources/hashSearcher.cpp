// Copyright 2020 Your Name <your_email>

#include "hashSearcher.hpp"

#include <boost/log/attributes/timer.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <cstdlib>
#include <hashSearcher.hpp>

#include "boost/log/attributes/named_scope.hpp"
#include "boost/thread.hpp"
#include "boost/thread/thread.hpp"
#include "chrono"
#include "iostream"
#include "picosha2.h"
#include "time.h"
crazySHA::crazySHA(int num) {
  maxThreadNum = std::thread::hardware_concurrency();
  numOfThreads = num;
  if (numOfThreads > maxThreadNum) {
    throw std::invalid_argument("Only " + std::to_string(maxThreadNum) +
                                " streams available");
  }
}

void startSearch() {
  srand(static_cast<unsigned int>(time(0)));
  while (true) {
    std::string hash_hex_str;
    std::string proimage = std::to_string(rand());
    picosha2::hash256_hex_string((proimage), hash_hex_str);
    if (hash_hex_str.substr(60, 4) == "0000") {
      BOOST_LOG_TRIVIAL(info)
          << std::endl
          << "hash: " << hash_hex_str << std::endl
          << "data: " << proimage << std::endl
          << "thread id: " << std::this_thread::get_id() << std::endl;
      std::this_thread::sleep_for(std::chrono::microseconds(1));
    } else {
      BOOST_LOG_TRIVIAL(trace)
          << std::endl
          << "hash: " << hash_hex_str << std::endl
          << "data: " << proimage << std::endl
          << "thread id: " << std::this_thread::get_id() << std::endl;
      std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
  }
}

void crazySHA::startSearchParallels() {
  std::thread *thrArray = new std::thread[numOfThreads];
  for (int i = 0; i < numOfThreads; ++i) {
    thrArray[i] = std::thread(startSearch);
  }
  for (int i = 0; i < numOfThreads; ++i) {
    thrArray[i].join();
  }
  delete[] thrArray;
}