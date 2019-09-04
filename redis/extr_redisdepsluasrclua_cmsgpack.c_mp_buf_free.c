#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; int free; struct TYPE_4__* b; } ;
typedef  TYPE_1__ mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  mp_realloc (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void mp_buf_free(lua_State *L, mp_buf *buf) {
    mp_realloc(L, buf->b, buf->len + buf->free, 0); /* realloc to 0 = free */
    mp_realloc(L, buf, sizeof(*buf), 0);
}