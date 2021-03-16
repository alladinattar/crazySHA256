
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
#include <csignal>
#include <cstdlib>

#include "boost/log/attributes/named_scope.hpp"
#include "hashSearcher.hpp"
#include "iostream"
#include "third-party/PicoSHA2/picosha2.h"
#include "thread"
#include "time.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    throw std::invalid_argument("The script only takes two arguments");
  } else {
    signal(SIGINT, crazySHA::signalInterceptor);
    crazySHA hasher(std::atoi(argv[1]), argv[2]);
    hasher.startSearch();
  }
  /*while (true) {
    std::string hash_hex_str;
    std::string proimage = std::to_string(rand());
    picosha2::hash256_hex_string((*/
  /*proimage*/ /*), hash_hex_str);
if (hash_hex_str.substr(60, 4) == "0000") {
std::cout << hash_hex_str << std::endl;
BOOST_LOG_TRIVIAL(trace) <<std::endl<< "hash: " << hash_hex_str << std::endl
<< "data: " << proimage << std::endl;
}
}*/
}

/*int k = 3;
std::thread thr(func,k);
thr.join();
return 0;*/
