// Copyright 2020 Your Name <your_email>
#include "iostream"
#include "thread"
#include "goodHashes.hpp"
#include "vector"
#include "nlohmann/json.hpp"
#include "mutex"
#include"fstream"
#include "boost/log/sources/severity_logger.hpp"
#include <boost/log/trivial.hpp>
#include <iostream>
#include "../third-party/PicoSHA2/picosha2.h"
#include <string>
#include <chrono>
#include <thread>
#include <csignal>
#include <nlohmann/json.hpp>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <sstream>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

class crazySHA{
 private:
  std::string nameOfFile;
  int maxThreadNum;
  int numOfThreads;
  std::vector<nlohmann::json> goodHashes;
  std::mutex mutex;
  boost::log::sources::severity_logger<boost::log::trivial::severity_level> slg;
  std::vector<std::thread> thrArray;
 public:

  void startSearch();
  ~crazySHA();
  void writeJSON(const std::string& file_name){
    std::ofstream outputFile;
    std::ifstream inputFile;
    outputFile.open(file_name);
    inputFile.open(file_name);
    nlohmann::json outJSON;
    if(inputFile.peek() != EOF)
      inputFile >> outJSON;
    for(auto & right_hash : goodHashes) {
      outJSON["values"].push_back(right_hash);
    }
    outputFile << outJSON.dump(4);
    outputFile.close();
  };

  void signalInterceptor(int signum){
    writeJSON("logs.json");
    sleep(1);
    std::cout << "\nProgram aborted with code " << --signum << "\n";
    exit(signum);
  }

  explicit crazySHA(int numOfThreads,std::string file);
  /*void startSearchParallels();*/
  /*std::vector<goodHash> getVector();*/
};
#endif // INCLUDE_HEADER_HPP_
