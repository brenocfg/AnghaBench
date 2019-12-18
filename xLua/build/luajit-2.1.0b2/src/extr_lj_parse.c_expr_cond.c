#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ k; int /*<<< orphan*/  f; } ;
struct TYPE_7__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ ExpDesc ;
typedef  int /*<<< orphan*/  BCPos ;

/* Variables and functions */
 scalar_t__ VKFALSE ; 
 scalar_t__ VKNIL ; 
 int /*<<< orphan*/  bcemit_branch_t (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  expr (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static BCPos expr_cond(LexState *ls)
{
  ExpDesc v;
  expr(ls, &v);
  if (v.k == VKNIL) v.k = VKFALSE;
  bcemit_branch_t(ls->fs, &v);
  return v.f;
}