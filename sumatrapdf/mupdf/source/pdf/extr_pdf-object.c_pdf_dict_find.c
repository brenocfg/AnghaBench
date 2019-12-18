#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; } ;
typedef  TYPE_2__ pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_13__ {int len; TYPE_1__* items; } ;
struct TYPE_12__ {int /*<<< orphan*/  n; } ;
struct TYPE_10__ {TYPE_2__* k; } ;

/* Variables and functions */
 TYPE_8__* DICT (TYPE_2__*) ; 
 TYPE_6__* NAME (TYPE_2__*) ; 
 int PDF_FLAGS_SORTED ; 
 TYPE_2__* PDF_LIMIT ; 
 int /*<<< orphan*/ * PDF_NAME_LIST ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pdf_dict_find(fz_context *ctx, pdf_obj *obj, pdf_obj *key)
{
	int len = DICT(obj)->len;
	if ((obj->flags & PDF_FLAGS_SORTED) && len > 0)
	{
		int l = 0;
		int r = len - 1;
		pdf_obj *k = DICT(obj)->items[r].k;

		if (k == key || (k >= PDF_LIMIT && strcmp(NAME(k)->n, PDF_NAME_LIST[(intptr_t)key]) < 0))
		{
			return -1 - (r+1);
		}

		while (l <= r)
		{
			int m = (l + r) >> 1;
			int c;

			k = DICT(obj)->items[m].k;
			c = (k < PDF_LIMIT ? (char *)key-(char *)k : -strcmp(NAME(k)->n, PDF_NAME_LIST[(intptr_t)key]));
			if (c < 0)
				r = m - 1;
			else if (c > 0)
				l = m + 1;
			else
				return m;
		}
		return -1 - l;
	}
	else
	{
		int i;
		for (i = 0; i < len; i++)
		{
			pdf_obj *k = DICT(obj)->items[i].k;
			if (k < PDF_LIMIT)
			{
				if (k == key)
					return i;
			}
			else
			{
				if (!strcmp(PDF_NAME_LIST[(intptr_t)key], NAME(k)->n))
					return i;
			}
		}

		return -1 - len;
	}
}