#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int MSize ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;
typedef  int /*<<< orphan*/  CTSize ;

/* Variables and functions */
 int /*<<< orphan*/  cconv_array_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cconv_err_initov (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cconv_struct_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ctype_isarray (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isstruct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cconv_multi_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lj_cconv_ct_init(CTState *cts, CType *d, CTSize sz,
		      uint8_t *dp, TValue *o, MSize len)
{
  if (len == 0)
    memset(dp, 0, sz);
  else if (len == 1 && !lj_cconv_multi_init(cts, d, o))
    lj_cconv_ct_tv(cts, d, dp, o, 0);
  else if (ctype_isarray(d->info))  /* Also handles valarray init with len>1. */
    cconv_array_init(cts, d, sz, dp, o, len);
  else if (ctype_isstruct(d->info))
    cconv_struct_init(cts, d, sz, dp, o, len);
  else
    cconv_err_initov(cts, d);
}