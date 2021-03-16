// Copyright 2021 Mukaev Rinat <rinamuka4@gmail.com>
// INCLUDE_GOODHASHES_HPP_
class goodHash {
 private:
  std::string timestamp;
  std::string hash;
  std::string data;

 public:
  goodHash(std::string stamp, std::string h, std::string d)
      : timestamp(stamp), hash(h), data(d) {}
  friend std::ostream& operator<<(std::ostream& out, goodHash& a) {
    out << "timestamp: " << a.timestamp << std::endl
        << "data: " << a.data << std::endl
        << "hash: " << a.hash << std::endl;
    return out;
  };
};
