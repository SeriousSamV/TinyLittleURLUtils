//
// Created by Samuel Vishesh Paul on 01/11/24.
//

#include <tiny_url_encoder.h>

#include <ctype.h>
#include <stdlib.h>

enum url_encode_result url_encode(
    const uint8_t *const src,
    const size_t src_len,
    uint8_t **out_dst,
    size_t *out_dst_len) {
    static const char *hex_chars = "0123456789ABCDEF";
    size_t output_length = 0;

    for (size_t i = 0; i < src_len; ++i) {
        if (isalnum(src[i]) || src[i] == '-' || src[i] == '_' || src[i] == '.' || src[i] == '~') {
            ++output_length;
        } else {
            output_length += 3;
        }
    }

    *out_dst = (uint8_t *) malloc(output_length + 1);
    if (*out_dst == NULL) {
        return URL_ENC_E_MEM_ALLOC;
    }

    uint8_t *dst_ptr = *out_dst;
    for (size_t i = 0; i < src_len; ++i) {
        if (isalnum(src[i]) || src[i] == '-' || src[i] == '_' || src[i] == '.' || src[i] == '~') {
            *dst_ptr++ = src[i];
        } else {
            *dst_ptr++ = '%';
            *dst_ptr++ = hex_chars[(src[i] >> 4) & 0xF];
            *dst_ptr++ = hex_chars[src[i] & 0xF];
        }
    }
    *dst_ptr = '\0';

    *out_dst_len = output_length;
    return URL_ENC_OK;
}
