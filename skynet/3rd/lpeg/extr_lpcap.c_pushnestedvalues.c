#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* cap; int /*<<< orphan*/  L; } ;
struct TYPE_6__ {scalar_t__ s; scalar_t__ siz; } ;
typedef  TYPE_1__ Capture ;
typedef  TYPE_2__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  isclosecap (TYPE_1__*) ; 
 scalar_t__ isfullcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ pushcapture (TYPE_2__*) ; 

__attribute__((used)) static int pushnestedvalues (CapState *cs, int addextra) {
  Capture *co = cs->cap;
  if (isfullcap(cs->cap++)) {  /* no nested captures? */
    lua_pushlstring(cs->L, co->s, co->siz - 1);  /* push whole match */
    return 1;  /* that is it */
  }
  else {
    int n = 0;
    while (!isclosecap(cs->cap))  /* repeat for all nested patterns */
      n += pushcapture(cs);
    if (addextra || n == 0) {  /* need extra? */
      lua_pushlstring(cs->L, co->s, cs->cap->s - co->s);  /* push whole match */
      n++;
    }
    cs->cap++;  /* skip close entry */
    return n;
  }
}