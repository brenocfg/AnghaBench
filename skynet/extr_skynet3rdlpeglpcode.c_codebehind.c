#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ n; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ TTree ;
typedef  int /*<<< orphan*/  CompileState ;

/* Variables and functions */
 int /*<<< orphan*/  IBehind ; 
 int /*<<< orphan*/  NOINST ; 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullset ; 
 int /*<<< orphan*/  sib1 (TYPE_2__*) ; 

__attribute__((used)) static void codebehind (CompileState *compst, TTree *tree) {
  if (tree->u.n > 0)
    addinstruction(compst, IBehind, tree->u.n);
  codegen(compst, sib1(tree), 0, NOINST, fullset);
}