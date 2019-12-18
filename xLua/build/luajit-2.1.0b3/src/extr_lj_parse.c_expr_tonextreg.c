#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ freereg; } ;
typedef  TYPE_1__ FuncState ;
typedef  int /*<<< orphan*/  ExpDesc ;

/* Variables and functions */
 int /*<<< orphan*/  bcreg_reserve (TYPE_1__*,int) ; 
 int /*<<< orphan*/  expr_discharge (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expr_toreg (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void expr_tonextreg(FuncState *fs, ExpDesc *e)
{
  expr_discharge(fs, e);
  expr_free(fs, e);
  bcreg_reserve(fs, 1);
  expr_toreg(fs, e, fs->freereg - 1);
}