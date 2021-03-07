// Copyright 2020 Your Name <your_email>
#include "iostream"
#include "thread"
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

class crazySHA{
 private:
  int maxThreadNum;
  int numOfThreads;
 public:
  explicit crazySHA(int numOfThreads);
  void startSerchParallels();
};
#endif // INCLUDE_HEADER_HPP_
