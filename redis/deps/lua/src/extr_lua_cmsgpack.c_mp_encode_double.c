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
typedef  int /*<<< orphan*/  f ;
typedef  int /*<<< orphan*/  d ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 int /*<<< orphan*/  memrevifle (unsigned char*,int) ; 
 int /*<<< orphan*/  mp_buf_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 

void mp_encode_double(lua_State *L, mp_buf *buf, double d) {
    unsigned char b[9];
    float f = d;

    assert(sizeof(f) == 4 && sizeof(d) == 8);
    if (d == (double)f) {
        b[0] = 0xca;    /* float IEEE 754 */
        memcpy(b+1,&f,4);
        memrevifle(b+1,4);
        mp_buf_append(L,buf,b,5);
    } else if (sizeof(d) == 8) {
        b[0] = 0xcb;    /* double IEEE 754 */
        memcpy(b+1,&d,8);
        memrevifle(b+1,8);
        mp_buf_append(L,buf,b,9);
    }
}