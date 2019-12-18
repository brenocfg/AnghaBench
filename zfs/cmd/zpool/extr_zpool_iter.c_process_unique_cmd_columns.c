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
struct TYPE_4__ {int cols_cnt; char** cols; char** lines; } ;
typedef  TYPE_1__ vdev_cmd_data_t ;
struct TYPE_5__ {int count; char** uniq_cols; int uniq_cols_cnt; int* uniq_cols_width; TYPE_1__* data; } ;
typedef  TYPE_2__ vdev_cmd_data_list_t ;

/* Variables and functions */
 int MAX (int,int) ; 
 char** realloc (char**,int) ; 
 int* safe_malloc (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
process_unique_cmd_columns(vdev_cmd_data_list_t *vcdl)
{
	char **uniq_cols = NULL, **tmp = NULL;
	int *uniq_cols_width;
	vdev_cmd_data_t *data;
	int cnt = 0;
	int k;

	/* For each vdev */
	for (int i = 0; i < vcdl->count; i++) {
		data = &vcdl->data[i];
		/* For each column the vdev reported */
		for (int j = 0; j < data->cols_cnt; j++) {
			/* Is this column in our list of unique column names? */
			for (k = 0; k < cnt; k++) {
				if (strcmp(data->cols[j], uniq_cols[k]) == 0)
					break; /* yes it is */
			}
			if (k == cnt) {
				/* No entry for column, add to list */
				tmp = realloc(uniq_cols, sizeof (*uniq_cols) *
				    (cnt + 1));
				if (tmp == NULL)
					break; /* Nothing we can do... */
				uniq_cols = tmp;
				uniq_cols[cnt] = data->cols[j];
				cnt++;
			}
		}
	}

	/*
	 * We now have a list of all the unique column names.  Figure out the
	 * max width of each column by looking at the column name and all its
	 * values.
	 */
	uniq_cols_width = safe_malloc(sizeof (*uniq_cols_width) * cnt);
	for (int i = 0; i < cnt; i++) {
		/* Start off with the column title's width */
		uniq_cols_width[i] = strlen(uniq_cols[i]);
		/* For each vdev */
		for (int j = 0; j < vcdl->count; j++) {
			/* For each of the vdev's values in a column */
			data = &vcdl->data[j];
			for (k = 0; k < data->cols_cnt; k++) {
				/* Does this vdev have a value for this col? */
				if (strcmp(data->cols[k], uniq_cols[i]) == 0) {
					/* Is the value width larger? */
					uniq_cols_width[i] =
					    MAX(uniq_cols_width[i],
					    strlen(data->lines[k]));
				}
			}
		}
	}

	vcdl->uniq_cols = uniq_cols;
	vcdl->uniq_cols_cnt = cnt;
	vcdl->uniq_cols_width = uniq_cols_width;
}