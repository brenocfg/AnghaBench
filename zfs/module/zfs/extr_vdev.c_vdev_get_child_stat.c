#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vdev_removing; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_7__ {int /*<<< orphan*/  vs_scan_removing; scalar_t__* vs_bytes; scalar_t__* vs_ops; } ;
typedef  TYPE_2__ vdev_stat_t ;

/* Variables and functions */
 int VS_ZIO_TYPES ; 

__attribute__((used)) static void
vdev_get_child_stat(vdev_t *cvd, vdev_stat_t *vs, vdev_stat_t *cvs)
{
	for (int t = 0; t < VS_ZIO_TYPES; t++) {
		vs->vs_ops[t] += cvs->vs_ops[t];
		vs->vs_bytes[t] += cvs->vs_bytes[t];
	}

	cvs->vs_scan_removing = cvd->vdev_removing;
}