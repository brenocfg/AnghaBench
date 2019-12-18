#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  INVALID_HID_DESC_5 ;
typedef  int /*<<< orphan*/  INVALID_HID_DESC_4 ;
typedef  int /*<<< orphan*/  INVALID_HID_DESC_3 ;
typedef  int /*<<< orphan*/  INVALID_HID_DESC_2 ;
typedef  int /*<<< orphan*/  INVALID_HID_DESC_1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ is_fido_security_token_desc (int const*,int) ; 

__attribute__((used)) static void test_is_fido_security_token_desc__invalid(void) {
        /* Size coded on 1 byte, but no byte given */
        static const uint8_t INVALID_HID_DESC_1[] = { 0x01 };
        assert_se(is_fido_security_token_desc(INVALID_HID_DESC_1, sizeof(INVALID_HID_DESC_1)) < 0);

        /* Size coded on 2 bytes, but only 1 byte given */
        static const uint8_t INVALID_HID_DESC_2[] = { 0x02, 0x01 };
        assert_se(is_fido_security_token_desc(INVALID_HID_DESC_2, sizeof(INVALID_HID_DESC_2)) < 0);

        /* Size coded on 4 bytes, but only 3 bytes given */
        static const uint8_t INVALID_HID_DESC_3[] = { 0x03, 0x01, 0x02, 0x03 };
        assert_se(is_fido_security_token_desc(INVALID_HID_DESC_3, sizeof(INVALID_HID_DESC_3)) < 0);

        /* Long item without a size byte */
        static const uint8_t INVALID_HID_DESC_4[] = { 0xfe };
        assert_se(is_fido_security_token_desc(INVALID_HID_DESC_4, sizeof(INVALID_HID_DESC_4)) < 0);

        /* Usage pages are coded on at most 2 bytes */
        static const uint8_t INVALID_HID_DESC_5[] = { 0x07, 0x01, 0x02, 0x03, 0x04 };
        assert_se(is_fido_security_token_desc(INVALID_HID_DESC_5, sizeof(INVALID_HID_DESC_5)) < 0);
}