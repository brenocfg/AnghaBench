#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  info; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct TYPE_7__ {scalar_t__ k; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  TYPE_3__ ExpDesc ;

/* Variables and functions */
 scalar_t__ VNONRELOC ; 
 int /*<<< orphan*/  bcreg_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void expr_free(FuncState *fs, ExpDesc *e)
{
  if (e->k == VNONRELOC)
    bcreg_free(fs, e->u.s.info);
}