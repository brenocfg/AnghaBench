#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {char* member_0; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ table_field ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  status; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  connect; } ;
typedef  TYPE_2__ errors ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TNUMBER ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  set_fields (int /*<<< orphan*/ *,int,TYPE_1__ const*) ; 

void script_errors(lua_State *L, errors *errors) {
    uint64_t e[] = {
        errors->connect,
        errors->read,
        errors->write,
        errors->status,
        errors->timeout
    };
    const table_field fields[] = {
        { "connect", LUA_TNUMBER, &e[0] },
        { "read",    LUA_TNUMBER, &e[1] },
        { "write",   LUA_TNUMBER, &e[2] },
        { "status",  LUA_TNUMBER, &e[3] },
        { "timeout", LUA_TNUMBER, &e[4] },
        { NULL,      0,           NULL  },
    };
    lua_newtable(L);
    set_fields(L, 2, fields);
    lua_setfield(L, 1, "errors");
}