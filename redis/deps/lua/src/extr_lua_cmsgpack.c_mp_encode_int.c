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
typedef  int /*<<< orphan*/  mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_buf_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 

void mp_encode_int(lua_State *L, mp_buf *buf, int64_t n) {
    unsigned char b[9];
    int enclen;

    if (n >= 0) {
        if (n <= 127) {
            b[0] = n & 0x7f;    /* positive fixnum */
            enclen = 1;
        } else if (n <= 0xff) {
            b[0] = 0xcc;        /* uint 8 */
            b[1] = n & 0xff;
            enclen = 2;
        } else if (n <= 0xffff) {
            b[0] = 0xcd;        /* uint 16 */
            b[1] = (n & 0xff00) >> 8;
            b[2] = n & 0xff;
            enclen = 3;
        } else if (n <= 0xffffffffLL) {
            b[0] = 0xce;        /* uint 32 */
            b[1] = (n & 0xff000000) >> 24;
            b[2] = (n & 0xff0000) >> 16;
            b[3] = (n & 0xff00) >> 8;
            b[4] = n & 0xff;
            enclen = 5;
        } else {
            b[0] = 0xcf;        /* uint 64 */
            b[1] = (n & 0xff00000000000000LL) >> 56;
            b[2] = (n & 0xff000000000000LL) >> 48;
            b[3] = (n & 0xff0000000000LL) >> 40;
            b[4] = (n & 0xff00000000LL) >> 32;
            b[5] = (n & 0xff000000) >> 24;
            b[6] = (n & 0xff0000) >> 16;
            b[7] = (n & 0xff00) >> 8;
            b[8] = n & 0xff;
            enclen = 9;
        }
    } else {
        if (n >= -32) {
            b[0] = ((signed char)n);   /* negative fixnum */
            enclen = 1;
        } else if (n >= -128) {
            b[0] = 0xd0;        /* int 8 */
            b[1] = n & 0xff;
            enclen = 2;
        } else if (n >= -32768) {
            b[0] = 0xd1;        /* int 16 */
            b[1] = (n & 0xff00) >> 8;
            b[2] = n & 0xff;
            enclen = 3;
        } else if (n >= -2147483648LL) {
            b[0] = 0xd2;        /* int 32 */
            b[1] = (n & 0xff000000) >> 24;
            b[2] = (n & 0xff0000) >> 16;
            b[3] = (n & 0xff00) >> 8;
            b[4] = n & 0xff;
            enclen = 5;
        } else {
            b[0] = 0xd3;        /* int 64 */
            b[1] = (n & 0xff00000000000000LL) >> 56;
            b[2] = (n & 0xff000000000000LL) >> 48;
            b[3] = (n & 0xff0000000000LL) >> 40;
            b[4] = (n & 0xff00000000LL) >> 32;
            b[5] = (n & 0xff000000) >> 24;
            b[6] = (n & 0xff0000) >> 16;
            b[7] = (n & 0xff00) >> 8;
            b[8] = n & 0xff;
            enclen = 9;
        }
    }
    mp_buf_append(L,buf,b,enclen);
}