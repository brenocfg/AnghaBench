#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t free; int len; unsigned char* b; } ;
typedef  TYPE_1__ mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 scalar_t__ mp_realloc (int /*<<< orphan*/ *,unsigned char*,size_t,size_t) ; 

void mp_buf_append(lua_State *L, mp_buf *buf, const unsigned char *s, size_t len) {
    if (buf->free < len) {
        size_t newsize = (buf->len+len)*2;

        buf->b = (unsigned char*)mp_realloc(L, buf->b, buf->len + buf->free, newsize);
        buf->free = newsize - buf->len;
    }
    memcpy(buf->b+buf->len,s,len);
    buf->len += len;
    buf->free -= len;
}