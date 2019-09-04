#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int* cs; } ;
struct TYPE_9__ {scalar_t__ tag; } ;
typedef  TYPE_1__ TTree ;
typedef  TYPE_2__ Charset ;

/* Variables and functions */
 int /*<<< orphan*/  TChoice ; 
 scalar_t__ TFalse ; 
 TYPE_1__* getpatt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 size_t i ; 
 int /*<<< orphan*/  loopset (size_t,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* newcharset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newroot2sib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nofail (TYPE_1__*) ; 
 scalar_t__ tocharset (TYPE_1__*,TYPE_2__*) ; 
 int* treebuffer (TYPE_1__*) ; 

__attribute__((used)) static int lp_choice (lua_State *L) {
  Charset st1, st2;
  TTree *t1 = getpatt(L, 1, NULL);
  TTree *t2 = getpatt(L, 2, NULL);
  if (tocharset(t1, &st1) && tocharset(t2, &st2)) {
    TTree *t = newcharset(L);
    loopset(i, treebuffer(t)[i] = st1.cs[i] | st2.cs[i]);
  }
  else if (nofail(t1) || t2->tag == TFalse)
    lua_pushvalue(L, 1);  /* true / x => true, x / false => x */
  else if (t1->tag == TFalse)
    lua_pushvalue(L, 2);  /* false / x => x */
  else
    newroot2sib(L, TChoice);
  return 1;
}