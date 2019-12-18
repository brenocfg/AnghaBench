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
typedef  enum attr_type { ____Placeholder_attr_type } attr_type ;
struct TYPE_5__ {void* pval; } ;
struct TYPE_6__ {int type; TYPE_1__ u; } ;
typedef  TYPE_2__ attr_t ;

/* Variables and functions */
 TYPE_2__* xmalloc (int) ; 

__attribute__((used)) static attr_t *make_attrp(enum attr_type type, void *val)
{
  attr_t *a = xmalloc(sizeof(attr_t));
  a->type = type;
  a->u.pval = val;
  return a;
}