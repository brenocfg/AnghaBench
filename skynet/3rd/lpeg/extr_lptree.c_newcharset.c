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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 int /*<<< orphan*/  CHARSETSIZE ; 
 int /*<<< orphan*/  TSet ; 
 scalar_t__ bytes2slots (int /*<<< orphan*/ ) ; 
 size_t i ; 
 int /*<<< orphan*/  loopset (size_t,scalar_t__) ; 
 TYPE_1__* newtree (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__* treebuffer (TYPE_1__*) ; 

__attribute__((used)) static TTree *newcharset (lua_State *L) {
  TTree *tree = newtree(L, bytes2slots(CHARSETSIZE) + 1);
  tree->tag = TSet;
  loopset(i, treebuffer(tree)[i] = 0);
  return tree;
}