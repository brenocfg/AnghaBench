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
struct TYPE_4__ {int cols_cnt; char** lines; int lines_cnt; int /*<<< orphan*/ * cols; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ vdev_cmd_data_t ;
struct TYPE_5__ {int count; int uniq_cols_cnt; char const** uniq_cols; char** uniq_cols_width; TYPE_1__* data; } ;
typedef  TYPE_2__ vdev_cmd_data_list_t ;

/* Variables and functions */
 scalar_t__ is_blank_str (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
zpool_print_cmd(vdev_cmd_data_list_t *vcdl, const char *pool, char *path)
{
	vdev_cmd_data_t *data;
	int i, j;
	char *val;

	for (i = 0; i < vcdl->count; i++) {
		if ((strcmp(vcdl->data[i].path, path) != 0) ||
		    (strcmp(vcdl->data[i].pool, pool) != 0)) {
			/* Not the vdev we're looking for */
			continue;
		}

		data = &vcdl->data[i];
		/* Print out all the output values for this vdev */
		for (j = 0; j < vcdl->uniq_cols_cnt; j++) {
			val = NULL;
			/* Does this vdev have values for this column? */
			for (int k = 0; k < data->cols_cnt; k++) {
				if (strcmp(data->cols[k],
				    vcdl->uniq_cols[j]) == 0) {
					/* yes it does, record the value */
					val = data->lines[k];
					break;
				}
			}
			/*
			 * Mark empty values with dashes to make output
			 * awk-able.
			 */
			if (is_blank_str(val))
				val = "-";

			printf("%*s", vcdl->uniq_cols_width[j], val);
			if (j < vcdl->uniq_cols_cnt - 1)
				printf("  ");
		}

		/* Print out any values that aren't in a column at the end */
		for (j = data->cols_cnt; j < data->lines_cnt; j++) {
			/* Did we have any columns?  If so print a spacer. */
			if (vcdl->uniq_cols_cnt > 0)
				printf("  ");

			val = data->lines[j];
			printf("%s", val ? val : "");
		}
		break;
	}
}