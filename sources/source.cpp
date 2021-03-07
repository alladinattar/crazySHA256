// Copyright 2020 Your Name <your_email>

#include <header.hpp>

#include "picosha2.h"

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
    picosha2::hash256_hex_string(std::to_string(rand()), hash_hex_str);
    if (hash_hex_str.substr(60, 4) == "0000") {
      std::cout << hash_hex_str << std::endl;
    }
  }
}

void crazySHA::startSerchParallels() {
  for (int i = 0; i < numOfThreads; ++i) {
    std::thread thr(startSearch);
    thr.join();
  }
}