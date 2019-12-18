#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_18__ ;
typedef  struct TYPE_22__   TYPE_16__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_12__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ kind; } ;
typedef  TYPE_3__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_28__ {int num; int gen; } ;
struct TYPE_27__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct TYPE_25__ {TYPE_3__* v; TYPE_3__* k; } ;
struct TYPE_24__ {int i; int /*<<< orphan*/  f; } ;
struct TYPE_23__ {int len; TYPE_3__** items; } ;
struct TYPE_22__ {int len; TYPE_2__* items; } ;
struct TYPE_21__ {int /*<<< orphan*/  n; } ;
struct TYPE_20__ {TYPE_1__ u; } ;

/* Variables and functions */
 TYPE_18__* ARRAY (TYPE_3__*) ; 
 TYPE_16__* DICT (TYPE_3__*) ; 
 TYPE_14__* NAME (TYPE_3__*) ; 
 TYPE_12__* NUM (TYPE_3__*) ; 
#define  PDF_ARRAY 134 
#define  PDF_DICT 133 
 TYPE_3__* PDF_FALSE ; 
#define  PDF_INDIRECT 132 
#define  PDF_INT 131 
 TYPE_3__* PDF_LIMIT ; 
#define  PDF_NAME 130 
 int /*<<< orphan*/ * PDF_NAME_LIST ; 
#define  PDF_REAL 129 
#define  PDF_STRING 128 
 TYPE_8__* REF (TYPE_3__*) ; 
 TYPE_6__* STRING (TYPE_3__*) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pdf_objcmp(fz_context *ctx, pdf_obj *a, pdf_obj *b)
{
	int i;

	if (a == b)
		return 0;

	/* a or b is null, true, or false */
	if (a <= PDF_FALSE || b <= PDF_FALSE)
		return 1;

	/* a is a constant name */
	if (a < PDF_LIMIT)
	{
		if (b < PDF_LIMIT)
			return a != b;
		if (b->kind != PDF_NAME)
			return 1;
		return strcmp(PDF_NAME_LIST[(intptr_t)a], NAME(b)->n);
	}

	/* b is a constant name */
	if (b < PDF_LIMIT)
	{
		if (a->kind != PDF_NAME)
			return 1;
		return strcmp(NAME(a)->n, PDF_NAME_LIST[(intptr_t)b]);
	}

	/* both a and b are allocated objects */
	if (a->kind != b->kind)
		return 1;

	switch (a->kind)
	{
	case PDF_INT:
		return NUM(a)->u.i - NUM(b)->u.i;

	case PDF_REAL:
		if (NUM(a)->u.f < NUM(b)->u.f)
			return -1;
		if (NUM(a)->u.f > NUM(b)->u.f)
			return 1;
		return 0;

	case PDF_STRING:
		if (STRING(a)->len < STRING(b)->len)
		{
			if (memcmp(STRING(a)->buf, STRING(b)->buf, STRING(a)->len) <= 0)
				return -1;
			return 1;
		}
		if (STRING(a)->len > STRING(b)->len)
		{
			if (memcmp(STRING(a)->buf, STRING(b)->buf, STRING(b)->len) >= 0)
				return 1;
			return -1;
		}
		return memcmp(STRING(a)->buf, STRING(b)->buf, STRING(a)->len);

	case PDF_NAME:
		return strcmp(NAME(a)->n, NAME(b)->n);

	case PDF_INDIRECT:
		if (REF(a)->num == REF(b)->num)
			return REF(a)->gen - REF(b)->gen;
		return REF(a)->num - REF(b)->num;

	case PDF_ARRAY:
		if (ARRAY(a)->len != ARRAY(b)->len)
			return ARRAY(a)->len - ARRAY(b)->len;
		for (i = 0; i < ARRAY(a)->len; i++)
			if (pdf_objcmp(ctx, ARRAY(a)->items[i], ARRAY(b)->items[i]))
				return 1;
		return 0;

	case PDF_DICT:
		if (DICT(a)->len != DICT(b)->len)
			return DICT(a)->len - DICT(b)->len;
		for (i = 0; i < DICT(a)->len; i++)
		{
			if (pdf_objcmp(ctx, DICT(a)->items[i].k, DICT(b)->items[i].k))
				return 1;
			if (pdf_objcmp(ctx, DICT(a)->items[i].v, DICT(b)->items[i].v))
				return 1;
		}
		return 0;
	}
	return 1;
}