//
// Created by Samuel Vishesh Paul on 01/11/24.
//

#ifndef TINY_URL_DECODER_LIB_H
#define TINY_URL_DECODER_LIB_H
#include <stdint.h>
#include <sys/types.h>

enum url_decode_result {
    URL_DEC_OK,
    URL_DEC_E_MEM_ALLOC,
};

enum url_decode_result url_decode(
    const uint8_t *const src,
    const size_t src_len,
    uint8_t **out_dst,
    size_t *out_dst_len);

#endif //TINY_URL_DECODER_LIB_H
