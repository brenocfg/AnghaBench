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
struct TYPE_4__ {char* arg; scalar_t__ nnl; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ marg_t ;
typedef  int /*<<< orphan*/  def_arg_t ;

/* Variables and functions */
 TYPE_1__* pp_xmalloc (int) ; 

__attribute__((used)) static marg_t *new_marg(char *str, def_arg_t type)
{
	marg_t *ma = pp_xmalloc(sizeof(marg_t));
	if(!ma)
		return NULL;
	ma->arg = str;
	ma->type = type;
	ma->nnl = 0;
	return ma;
}