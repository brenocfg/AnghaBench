#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ TTree ;
typedef  int /*<<< orphan*/  CompileState ;

/* Variables and functions */
 int /*<<< orphan*/  Cclose ; 
 int /*<<< orphan*/  Cgroup ; 
 int /*<<< orphan*/  ICloseRunTime ; 
 int /*<<< orphan*/  IOpenCapture ; 
 int /*<<< orphan*/  addinstcap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullset ; 
 int /*<<< orphan*/  sib1 (TYPE_1__*) ; 

__attribute__((used)) static void coderuntime (CompileState *compst, TTree *tree, int tt) {
  addinstcap(compst, IOpenCapture, Cgroup, tree->key, 0);
  codegen(compst, sib1(tree), 0, tt, fullset);
  addinstcap(compst, ICloseRunTime, Cclose, 0, 0);
}