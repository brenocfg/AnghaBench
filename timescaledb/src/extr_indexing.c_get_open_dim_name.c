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
struct TYPE_4__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_5__ {TYPE_1__ fd; int /*<<< orphan*/ * partitioning; } ;
typedef  TYPE_2__ Dimension ;

/* Variables and functions */
 char* NameStr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_open_dim_name(Dimension *dim)
{
	if (dim == NULL || dim->partitioning != NULL)
		return NULL;

	return NameStr(dim->fd.column_name);
}