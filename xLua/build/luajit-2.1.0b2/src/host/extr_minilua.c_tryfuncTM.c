#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_9__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  TM_CALL ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  luaG_typeerror (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/ * luaT_gettmbyobj (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ restorestack (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ttisfunction (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static StkId tryfuncTM(lua_State*L,StkId func){
const TValue*tm=luaT_gettmbyobj(L,func,TM_CALL);
StkId p;
ptrdiff_t funcr=savestack(L,func);
if(!ttisfunction(tm))
luaG_typeerror(L,func,"call");
for(p=L->top;p>func;p--)setobj(L,p,p-1);
incr_top(L);
func=restorestack(L,funcr);
setobj(L,func,tm);
return func;
}