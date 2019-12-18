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
struct TYPE_3__ {long double msec; scalar_t__ sec; } ;
typedef  TYPE_1__ ngx_time_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_timeofday () ; 

__attribute__((used)) static int
ngx_http_lua_ngx_now(lua_State *L)
{
    ngx_time_t              *tp;

    tp = ngx_timeofday();

    lua_pushnumber(L, (lua_Number) (tp->sec + tp->msec / 1000.0L));

    return 1;
}