#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_21__ {int currentline; int isvararg; int istailcall; char* namewhat; int /*<<< orphan*/ * name; int /*<<< orphan*/  nparams; int /*<<< orphan*/  nups; } ;
typedef  TYPE_5__ lua_Debug ;
struct TYPE_23__ {int callstatus; } ;
struct TYPE_20__ {TYPE_3__* p; } ;
struct TYPE_17__ {int /*<<< orphan*/  nupvalues; } ;
struct TYPE_22__ {TYPE_4__ l; TYPE_1__ c; } ;
struct TYPE_19__ {TYPE_2__* sp; } ;
struct TYPE_18__ {int is_vararg; int /*<<< orphan*/  numparams; } ;
typedef  TYPE_6__ Closure ;
typedef  TYPE_7__ CallInfo ;

/* Variables and functions */
 int CIST_TAIL ; 
 int currentline (TYPE_7__*) ; 
 int /*<<< orphan*/  funcinfo (TYPE_5__*,TYPE_6__*) ; 
 char* getfuncname (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isLua (TYPE_7__*) ; 
 int /*<<< orphan*/  noLuaClosure (TYPE_6__*) ; 

__attribute__((used)) static int auxgetinfo (lua_State *L, const char *what, lua_Debug *ar,
                       Closure *f, CallInfo *ci) {
  int status = 1;
  for (; *what; what++) {
    switch (*what) {
      case 'S': {
        funcinfo(ar, f);
        break;
      }
      case 'l': {
        ar->currentline = (ci && isLua(ci)) ? currentline(ci) : -1;
        break;
      }
      case 'u': {
        ar->nups = (f == NULL) ? 0 : f->c.nupvalues;
        if (noLuaClosure(f)) {
          ar->isvararg = 1;
          ar->nparams = 0;
        }
        else {
          ar->isvararg = f->l.p->sp->is_vararg;
          ar->nparams = f->l.p->sp->numparams;
        }
        break;
      }
      case 't': {
        ar->istailcall = (ci) ? ci->callstatus & CIST_TAIL : 0;
        break;
      }
      case 'n': {
        ar->namewhat = getfuncname(L, ci, &ar->name);
        if (ar->namewhat == NULL) {
          ar->namewhat = "";  /* not found */
          ar->name = NULL;
        }
        break;
      }
      case 'L':
      case 'f':  /* handled by lua_getinfo */
        break;
      default: status = 0;  /* invalid option */
    }
  }
  return status;
}