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
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
#define  LUA_OPBAND 136 
#define  LUA_OPBNOT 135 
#define  LUA_OPBOR 134 
#define  LUA_OPBXOR 133 
#define  LUA_OPDIV 132 
#define  LUA_OPIDIV 131 
#define  LUA_OPMOD 130 
#define  LUA_OPSHL 129 
#define  LUA_OPSHR 128 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tointeger (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int validop (int op, TValue *v1, TValue *v2) {
  switch (op) {
    case LUA_OPBAND: case LUA_OPBOR: case LUA_OPBXOR:
    case LUA_OPSHL: case LUA_OPSHR: case LUA_OPBNOT: {  /* conversion errors */
      lua_Integer i;
      return (tointeger(v1, &i) && tointeger(v2, &i));
    }
    case LUA_OPDIV: case LUA_OPIDIV: case LUA_OPMOD:  /* division by 0 */
      return (nvalue(v2) != 0);
    default: return 1;  /* everything else is valid */
  }
}