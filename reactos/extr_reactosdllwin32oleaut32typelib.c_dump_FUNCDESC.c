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
struct TYPE_3__ {int cParams; int funckind; int invkind; int callconv; int /*<<< orphan*/  elemdescFunc; int /*<<< orphan*/  wFuncFlags; int /*<<< orphan*/  cParamsOpt; int /*<<< orphan*/  oVft; int /*<<< orphan*/ * lprgelemdescParam; int /*<<< orphan*/  memid; } ;
typedef  TYPE_1__ FUNCDESC ;

/* Variables and functions */
#define  CC_CDECL 140 
#define  CC_PASCAL 139 
#define  CC_STDCALL 138 
#define  CC_SYSCALL 137 
#define  FUNC_DISPATCH 136 
#define  FUNC_NONVIRTUAL 135 
#define  FUNC_PUREVIRTUAL 134 
#define  FUNC_STATIC 133 
#define  FUNC_VIRTUAL 132 
#define  INVOKE_FUNC 131 
#define  INVOKE_PROPERTYGET 130 
#define  INVOKE_PROPERTYPUT 129 
#define  INVOKE_PROPERTYPUTREF 128 
 int /*<<< orphan*/  MESSAGE (char*,...) ; 
 int /*<<< orphan*/  dump_ELEMDESC (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dump_FUNCDESC(const FUNCDESC *funcdesc) {
  int i;
  MESSAGE("memid is %08x\n",funcdesc->memid);
  for (i=0;i<funcdesc->cParams;i++) {
      MESSAGE("Param %d:\n",i);
      dump_ELEMDESC(funcdesc->lprgelemdescParam+i);
  }
  MESSAGE("\tfunckind: %d (",funcdesc->funckind);
  switch (funcdesc->funckind) {
  case FUNC_VIRTUAL: MESSAGE("virtual");break;
  case FUNC_PUREVIRTUAL: MESSAGE("pure virtual");break;
  case FUNC_NONVIRTUAL: MESSAGE("nonvirtual");break;
  case FUNC_STATIC: MESSAGE("static");break;
  case FUNC_DISPATCH: MESSAGE("dispatch");break;
  default: MESSAGE("unknown");break;
  }
  MESSAGE(")\n\tinvkind: %d (",funcdesc->invkind);
  switch (funcdesc->invkind) {
  case INVOKE_FUNC: MESSAGE("func");break;
  case INVOKE_PROPERTYGET: MESSAGE("property get");break;
  case INVOKE_PROPERTYPUT: MESSAGE("property put");break;
  case INVOKE_PROPERTYPUTREF: MESSAGE("property put ref");break;
  }
  MESSAGE(")\n\tcallconv: %d (",funcdesc->callconv);
  switch (funcdesc->callconv) {
  case CC_CDECL: MESSAGE("cdecl");break;
  case CC_PASCAL: MESSAGE("pascal");break;
  case CC_STDCALL: MESSAGE("stdcall");break;
  case CC_SYSCALL: MESSAGE("syscall");break;
  default:break;
  }
  MESSAGE(")\n\toVft: %d\n", funcdesc->oVft);
  MESSAGE("\tcParamsOpt: %d\n", funcdesc->cParamsOpt);
  MESSAGE("\twFlags: %x\n", funcdesc->wFuncFlags);

  MESSAGE("\telemdescFunc (return value type):\n");
  dump_ELEMDESC(&funcdesc->elemdescFunc);
}