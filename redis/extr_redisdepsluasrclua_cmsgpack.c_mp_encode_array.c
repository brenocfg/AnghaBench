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

void mp_encode_array(lua_State *L, mp_buf *buf, int64_t n) {
    unsigned char b[5];
    int enclen;

    if (n <= 15) {
        b[0] = 0x90 | (n & 0xf);    /* fix array */
        enclen = 1;
    } else if (n <= 65535) {
        b[0] = 0xdc;                /* array 16 */
        b[1] = (n & 0xff00) >> 8;
        b[2] = n & 0xff;
        enclen = 3;
    } else {
        b[0] = 0xdd;                /* array 32 */
        b[1] = (n & 0xff000000) >> 24;
        b[2] = (n & 0xff0000) >> 16;
        b[3] = (n & 0xff00) >> 8;
        b[4] = n & 0xff;
        enclen = 5;
    }
    mp_buf_append(L,buf,b,enclen);
}