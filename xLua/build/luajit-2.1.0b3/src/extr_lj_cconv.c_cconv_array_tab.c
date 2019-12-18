#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_7__ {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  scalar_t__ CTSize ;
typedef  int /*<<< orphan*/  CTInfo ;

/* Variables and functions */
 scalar_t__ CTSIZE_INVALID ; 
 int /*<<< orphan*/  cconv_err_initov (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_tab_getint (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cconv_array_tab(CTState *cts, CType *d,
			    uint8_t *dp, GCtab *t, CTInfo flags)
{
  int32_t i;
  CType *dc = ctype_rawchild(cts, d);  /* Array element type. */
  CTSize size = d->size, esize = dc->size, ofs = 0;
  for (i = 0; ; i++) {
    TValue *tv = (TValue *)lj_tab_getint(t, i);
    if (!tv || tvisnil(tv)) {
      if (i == 0) continue;  /* Try again for 1-based tables. */
      break;  /* Stop at first nil. */
    }
    if (ofs >= size)
      cconv_err_initov(cts, d);
    lj_cconv_ct_tv(cts, dc, dp + ofs, tv, flags);
    ofs += esize;
  }
  if (size != CTSIZE_INVALID) {  /* Only fill up arrays with known size. */
    if (ofs == esize) {  /* Replicate a single element. */
      for (; ofs < size; ofs += esize) memcpy(dp + ofs, dp, esize);
    } else {  /* Otherwise fill the remainder with zero. */
      memset(dp + ofs, 0, size - ofs);
    }
  }
}