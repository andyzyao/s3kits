// Copyright (c) 2018. All rights reserved.

#include "auth.h"
#include <cassert>
#include <openssl/hmac.h>
#include "base64.h"

namespace s3kits {

std::string CreateSignature(
        const std::string& access_key_id,     // AKIAIVYMYVEWA7EGJK2A
        const std::string& secret_access_key, // 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
        const std::string& raw) {
    unsigned char md[EVP_MAX_MD_SIZE] = {0};
    unsigned int md_len = EVP_MAX_MD_SIZE;
    assert(HMAC(EVP_sha1(), secret_access_key.data(), secret_access_key.size(),
                reinterpret_cast<const unsigned char*>(raw.data()), raw.size(), md, &md_len) != NULL);
    std::string mac(reinterpret_cast<const char*>(md), static_cast<size_t>(md_len));

    return Base64Encode(mac);
}

}  // namespace s3kits
