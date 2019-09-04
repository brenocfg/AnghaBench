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
struct TYPE_4__ {int ptop; int valuecached; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  getfromktable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int updatecache (CapState *cs, int v) {
  int idx = cs->ptop + 1;  /* stack index of cache for Lua values */
  if (v != cs->valuecached) {  /* not there? */
    getfromktable(cs, v);  /* get value from 'ktable' */
    lua_replace(cs->L, idx);  /* put it at reserved stack position */
    cs->valuecached = v;  /* keep track of what is there */
  }
  return idx;
}