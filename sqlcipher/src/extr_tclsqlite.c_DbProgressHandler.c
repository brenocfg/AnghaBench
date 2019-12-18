#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  interp; int /*<<< orphan*/  zProgress; } ;
typedef  TYPE_1__ SqliteDb ;

/* Variables and functions */
 int TCL_OK ; 
 int Tcl_Eval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_GetStringResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DbProgressHandler(void *cd){
  SqliteDb *pDb = (SqliteDb*)cd;
  int rc;

  assert( pDb->zProgress );
  rc = Tcl_Eval(pDb->interp, pDb->zProgress);
  if( rc!=TCL_OK || atoi(Tcl_GetStringResult(pDb->interp)) ){
    return 1;
  }
  return 0;
}