#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {scalar_t__ hmask; } ;
typedef  TYPE_1__ GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  clearapart (TYPE_1__*) ; 
 int /*<<< orphan*/  clearhpart (TYPE_1__*) ; 
 TYPE_1__* newtab (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GCtab *lj_tab_new(lua_State *L, uint32_t asize, uint32_t hbits)
{
  GCtab *t = newtab(L, asize, hbits);
  clearapart(t);
  if (t->hmask > 0) clearhpart(t);
  return t;
}