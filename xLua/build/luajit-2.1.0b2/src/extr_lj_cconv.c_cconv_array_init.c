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
struct TYPE_7__ {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ MSize ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  scalar_t__ CTSize ;

/* Variables and functions */
 int /*<<< orphan*/  cconv_err_initov (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* ctype_rawchild (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cconv_array_init(CTState *cts, CType *d, CTSize sz, uint8_t *dp,
			     TValue *o, MSize len)
{
  CType *dc = ctype_rawchild(cts, d);  /* Array element type. */
  CTSize ofs, esize = dc->size;
  MSize i;
  if (len*esize > sz)
    cconv_err_initov(cts, d);
  for (i = 0, ofs = 0; i < len; i++, ofs += esize)
    lj_cconv_ct_tv(cts, dc, dp + ofs, o + i, 0);
  if (ofs == esize) {  /* Replicate a single element. */
    for (; ofs < sz; ofs += esize) memcpy(dp + ofs, dp, esize);
  } else {  /* Otherwise fill the remainder with zero. */
    memset(dp + ofs, 0, sz - ofs);
  }
}