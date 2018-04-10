// Copyright (c) 2018. All rights reserved.
// Author: Andy Yao <andyzyao@vip.qq.com>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/DeleteBucketRequest.h>

static bool g_show_usage = false;
static bool g_show_debug = false;

static void ShowUsage() {
  std::cout << "Usage: s3sh [options] COMMAND [parameters]" << std::endl
            << "  -a, --access-key           Secret ID  [0555b35654ad1656d804]" << std::endl
            << "  -s, --secret-key           Secret Key [h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q==]" << std::endl
            << "  -d, --debug                Show debug information" << std::endl
            << "  -h, --help                 Show this help" << std::endl
            << "example:" << std::endl
	    << "Example: s3sh --access-key=aaa --secret-key=bbb rm http://127.0.0.1:8000/testbucket" << std::endl;
}

void DeleteBucket(const std::string bucket) {
}

int main(int argc, const char* argv[]) {
  std::string rgw_domain;
  std::string access_key = "0555b35654ad1656d804";
  std::string secret_key = "h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q==";
  std::string file;

  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
            {"access-key",          1, 0, 'a' },
            {"secret-key",          1, 0, 's' },
            {"file",                1, 0, 'f' },
            {"debug",               0, 0, 'd' },
            {"help",                0, 0, 'h' },
            {0,                     0, 0, 0   }
    };

    int c = getopt_long(argc, const_cast<char * const*>(argv), "a:s:f:?hd", long_options, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
    case 0:
      break;
    case 'a':
      access_key = optarg;
      break;
    case 's':
      secret_key = optarg;
      break;
    case 'f':
      file = optarg;
      break;
    case '?':
      // follow through
    case 'h':
      g_show_usage = true;
      break;
    case 'd':
      g_show_debug = true;
      break;
    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
    }
  }
    
  if (g_show_usage) {
    ShowUsage();
    return 0;
  }
  
  std::string command;
  std::string uri;
  if (optind < argc) {
    command = argv[optind];
  }
  if ((optind + 1) < argc) {
    uri = argv[optind + 1]	    ;
  }

  std::cout << "command " << command << " uri " << uri << std::endl;


  if (command.empty()) {
    ShowUsage();	    
    return -1;	    
  }

  // TODO

  return 0;



/*
  Aws::SDKOptions options;
  options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Debug;
  Aws::InitAPI(options);
  
  Aws::Client::ClientConfiguration config;
  config.endpointOverride = "127.0.0.1:8000";
  config.scheme = Aws::Http::Scheme::HTTP;
  config.connectTimeoutMs = 100000;
  config.requestTimeoutMs = 100000;
  Aws::S3::S3Client s3_client(Aws::Auth::AWSCredentials("0555b35654ad1656d804", "h7GhxuBLTrlhVUyxSPUKUV8r/2EI4ngqJxD7iBdBYLhwluN30JaT3Q=="), config, 
		  Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);


  Aws::S3::Model::DeleteBucketRequest bucket_request;
  bucket_request.SetBucket("testbucket");

  auto outcome = s3_client.DeleteBucket(bucket_request);

  if (outcome.IsSuccess()) {
	  std::cout << "Done!" << std::endl;
  } else {
	  std::cout << "DeleteBucket error: "
		  << outcome.GetError().GetExceptionName() << " - "
		  << outcome.GetError().GetMessage() << std::endl;
  }
  
  Aws::ShutdownAPI(options);

  return 0;	
*/
}
