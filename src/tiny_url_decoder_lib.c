//
// Created by Samuel Vishesh Paul on 01/11/24.
//

#include <tiny_url_decoder_lib.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t hex_to_dec(const uint8_t hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    }
    if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    }
    if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    }
    fprintf(stderr, "Unrecognized hex character '%c'\n", hex);
    fflush(stderr);
    return 0; // Should never reach here
}

enum url_decode_result url_decode(
    const uint8_t * const src,
    const size_t src_len,
    uint8_t **out_dst,
    size_t *out_dst_len) {
    // Allocate memory for the output buffer
    *out_dst = (uint8_t *) malloc(src_len);
    if (*out_dst == NULL) {
        return URL_DEC_E_MEM_ALLOC;
    }

    uint8_t *dst = *out_dst;
    *out_dst_len = 0;

    for (size_t i = 0; i < src_len; ++i) {
        if (src[i] == '%' && (i + 2) < src_len) {
            const uint8_t high = src[i + 1];
            const uint8_t low = src[i + 2];
            if (isxdigit(high) && isxdigit(low)) {
                *dst++ = (uint8_t) ((hex_to_dec(high) << 4) | hex_to_dec(low));
                *out_dst_len += 1;
                i += 2;
            } else {
                free(*out_dst);
                return URL_DEC_E_MEM_ALLOC;
            }
        } else if (src[i] == '+') {
            *dst++ = ' ';
            *out_dst_len += 1;
        } else {
            *dst++ = src[i];
            *out_dst_len += 1;
        }
    }

    return URL_DEC_OK;
}
