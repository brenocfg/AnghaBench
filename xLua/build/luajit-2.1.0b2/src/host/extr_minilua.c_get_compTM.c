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
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TMS ;

/* Variables and functions */
 int /*<<< orphan*/ * fasttm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ luaO_rawequalObj (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const TValue*get_compTM(lua_State*L,Table*mt1,Table*mt2,
TMS event){
const TValue*tm1=fasttm(L,mt1,event);
const TValue*tm2;
if(tm1==NULL)return NULL;
if(mt1==mt2)return tm1;
tm2=fasttm(L,mt2,event);
if(tm2==NULL)return NULL;
if(luaO_rawequalObj(tm1,tm2))
return tm1;
return NULL;
}