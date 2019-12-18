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
struct TYPE_8__ {int /*<<< orphan*/  L; } ;
struct TYPE_7__ {int sizecode; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ Proto ;
typedef  TYPE_2__ LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  Instruction ; 
 int LoadInt (TYPE_2__*) ; 
 int /*<<< orphan*/  LoadVector (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaM_newvector (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LoadCode (LoadState *S, Proto *f) {
  int n = LoadInt(S);
  f->code = luaM_newvector(S->L, n, Instruction);
  f->sizecode = n;
  LoadVector(S, f->code, n);
}