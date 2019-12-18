#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cts; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CPState ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_CTYPE_RESTORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LJ_CTYPE_SAVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  cpcparser ; 
 int lj_vm_cpcall (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

int lj_cparse(CPState *cp)
{
  LJ_CTYPE_SAVE(cp->cts);
  int errcode = lj_vm_cpcall(cp->L, NULL, cp, cpcparser);
  if (errcode)
    LJ_CTYPE_RESTORE(cp->cts);
  cp_cleanup(cp);
  return errcode;
}