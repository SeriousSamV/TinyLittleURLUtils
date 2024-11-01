#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <tiny_url_encoder.h>

void test_url_encode() {
    // Test 1: Encode "hello!" (symbol !)
    const uint8_t src1[] = "hello!";
    uint8_t *dst1 = nullptr;
    size_t dst1_len = 0;
    const enum url_encode_result r1 = url_encode(src1, sizeof(src1)-1, &dst1, &dst1_len);
    assert(r1 == URL_ENC_OK);
    assert(dst1 != nullptr);
    assert(strncmp((char *) dst1, "hello%21", 32) == 0);
    assert(dst1_len == 8);

    // Test 2: Encode " " (space)
    const uint8_t src2[] = " ";
    uint8_t *dst2 = nullptr;
    size_t dst2_len = 0;
    const enum url_encode_result r2 = url_encode(src2, sizeof(src2) - 1, &dst2, &dst2_len);
    assert(r2 == URL_ENC_OK);
    assert(dst2 != nullptr);
    assert(strncmp((char *) dst2, "%20", 32) == 0);
    assert(dst2_len == 3);
    free(dst2);

    // Test 3: Encode "a+b"
    const uint8_t src3[] = "a+b";
    uint8_t *dst3 = nullptr;
    size_t dst3_len = 0;
    const enum url_encode_result r3 = url_encode(src3, sizeof(src3) - 1, &dst3, &dst3_len);
    assert(r3 == URL_ENC_OK);
    assert(dst3 != nullptr);
    assert(strncmp((char *) dst3, "a%2Bb", 32) == 0);
    assert(dst3_len == 5);
    free(dst3);

    // Test 4: Encode "100%"
    const uint8_t src4[] = "100%";
    uint8_t *dst4 = nullptr;
    size_t dst4_len = 0;
    const enum url_encode_result r4 = url_encode(src4, sizeof(src4) - 1, &dst4, &dst4_len);
    assert(r4 == URL_ENC_OK);
    assert(dst4 != nullptr);
    assert(strncmp((char *) dst4, "100%25", 32) == 0);
    assert(dst4_len == 6);
    free(dst4);

    // Test 5: Encode "!@#"
    const uint8_t src5[] = "!@#";
    uint8_t *dst5 = nullptr;
    size_t dst5_len = 0;
    const enum url_encode_result r5 = url_encode(src5, sizeof(src5) - 1, &dst5, &dst5_len);
    assert(r5 == URL_ENC_OK);
    assert(dst5 != nullptr);
    assert(strncmp((char *) dst5, "%21%40%23", 32) == 0);
    assert(dst5_len == 9);
    free(dst5);

    // Test 6: Encode "foo/bar"
    const uint8_t src6[] = "foo/bar";
    uint8_t *dst6 = nullptr;
    size_t dst6_len = 0;
    const enum url_encode_result r6 = url_encode(src6, sizeof(src6) - 1, &dst6, &dst6_len);
    assert(r6 == URL_ENC_OK);
    assert(dst6 != nullptr);
    assert(strncmp((char *) dst6, "foo%2Fbar", 32) == 0);
    assert(dst6_len == 9);
    free(dst6);

    // Test 7: Encode "日本"
    const uint8_t src7[] = {0xE6, 0x97, 0xA5, 0xE6, 0x9C, 0xAC, 0x00};
    uint8_t *dst7 = nullptr;
    size_t dst7_len = 0;
    const enum url_encode_result r7 = url_encode(src7, 6, &dst7, &dst7_len);
    assert(r7 == URL_ENC_OK);
    assert(dst7 != nullptr);
    assert(strncmp((char *) dst7, "%E6%97%A5%E6%9C%AC", 32) == 0);
    assert(dst7_len == 18);
    free(dst7);

    // Test 8: Encode "-_.*"
    const uint8_t src8[] = "-_.*";
    uint8_t *dst8 = nullptr;
    size_t dst8_len = 0;
    const enum url_encode_result r8 = url_encode(src8, sizeof(src8) - 1, &dst8, &dst8_len);
    assert(r8 == URL_ENC_OK);
    assert(dst8 != nullptr);
    assert(strncmp((char *) dst8, "-_.%2A", 32) == 0);
    assert(dst8_len == 6);
    free(dst8);

    // Test 9: Encode "~"
    const uint8_t src9[] = "~";
    uint8_t *dst9 = nullptr;
    size_t dst9_len = 0;
    const enum url_encode_result r9 = url_encode(src9, sizeof(src9) - 1, &dst9, &dst9_len);
    assert(r9 == URL_ENC_OK);
    assert(dst9 != nullptr);
    assert(strncmp((char *) dst9, "~", 32) == 0);
    assert(dst9_len == 1);
    free(dst9);

    // Test 10: Encode "<>/\\"
    const uint8_t src10[] = "<>/\\";
    uint8_t *dst10 = nullptr;
    size_t dst10_len = 0;
    const enum url_encode_result r10 = url_encode(src10, sizeof(src10) - 1, &dst10, &dst10_len);
    assert(r10 == URL_ENC_OK);
    assert(dst10 != nullptr);
    assert(strncmp((char *) dst10, "%3C%3E%2F%5C", 32) == 0);
    assert(dst10_len == 12);
    free(dst10);

    // Test 11: Encode ""
    const uint8_t src11[] = "";
    uint8_t *dst11 = nullptr;
    size_t dst11_len = 0;
    const enum url_encode_result r11 = url_encode(src11, sizeof(src11) - 1, &dst11, &dst11_len);
    assert(r11 == URL_ENC_OK);
    assert(dst11 != nullptr);
    assert(strcmp((char *) dst11, "") == 0);
    assert(dst11_len == 0);
    free(dst11);

    // Test 12: Encode "😀"
    const uint8_t src12[] = {0xF0, 0x9F, 0x98, 0x80, 0x00};
    uint8_t *dst12 = nullptr;
    size_t dst12_len = 0;
    const enum url_encode_result r12 = url_encode(src12, 4, &dst12, &dst12_len);
    assert(r12 == URL_ENC_OK);
    assert(dst12 != nullptr);
    assert(strncmp((char *) dst12, "%F0%9F%98%80", 32) == 0);
    assert(dst12_len == 12);
    free(dst12);

    // Test 13: Encode "example.com"
    const uint8_t src13[] = "example.com";
    uint8_t *dst13 = nullptr;
    size_t dst13_len = 0;
    const enum url_encode_result r13 = url_encode(src13, sizeof(src13) - 1, &dst13, &dst13_len);
    assert(r13 == URL_ENC_OK);
    assert(dst13 != nullptr);
    assert(strncmp((char *) dst13, "example.com", 32) == 0);
    assert(dst13_len == 11);
    free(dst13);

    // Test 14: Encode "?"
    const uint8_t src14[] = "?";
    uint8_t *dst14 = nullptr;
    size_t dst14_len = 0;
    const enum url_encode_result r14 = url_encode(src14, sizeof(src14) - 1, &dst14, &dst14_len);
    assert(r14 == URL_ENC_OK);
    assert(dst14 != nullptr);
    assert(strncmp((char *) dst14, "%3F", 32) == 0);
    assert(dst14_len == 3);
    free(dst14);

    // Test 15: Encode "&="
    const uint8_t src15[] = "&=";
    uint8_t *dst15 = nullptr;
    size_t dst15_len = 0;
    const enum url_encode_result r15 = url_encode(src15, sizeof(src15) - 1, &dst15, &dst15_len);
    assert(r15 == URL_ENC_OK);
    assert(dst15 != nullptr);
    assert(strncmp((char *) dst15, "%26%3D", 32) == 0);
    assert(dst15_len == 6);
    free(dst15);

    // Test 16: Encode "#$"
    const uint8_t src16[] = "#$";
    uint8_t *dst16 = nullptr;
    size_t dst16_len = 0;
    const enum url_encode_result r16 = url_encode(src16, sizeof(src16) - 1, &dst16, &dst16_len);
    assert(r16 == URL_ENC_OK);
    assert(dst16 != nullptr);
    assert(strncmp((char *) dst16, "%23%24", 32) == 0);
    assert(dst16_len == 6);
    free(dst16);

    // Test 17: Encode "+"
    const uint8_t src17[] = "+";
    uint8_t *dst17 = nullptr;
    size_t dst17_len = 0;
    const enum url_encode_result r17 = url_encode(src17, sizeof(src17) - 1, &dst17, &dst17_len);
    assert(r17 == URL_ENC_OK);
    assert(dst17 != nullptr);
    assert(strncmp((char *) dst17, "%2B", 32) == 0);
    assert(dst17_len == 3);
    free(dst17);
}

int main() {
    return EXIT_SUCCESS;
}
