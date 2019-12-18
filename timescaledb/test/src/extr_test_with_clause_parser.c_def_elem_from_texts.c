#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* defnamespace; void* defname; int /*<<< orphan*/ * arg; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ DefElem ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetTextP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ makeString (void*) ; 
 TYPE_1__* palloc0 (int) ; 
 void* text_to_cstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DefElem *
def_elem_from_texts(Datum *texts, int nelems)
{
	DefElem *elem = palloc0(sizeof(*elem));
	switch (nelems)
	{
		case 1:
			elem->defname = text_to_cstring(DatumGetTextP(texts[0]));
			break;
		case 3:
			elem->arg = (Node *) makeString(text_to_cstring(DatumGetTextP(texts[2])));
			/* FALLTHROUGH */
		case 2:
			elem->defname = text_to_cstring(DatumGetTextP(texts[1]));
			elem->defnamespace = text_to_cstring(DatumGetTextP(texts[0]));
			break;
		default:
			elog(ERROR, "%d elements invalid for defelem", nelems);
	}
	return elem;
}