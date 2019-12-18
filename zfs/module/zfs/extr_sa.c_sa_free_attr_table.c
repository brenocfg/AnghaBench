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
struct TYPE_5__ {int sa_num_attrs; TYPE_2__* sa_attr_table; } ;
typedef  TYPE_1__ sa_os_t ;
typedef  int /*<<< orphan*/  sa_attr_table_t ;
struct TYPE_6__ {struct TYPE_6__* sa_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int strlen (TYPE_2__*) ; 

__attribute__((used)) static void
sa_free_attr_table(sa_os_t *sa)
{
	int i;

	if (sa->sa_attr_table == NULL)
		return;

	for (i = 0; i != sa->sa_num_attrs; i++) {
		if (sa->sa_attr_table[i].sa_name)
			kmem_free(sa->sa_attr_table[i].sa_name,
			    strlen(sa->sa_attr_table[i].sa_name) + 1);
	}

	kmem_free(sa->sa_attr_table,
	    sizeof (sa_attr_table_t) * sa->sa_num_attrs);

	sa->sa_attr_table = NULL;
}