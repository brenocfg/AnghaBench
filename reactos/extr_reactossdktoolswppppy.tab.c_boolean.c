#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wrc_ull_t ;
typedef  int /*<<< orphan*/  wrc_sll_t ;
struct TYPE_4__ {int si; unsigned int ui; long sl; unsigned long ul; int /*<<< orphan*/  ull; int /*<<< orphan*/  sll; } ;
struct TYPE_5__ {int type; TYPE_1__ val; } ;
typedef  TYPE_2__ cval_t ;

/* Variables and functions */
#define  cv_sint 133 
#define  cv_sll 132 
#define  cv_slong 131 
#define  cv_uint 130 
#define  cv_ull 129 
#define  cv_ulong 128 

__attribute__((used)) static int boolean(cval_t *v)
{
	switch(v->type)
	{
	case cv_sint:	return v->val.si != (int)0;
	case cv_uint:	return v->val.ui != (unsigned int)0;
	case cv_slong:	return v->val.sl != (long)0;
	case cv_ulong:	return v->val.ul != (unsigned long)0;
	case cv_sll:	return v->val.sll != (wrc_sll_t)0;
	case cv_ull:	return v->val.ull != (wrc_ull_t)0;
	}
	return 0;
}