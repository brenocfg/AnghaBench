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
struct TYPE_4__ {char* pi_name; scalar_t__ pi_value; } ;
typedef  TYPE_1__ zprop_index_t ;
struct TYPE_5__ {TYPE_1__* pd_table; } ;
typedef  TYPE_2__ zprop_desc_t ;
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ZPROP_CONT ; 
 int ZPROP_INVAL ; 
 int zprop_get_numprops (int /*<<< orphan*/ ) ; 
 TYPE_2__* zprop_get_proptable (int /*<<< orphan*/ ) ; 

int
zprop_index_to_string(int prop, uint64_t index, const char **string,
    zfs_type_t type)
{
	zprop_desc_t *prop_tbl;
	const zprop_index_t *idx_tbl;
	int i;

	if (prop == ZPROP_INVAL || prop == ZPROP_CONT)
		return (-1);

	ASSERT(prop < zprop_get_numprops(type));
	prop_tbl = zprop_get_proptable(type);
	if ((idx_tbl = prop_tbl[prop].pd_table) == NULL)
		return (-1);

	for (i = 0; idx_tbl[i].pi_name != NULL; i++) {
		if (idx_tbl[i].pi_value == index) {
			*string = idx_tbl[i].pi_name;
			return (0);
		}
	}

	return (-1);
}