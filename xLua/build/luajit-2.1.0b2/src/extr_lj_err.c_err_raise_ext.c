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
struct TYPE_3__ {int /*<<< orphan*/ * excleanup; int /*<<< orphan*/  exclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_UEXCLASS_MAKE (int) ; 
 int /*<<< orphan*/  _Unwind_RaiseException (TYPE_1__*) ; 
 TYPE_1__ static_uex ; 

__attribute__((used)) static void err_raise_ext(int errcode)
{
  static_uex.exclass = LJ_UEXCLASS_MAKE(errcode);
  static_uex.excleanup = NULL;
  _Unwind_RaiseException(&static_uex);
}