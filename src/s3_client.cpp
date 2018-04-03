// Copyright (c) 2018. All rights reserved.
// Author: Andy Yao <andyzyao@vip.qq.com>

#include "s3_client.h"
#include <assert.h>
#include <sstream>
#include "rapidxml/rapidxml.hpp"
#include "auth.h"

namespace s3kits {

S3Client::S3Client(const std::string& access_key, const std::string& secret_key) : 
	access_key_(access_key), secret_key_(secret_key), curl_(NULL) {
  curl_ = curl_easy_init();
  assert(curl_ != NULL);
}

S3Client::~S3Client() {
  curl_easy_cleanup(curl_);
}

std::string S3Client::GetDate() {
  time_t timestamp = time(NULL);
  struct tm tm = {0};
  gmtime_r(&timestamp, &tm);
  char date[128] = {0};
  strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S %Z", &tm);
  return std::string(date);
}

void S3Client::Reset() {
  curl_easy_reset(curl_);
}

size_t S3Client::CurlWriteCallbackWrapper(char *ptr, size_t size, size_t nmemb, void *userdata) {
  (static_cast<std::string*>(userdata))->append(ptr, size * nmemb);
  return size * nmemb;
}

int32_t S3Client::GetService(const std::string& url, std::vector<BucketInfo>* buckets) {
  struct curl_slist* header = NULL;
  std::string date = GetDate();
  std::string raw =
        "GET\n"
        "\n"
        "\n" +
        date + "\n" +
        "/";
  std::string signature = "AWS " + access_key_ + ":" + CreateSignature(access_key_, secret_key_, raw);
  header = curl_slist_append(header, ("Authorization: " + signature).c_str());
  header = curl_slist_append(header, ("Date: " + date).c_str());

  Reset();

  std::string response_body;

  curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header);
  //curl_easy_setopt(curl_, CURLOPT_VERBOSE, FLAGS_debug ? 1L : 0L);
  //curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlWriteCallbackWrapper);
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response_body);
  CURLcode curl_code = curl_easy_perform(curl_);
  curl_slist_free_all(header);

  if (curl_code != CURLE_OK) {
	  /*
    DISTRIBUTION_get_service.Add(curl_code);
    LOG(ERROR) << "curl_easy_perform failed: curl_code " << curl_code 
	    << " curl_message " << curl_easy_strerror(curl_code);
	    */
    return -1;
  }

  long http_code = 0;
  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_code);
//  DISTRIBUTION_get_service.Add(http_code);
//  last_http_status_code_ = static_cast<int32_t>(http_code);

  if (http_code != 200) {
    //LOG(ERROR) << "get service failed: http_code " << http_code;
    return -1;
  }

  std::string uid;
  std::string display_name;

  rapidxml::xml_document<> doc;
  doc.parse<0>(const_cast<char*>(response_body.c_str()));
  rapidxml::xml_node<>* root = doc.first_node();

  rapidxml::xml_node<>* owner = root->first_node("Owner");
  if (owner != NULL) {
        rapidxml::xml_node<>* node = owner->first_node("ID");
        if (node != NULL) {
            uid = node->value();
        }
        node = owner->first_node("DisplayName");
        if (node != NULL) {
            display_name = node->value();
        }
  }

  rapidxml::xml_node<>* node = root->first_node("Buckets");
  if (node != NULL) {
        rapidxml::xml_node<>* bucket = node->first_node("Bucket");
        while (bucket != NULL) {
            BucketInfo bucket_info;
            if (bucket->first_node("Name") != NULL) {
                bucket_info.name = bucket->first_node("Name")->value();
            }
            if (bucket->first_node("CreationDate") != NULL) {
                bucket_info.creation_date = bucket->first_node("CreationDate")->value();
            }
            bucket_info.uid = uid;
            bucket_info.display_name = display_name;

            buckets->push_back(bucket_info);

            bucket = bucket->next_sibling("Bucket");
        }
  }

  return 0;
}

} // namespace s3kits
