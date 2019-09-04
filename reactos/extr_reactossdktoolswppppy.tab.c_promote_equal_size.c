#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; } ;
typedef  TYPE_1__ cval_t ;

/* Variables and functions */
 int SIZE_MASK ; 
 int /*<<< orphan*/  cast_to_sint (TYPE_1__*) ; 
 int /*<<< orphan*/  cast_to_sll (TYPE_1__*) ; 
 int /*<<< orphan*/  cast_to_slong (TYPE_1__*) ; 
 int /*<<< orphan*/  cast_to_uint (TYPE_1__*) ; 
 int /*<<< orphan*/  cast_to_ull (TYPE_1__*) ; 
 int /*<<< orphan*/  cast_to_ulong (TYPE_1__*) ; 
#define  cv_sint 133 
#define  cv_sll 132 
#define  cv_slong 131 
#define  cv_uint 130 
#define  cv_ull 129 
#define  cv_ulong 128 

__attribute__((used)) static void promote_equal_size(cval_t *v1, cval_t *v2)
{
#define cv_sizeof(v)	((int)(v->type & SIZE_MASK))
	int s1 = cv_sizeof(v1);
	int s2 = cv_sizeof(v2);
#undef cv_sizeof

	if(s1 == s2)
		return;
	else if(s1 > s2)
	{
		switch(v1->type)
		{
		case cv_sint:	cast_to_sint(v2); break;
		case cv_uint:	cast_to_uint(v2); break;
		case cv_slong:	cast_to_slong(v2); break;
		case cv_ulong:	cast_to_ulong(v2); break;
		case cv_sll:	cast_to_sll(v2); break;
		case cv_ull:	cast_to_ull(v2); break;
		}
	}
	else
	{
		switch(v2->type)
		{
		case cv_sint:	cast_to_sint(v1); break;
		case cv_uint:	cast_to_uint(v1); break;
		case cv_slong:	cast_to_slong(v1); break;
		case cv_ulong:	cast_to_ulong(v1); break;
		case cv_sll:	cast_to_sll(v1); break;
		case cv_ull:	cast_to_ull(v1); break;
		}
	}
}