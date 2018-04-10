// Copyright (c) 2018. All rights reserved.
// Author: Andy Yao <andyzyao@vip.qq.com>

#pragma once

#include <string>

struct ParsedUrl {
  std::string scheme;
  std::string host;
  unsigned short port = 0;
  std::string user;
  std::string pass;
  //std::string path;
  std::string bucket;
  std::string key;
  std::string query; 
  std::string fragment; 
};

bool ParseUrl(const std::string& url, ParsedUrl* parsed_url);
