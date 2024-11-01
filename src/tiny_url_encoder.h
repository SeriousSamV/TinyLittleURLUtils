//
// Created by Samuel Vishesh Paul on 01/11/24.
//

#ifndef TINY_URL_ENCODER_H
#define TINY_URL_ENCODER_H
#include <stdint.h>
#include <sys/_types/_size_t.h>

enum url_encode_result {
    URL_ENC_OK,
    URL_ENC_E_MEM_ALLOC,
};

enum url_encode_result url_encode(const uint8_t *const src, const size_t src_len, uint8_t **out_dst, size_t *out_dst_len);

#endif //TINY_URL_ENCODER_H
