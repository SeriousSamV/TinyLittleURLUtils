#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <tiny_url_decoder_lib.h>

void test_url_decode() {
    const uint8_t src1[] = "hello%21";
    uint8_t *dst1 = nullptr;
    size_t dst1_len = 0;
    const enum url_decode_result r1 = url_decode(src1, sizeof(src1) - 1, &dst1, &dst1_len);
    assert(r1 == URL_DEC_OK);
    assert(dst1 != nullptr);
    assert(strncmp((char *) dst1, "hello!", sizeof("hello") + 1) == 0);
    assert(dst1_len == sizeof("hello!"));
    free(dst1);

    const uint8_t src2[] = "C%2B%2B";
    uint8_t *dst2 = nullptr;
    size_t dst2_len = 0;
    const enum url_decode_result r2 = url_decode(src2, sizeof(src2) - 1, &dst2, &dst2_len);
    assert(r2 == URL_DEC_OK);
    assert(dst2 != nullptr);
    assert(strncmp((char *) dst2, "C++", sizeof("C++") + 1) == 0);
    assert(dst2_len == sizeof("C++"));
    free(dst2);

    const uint8_t src3[] = "space%20here";
    uint8_t *dst3 = nullptr;
    size_t dst3_len = 0;
    const enum url_decode_result r3 = url_decode(src3, sizeof(src3) - 1, &dst3, &dst3_len);
    assert(r3 == URL_DEC_OK);
    assert(dst3 != nullptr);
    assert(strncmp((char *) dst3, "space here", sizeof("space here") + 1) == 0);
    assert(dst3_len == sizeof("space here"));
    free(dst3);

    const uint8_t src4[] = "%2Fpath%2Fto%2Ffile";
    uint8_t *dst4 = nullptr;
    size_t dst4_len = 0;
    const enum url_decode_result r4 = url_decode(src4, sizeof(src4) - 1, &dst4, &dst4_len);
    assert(r4 == URL_DEC_OK);
    assert(dst4 != nullptr);
    assert(strncmp((char *) dst4, "/path/to/file", sizeof("/path/to/file") + 1) == 0);
    assert(dst4_len == sizeof("/path/to/file"));
    free(dst4);

    const uint8_t src5[] = "%40email";
    uint8_t *dst5 = nullptr;
    size_t dst5_len = 0;
    const enum url_decode_result r5 = url_decode(src5, sizeof(src5) - 1, &dst5, &dst5_len);
    assert(r5 == URL_DEC_OK);
    assert(dst5 != nullptr);
    assert(strncmp((char *) dst5, "@email", sizeof("@email") + 1) == 0);
    assert(dst5_len == sizeof("@email"));
    free(dst5);

    const uint8_t src6[] = "number%231";
    uint8_t *dst6 = nullptr;
    size_t dst6_len = 0;
    const enum url_decode_result r6 = url_decode(src6, sizeof(src6) - 1, &dst6, &dst6_len);
    assert(r6 == URL_DEC_OK);
    assert(dst6 != nullptr);
    assert(strncmp((char *) dst6, "number#1", sizeof("number#1") + 1) == 0);
    assert(dst6_len == sizeof("number#1"));
    free(dst6);

    const uint8_t src7[] = "h%26ell%26o2";
    uint8_t *dst7 = nullptr;
    size_t dst7_len = 0;
    const enum url_decode_result r7 = url_decode(src7, sizeof(src7) - 1, &dst7, &dst7_len);
    assert(r7 == URL_DEC_OK);
    assert(dst7 != nullptr);
    assert(strncmp((char *) dst7, "h&ell&o2", sizeof("h&ell&o2") + 1) == 0);
    assert(dst7_len == sizeof("h&ell&o2"));
    free(dst7);

    const uint8_t src8[] = "%3Ctag%3E";
    uint8_t *dst8 = nullptr;
    size_t dst8_len = 0;
    const enum url_decode_result r8 = url_decode(src8, sizeof(src8) - 1, &dst8, &dst8_len);
    assert(r8 == URL_DEC_OK);
    assert(dst8 != nullptr);
    assert(strncmp((char *) dst8, "<tag>", sizeof("<tag>") + 1) == 0);
    assert(dst8_len == sizeof("<tag>"));
    free(dst8);

    const uint8_t src9[] = "%22quote%22";
    uint8_t *dst9 = nullptr;
    size_t dst9_len = 0;
    const enum url_decode_result r9 = url_decode(src9, sizeof(src9) - 1, &dst9, &dst9_len);
    assert(r9 == URL_DEC_OK);
    assert(dst9 != nullptr);
    assert(strncmp((char *) dst9, "\"quote\"", sizeof("\"quote\"") + 1) == 0);
    assert(dst9_len == sizeof("\"quote\""));
    free(dst9);

    const uint8_t src10[] = "%23hash";
    uint8_t *dst10 = nullptr;
    size_t dst10_len = 0;
    const enum url_decode_result r10 = url_decode(src10, sizeof(src10) - 1, &dst10, &dst10_len);
    assert(r10 == URL_DEC_OK);
    assert(dst10 != nullptr);
    assert(strncmp((char *) dst10, "#hash", sizeof("#hash") + 1) == 0);
    assert(dst10_len == sizeof("#hash"));
    free(dst10);

    const uint8_t src11[] = "%24dollar";
    uint8_t *dst11 = nullptr;
    size_t dst11_len = 0;
    const enum url_decode_result r11 = url_decode(src11, sizeof(src11) - 1, &dst11, &dst11_len);
    assert(r11 == URL_DEC_OK);
    assert(dst11 != nullptr);
    assert(strncmp((char *) dst11, "$dollar", sizeof("$dollar") + 1) == 0);
    assert(dst11_len == sizeof("$dollar"));
    free(dst11);

    const uint8_t src12[] = "%25percent";
    uint8_t *dst12 = nullptr;
    size_t dst12_len = 0;
    const enum url_decode_result r12 = url_decode(src12, sizeof(src12) - 1, &dst12, &dst12_len);
    assert(r12 == URL_DEC_OK);
    assert(dst12 != nullptr);
    assert(strncmp((char *) dst12, "%percent", sizeof("%percent") + 1) == 0);
    assert(dst12_len == sizeof("%percent"));
    free(dst12);

    const uint8_t src13[] = "%2Ccomma";
    uint8_t *dst13 = nullptr;
    size_t dst13_len = 0;
    const enum url_decode_result r13 = url_decode(src13, sizeof(src13) - 1, &dst13, &dst13_len);
    assert(r13 == URL_DEC_OK);
    assert(dst13 != nullptr);
    assert(strncmp((char *) dst13, ",comma", sizeof(",comma") + 1) == 0);
    assert(dst13_len == sizeof(",comma"));
    free(dst13);

    const uint8_t src14[] = "%2Eperiod";
    uint8_t *dst14 = nullptr;
    size_t dst14_len = 0;
    const enum url_decode_result r14 = url_decode(src14, sizeof(src14) - 1, &dst14, &dst14_len);
    assert(r14 == URL_DEC_OK);
    assert(dst14 != nullptr);
    assert(strncmp((char *) dst14, ".period", sizeof(".period") + 1) == 0);
    assert(dst14_len == sizeof(".period"));
    free(dst14);

    const uint8_t src15[] = "%2Ddash";
    uint8_t *dst15 = nullptr;
    size_t dst15_len = 0;
    const enum url_decode_result r15 = url_decode(src15, sizeof(src15) - 1, &dst15, &dst15_len);
    assert(r15 == URL_DEC_OK);
    assert(dst15 != nullptr);
    assert(strncmp((char *) dst15, "-dash", sizeof("-dash") + 1) == 0);
    assert(dst15_len == sizeof("-dash"));
    free(dst15);

    const uint8_t src16[] = "%5Funderscore";
    uint8_t *dst16 = nullptr;
    size_t dst16_len = 0;
    const enum url_decode_result r16 = url_decode(src16, sizeof(src16) - 1, &dst16, &dst16_len);
    assert(r16 == URL_DEC_OK);
    assert(dst16 != nullptr);
    assert(strncmp((char *) dst16, "_underscore", sizeof("_underscore") + 1) == 0);
    assert(dst16_len == sizeof("_underscore"));
    free(dst16);

    const uint8_t src17[] = "%2Bplus";
    uint8_t *dst17 = nullptr;
    size_t dst17_len = 0;
    const enum url_decode_result r17 = url_decode(src17, sizeof(src17) - 1, &dst17, &dst17_len);
    assert(r17 == URL_DEC_OK);
    assert(dst17 != nullptr);
    assert(strncmp((char *) dst17, "+plus", sizeof("+plus") + 1) == 0);
    assert(dst17_len == sizeof("+plus"));
    free(dst17);

    const uint8_t src18[] = "%2Astar";
    uint8_t *dst18 = nullptr;
    size_t dst18_len = 0;
    const enum url_decode_result r18 = url_decode(src18, sizeof(src18) - 1, &dst18, &dst18_len);
    assert(r18 == URL_DEC_OK);
    assert(dst18 != nullptr);
    assert(strncmp((char *) dst18, "*star", sizeof("*star") + 1) == 0);
    assert(dst18_len == sizeof("*star"));
    free(dst18);

    const uint8_t src19[] = "%3Acolon";
    uint8_t *dst19 = nullptr;
    size_t dst19_len = 0;
    const enum url_decode_result r19 = url_decode(src19, sizeof(src19) - 1, &dst19, &dst19_len);
    assert(r19 == URL_DEC_OK);
    assert(dst19 != nullptr);
    assert(strncmp((char *) dst19, ":colon", sizeof(":colon") + 1) == 0);
    assert(dst19_len == sizeof(":colon"));
    free(dst19);

    const uint8_t src20[] = "slash%2F";
    uint8_t *dst20 = nullptr;
    size_t dst20_len = 0;
    const enum url_decode_result r20 = url_decode(src20, sizeof(src20) - 1, &dst20, &dst20_len);
    assert(r20 == URL_DEC_OK);
    assert(dst20 != nullptr);
    assert(strncmp((char *) dst20, "slash/", sizeof("slash/") + 1) == 0);
    assert(dst20_len == sizeof("slash/"));
    free(dst20);
}

int main() {
    return EXIT_SUCCESS;
}
