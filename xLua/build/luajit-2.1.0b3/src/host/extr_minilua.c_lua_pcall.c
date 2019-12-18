#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct CallS {int func; int nresults; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
struct TYPE_10__ {int top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int StkId ;

/* Variables and functions */
 int /*<<< orphan*/  adjustresults (TYPE_1__*,int) ; 
 int /*<<< orphan*/  api_checknelems (TYPE_1__*,int) ; 
 int /*<<< orphan*/  api_checkvalidindex (TYPE_1__*,int) ; 
 int /*<<< orphan*/  checkresults (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  f_call ; 
 int index2adr (TYPE_1__*,int) ; 
 int luaD_pcall (TYPE_1__*,int /*<<< orphan*/ ,struct CallS*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,int) ; 

__attribute__((used)) static int lua_pcall(lua_State*L,int nargs,int nresults,int errfunc){
struct CallS c;
int status;
ptrdiff_t func;
api_checknelems(L,nargs+1);
checkresults(L,nargs,nresults);
if(errfunc==0)
func=0;
else{
StkId o=index2adr(L,errfunc);
api_checkvalidindex(L,o);
func=savestack(L,o);
}
c.func=L->top-(nargs+1);
c.nresults=nresults;
status=luaD_pcall(L,f_call,&c,savestack(L,c.func),func);
adjustresults(L,nresults);
return status;
}