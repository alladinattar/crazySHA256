
#include <cstdlib>
#include "thread"
#include "iostream"
#include "third-party/PicoSHA2/picosha2.h"
#include "time.h"
#include "header.hpp"

void func(int m){
  std::cout<<m;
}
int main(int argc, char *argv[]) {
  if (argc>2){
    throw std::invalid_argument("The script only takes one argument");
  }

  crazySHA searcher = crazySHA(std::atoi(argv[1]));
  searcher.startSerchParallels();


  /*int k = 3;
  std::thread thr(func,k);
  thr.join();
  return 0;*/
}