#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int nactvar; int /*<<< orphan*/  ls; } ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_1__ FuncState ;
typedef  int /*<<< orphan*/  BCReg ;

/* Variables and functions */
 int /*<<< orphan*/ * strref (int /*<<< orphan*/ ) ; 
 TYPE_3__ var_get (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static BCReg var_lookup_local(FuncState *fs, GCstr *n)
{
  int i;
  for (i = fs->nactvar-1; i >= 0; i--) {
    if (n == strref(var_get(fs->ls, fs, i).name))
      return (BCReg)i;
  }
  return (BCReg)-1;  /* Not found. */
}