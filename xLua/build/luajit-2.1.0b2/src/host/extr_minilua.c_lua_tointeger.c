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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/ * index2adr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_number2integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ tonumber (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lua_Integer lua_tointeger(lua_State*L,int idx){
TValue n;
const TValue*o=index2adr(L,idx);
if(tonumber(o,&n)){
lua_Integer res;
lua_Number num=nvalue(o);
lua_number2integer(res,num);
return res;
}
else
return 0;
}