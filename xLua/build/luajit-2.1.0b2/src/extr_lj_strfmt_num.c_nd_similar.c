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
typedef  size_t uint32_t ;
typedef  int MSize ;

/* Variables and functions */
 scalar_t__ LJ_UNLIKELY (int) ; 
 int /*<<< orphan*/  lj_strfmt_wuint9 (char*,size_t) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 

__attribute__((used)) static int nd_similar(uint32_t* nd, uint32_t ndhi, uint32_t* ref, MSize hilen,
		      MSize prec)
{
  char nd9[9], ref9[9];
  if (hilen <= prec) {
    if (LJ_UNLIKELY(nd[ndhi] != *ref)) return 0;
    prec -= hilen; ref--; ndhi = (ndhi - 1) & 0x3f;
    if (prec >= 9) {
      if (LJ_UNLIKELY(nd[ndhi] != *ref)) return 0;
      prec -= 9; ref--; ndhi = (ndhi - 1) & 0x3f;
    }
  } else {
    prec -= hilen - 9;
  }
  lua_assert(prec < 9);
  lj_strfmt_wuint9(nd9, nd[ndhi]);
  lj_strfmt_wuint9(ref9, *ref);
  return !memcmp(nd9, ref9, prec) && (nd9[prec] < '5') == (ref9[prec] < '5');
}