#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 int LJ_MAX_ABITS ; 
 int bestasize (int*,int*) ; 
 int countarray (int /*<<< orphan*/ *,int*) ; 
 int counthash (int /*<<< orphan*/ *,int*,int*) ; 
 int countint (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  hsize2hbits (int) ; 
 int /*<<< orphan*/  lj_tab_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rehashtab(lua_State *L, GCtab *t, cTValue *ek)
{
  uint32_t bins[LJ_MAX_ABITS];
  uint32_t total, asize, na, i;
  for (i = 0; i < LJ_MAX_ABITS; i++) bins[i] = 0;
  asize = countarray(t, bins);
  total = 1 + asize;
  total += counthash(t, bins, &asize);
  asize += countint(ek, bins);
  na = bestasize(bins, &asize);
  total -= na;
  lj_tab_resize(L, t, asize, hsize2hbits(total));
}