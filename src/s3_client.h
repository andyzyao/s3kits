// Copyright (c) 2018. All rights reserved.
// Author: Andy Yao <andyzyao@vip.qq.com>

#ifndef S3_CLIENT_H
#define S3_CLIENT_H

#include <stdint.h>
#include <curl/curl.h>
#include <map>
#include <string>
#include <vector>

namespace s3kits {

class S3Client {
 public:
  S3Client(const std::string& access_key, const std::string& secret_key);
  ~S3Client();

  void EnableDebugging();
  void DisableDebugging();
    
  struct BucketInfo {
    std::string name;
    std::string creation_date;
    std::string uid;
    std::string display_name;
  };

  int32_t GetService(const std::string& url, std::vector<BucketInfo>* buckets);

private:
  std::string GetDate();

  void Reset();
  static size_t CurlWriteCallbackWrapper(char *ptr, size_t size, size_t nmemb, void *userdata);

  std::string access_key_;
  std::string secret_key_;
  CURL* curl_;
};

} // namespace s3kits

#endif // S3_CLIENT_H
