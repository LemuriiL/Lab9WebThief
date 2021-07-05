// Copyright 2021 LemuriiL <LemuriiL@yandex.ru>
#ifndef PAVUK_CRAWLER_H
#define PAVUK_CRAWLER_H
#include <gumbo.h>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "../third-party/ThreadPool/ThreadPool.h"
#include "../third-party/beast/root_certificates.hpp"

using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;     // from <boost/asio/ssl.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>
namespace po = boost::program_options;

using string = std::string;
using std::cout;

struct Html {
  string protocol{};
  string host{};
  string html{};
};

class Crawl {
 public:
  Crawl(int depth_, string path)
      : depth(depth_), path_out_file(std::move(path)){};
  ~Crawl();

  void start(const string& url, const int& num_loaders, const int& num_parsers);

  void print_img_to_file(const string& file_path);

 private:
  int depth;
  string path_out_file;
  std::vector<string> all_img;
  std::deque<std::pair<std::deque<string>, std::deque<Html>>> all_levels;
};
#endif  // PAVUK_CRAWLER_H
