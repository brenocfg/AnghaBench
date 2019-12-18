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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ table_field ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TNUMBER ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_fields (int /*<<< orphan*/ *,int,TYPE_1__ const*) ; 

void script_summary(lua_State *L, uint64_t duration, uint64_t requests, uint64_t bytes) {
    const table_field fields[] = {
        { "duration", LUA_TNUMBER, &duration },
        { "requests", LUA_TNUMBER, &requests },
        { "bytes",    LUA_TNUMBER, &bytes    },
        { NULL,       0,           NULL      },
    };
    lua_newtable(L);
    set_fields(L, 1, fields);
}