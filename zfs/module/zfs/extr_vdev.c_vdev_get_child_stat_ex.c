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
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_4__ {scalar_t__** vsx_agg_histo; scalar_t__** vsx_ind_histo; scalar_t__* vsx_pend_queue; scalar_t__* vsx_active_queue; scalar_t__** vsx_queue_histo; scalar_t__** vsx_total_histo; scalar_t__** vsx_disk_histo; } ;
typedef  TYPE_1__ vdev_stat_ex_t ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int ZIO_PRIORITY_NUM_QUEUEABLE ; 
 int ZIO_TYPES ; 

__attribute__((used)) static void
vdev_get_child_stat_ex(vdev_t *cvd, vdev_stat_ex_t *vsx, vdev_stat_ex_t *cvsx)
{
	int t, b;
	for (t = 0; t < ZIO_TYPES; t++) {
		for (b = 0; b < ARRAY_SIZE(vsx->vsx_disk_histo[0]); b++)
			vsx->vsx_disk_histo[t][b] += cvsx->vsx_disk_histo[t][b];

		for (b = 0; b < ARRAY_SIZE(vsx->vsx_total_histo[0]); b++) {
			vsx->vsx_total_histo[t][b] +=
			    cvsx->vsx_total_histo[t][b];
		}
	}

	for (t = 0; t < ZIO_PRIORITY_NUM_QUEUEABLE; t++) {
		for (b = 0; b < ARRAY_SIZE(vsx->vsx_queue_histo[0]); b++) {
			vsx->vsx_queue_histo[t][b] +=
			    cvsx->vsx_queue_histo[t][b];
		}
		vsx->vsx_active_queue[t] += cvsx->vsx_active_queue[t];
		vsx->vsx_pend_queue[t] += cvsx->vsx_pend_queue[t];

		for (b = 0; b < ARRAY_SIZE(vsx->vsx_ind_histo[0]); b++)
			vsx->vsx_ind_histo[t][b] += cvsx->vsx_ind_histo[t][b];

		for (b = 0; b < ARRAY_SIZE(vsx->vsx_agg_histo[0]); b++)
			vsx->vsx_agg_histo[t][b] += cvsx->vsx_agg_histo[t][b];
	}

}