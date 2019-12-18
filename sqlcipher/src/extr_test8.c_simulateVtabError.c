#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zErrMsg; } ;
struct TYPE_5__ {TYPE_1__ base; int /*<<< orphan*/  interp; int /*<<< orphan*/  zTableName; } ;
typedef  TYPE_2__ echo_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  TCL_GLOBAL_ONLY ; 
 char* Tcl_GetVar (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simulateVtabError(echo_vtab *p, const char *zMethod){
  const char *zErr;
  char zVarname[128];
  zVarname[127] = '\0';
  sqlite3_snprintf(127, zVarname, "echo_module_fail(%s,%s)", zMethod, p->zTableName);
  zErr = Tcl_GetVar(p->interp, zVarname, TCL_GLOBAL_ONLY);
  if( zErr ){
    p->base.zErrMsg = sqlite3_mprintf("echo-vtab-error: %s", zErr);
  }
  return (zErr!=0);
}