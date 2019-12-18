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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int MSize ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/ * lj_tab_getint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MSize unbound_search(GCtab *t, MSize j)
{
  cTValue *tv;
  MSize i = j;  /* i is zero or a present index */
  j++;
  /* find `i' and `j' such that i is present and j is not */
  while ((tv = lj_tab_getint(t, (int32_t)j)) && !tvisnil(tv)) {
    i = j;
    j *= 2;
    if (j > (MSize)(INT_MAX-2)) {  /* overflow? */
      /* table was built with bad purposes: resort to linear search */
      i = 1;
      while ((tv = lj_tab_getint(t, (int32_t)i)) && !tvisnil(tv)) i++;
      return i - 1;
    }
  }
  /* now do a binary search between them */
  while (j - i > 1) {
    MSize m = (i+j)/2;
    cTValue *tvb = lj_tab_getint(t, (int32_t)m);
    if (tvb && !tvisnil(tvb)) i = m; else j = m;
  }
  return i;
}