// Copyright (c) 2018. All rights reserved.

#pragma once

#include <string>

namespace s3kits {

// Create signature using amazon Signature Version 2.
// For more information, please refer to
// http://docs.aws.amazon.com/AmazonS3/latest/dev/RESTAuthentication.html.
std::string CreateSignature(
        const std::string& access_key_id,     // AKIAIVYMYVEWA7EGJK2A
        const std::string& secret_access_key, // 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
        const std::string& raw);

}  // namespace s3kits
