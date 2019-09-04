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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/ * tree; } ;
typedef  int /*<<< orphan*/  TTree ;
typedef  TYPE_1__ Pattern ;

/* Variables and functions */
 TYPE_1__* getpattern (int /*<<< orphan*/ *,int) ; 
 int getsize (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static TTree *gettree (lua_State *L, int idx, int *len) {
  Pattern *p = getpattern(L, idx);
  if (len)
    *len = getsize(L, idx);
  return p->tree;
}