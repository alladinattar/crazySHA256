// Copyright 2020 Your Name <your_email>
#include <unistd.h>

#include <boost/log/attributes/named_scope.hpp>
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
#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../third-party/PicoSHA2/picosha2.h"
#include "boost/log/sources/severity_logger.hpp"
#include "fstream"
#include "goodHashes.hpp"
#include "iostream"
#include "mutex"
#include "nlohmann/json.hpp"
#include "thread"
#include "vector"
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

class crazySHA {
 private:
  static std::string nameOfFile;
  int maxThreadNum;
  int numOfThreads;
  static std::vector<nlohmann::json> goodHashes;
  std::mutex mutex;
  boost::log::sources::severity_logger<boost::log::trivial::severity_level> slg;
  std::vector<std::thread> thrArray;

 public:
  void startSearch();
  ~crazySHA();
  static void writeJSON() {
    std::ofstream outputFile;
    std::ifstream inputFile;
    outputFile.open(nameOfFile);
    inputFile.open(nameOfFile);
    nlohmann::json outJSON;
    if (inputFile.peek() != EOF) inputFile >> outJSON;
    for (auto& goodHash : goodHashes) {
      outJSON["values"].push_back(goodHash);
    }
    outputFile << outJSON.dump(4);
    outputFile.close();
  };

  static void signalInterceptor(int signum) {
    writeJSON();
    sleep(1);
    std::cout << "\nProgram aborted with code " << --signum << "\n";
    exit(signum);
  }

  explicit crazySHA(int numOfThreads, std::string file);
  /*void startSearchParallels();*/
  /*std::vector<goodHash> getVector();*/
};
#endif  // INCLUDE_HEADER_HPP_
