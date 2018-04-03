// Copyright (c) 2018. All rights reserved.
// Author: Andy Yao <andyzyao@vip.qq.com>

#include "gtest/gtest.h"
#include "s3_client.h"

namespace s3kits {

//DEFINE_string(rgw_domain, "10.156.16.33:8080", "rgw_domain");
//DEFINE_string(access_key, "0555b35654ad1656d804", "access key");
//DEFINE_string(secret_key, "h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q==", "secret key");

class S3ClientTest : public ::testing::Test {
public:
    //RGWClientTest() : rgw_client_("aaa", FLAGS_secret_key) {
    S3ClientTest() : s3_client_("0555b35654ad1656d804", "h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q==") {
    }

    ~S3ClientTest() {
    }

    void SetUp() {
    }

    void TearDown() {
    }

protected:
    S3Client s3_client_;
};

TEST_F(S3ClientTest, GetService) {
    std::vector<S3Client::BucketInfo> buckets;
    EXPECT_EQ(0, s3_client_.GetService("http://127.0.0.1:8000/", &buckets));
    for (std::size_t i = 0; i < buckets.size(); ++i) {
        std::cout << "uid " << buckets[i].uid << std::endl;	    
        std::cout << "display_name " << buckets[i].display_name << std::endl;	    
        std::cout << "name " << buckets[i].name << std::endl;	    
        std::cout << "creation_date " << buckets[i].creation_date << std::endl;	    
	    /*
        LOG(INFO) << "uid " << buckets[i].uid;
        LOG(INFO) << "display_name " << buckets[i].display_name;
        LOG(INFO) << "name " << buckets[i].name;
        LOG(INFO) << "creation_date " << buckets[i].creation_date;
	*/
    }
}

} // namespace s3kits
