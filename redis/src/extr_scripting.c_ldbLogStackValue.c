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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  ldbCatStackValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldbLogWithMaxLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsnew (char*) ; 

void ldbLogStackValue(lua_State *lua, char *prefix) {
    sds s = sdsnew(prefix);
    s = ldbCatStackValue(s,lua,-1);
    ldbLogWithMaxLen(s);
}