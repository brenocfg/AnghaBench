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
struct TYPE_3__ {scalar_t__ free; scalar_t__ len; int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ mp_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

mp_buf *mp_buf_new(lua_State *L) {
    mp_buf *buf = NULL;

    /* Old size = 0; new size = sizeof(*buf) */
    buf = (mp_buf*)mp_realloc(L, NULL, 0, sizeof(*buf));

    buf->b = NULL;
    buf->len = buf->free = 0;
    return buf;
}