#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int argidx; char* text; } ;
struct TYPE_6__ {int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; int /*<<< orphan*/  type; TYPE_1__ subst; } ;
typedef  TYPE_2__ mtext_t ;
typedef  int /*<<< orphan*/  def_exp_t ;

/* Variables and functions */
 TYPE_2__* pp_xmalloc (int) ; 

__attribute__((used)) static mtext_t *new_mtext(char *str, int idx, def_exp_t type)
{
	mtext_t *mt = pp_xmalloc(sizeof(mtext_t));
	if(!mt)
		return NULL;
	if(str == NULL)
		mt->subst.argidx = idx;
	else
		mt->subst.text = str;
	mt->type = type;
	mt->next = mt->prev = NULL;
	return mt;
}