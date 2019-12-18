#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ vdev_state; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  VDEV_LABEL_CREATE ; 
 int /*<<< orphan*/  VDEV_LABEL_REPLACE ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 int /*<<< orphan*/  vdev_close (TYPE_1__*) ; 
 int vdev_dtl_load (TYPE_1__*) ; 
 int vdev_label_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vdev_open (TYPE_1__*) ; 

int
vdev_create(vdev_t *vd, uint64_t txg, boolean_t isreplacing)
{
	int error;

	/*
	 * Normally, partial opens (e.g. of a mirror) are allowed.
	 * For a create, however, we want to fail the request if
	 * there are any components we can't open.
	 */
	error = vdev_open(vd);

	if (error || vd->vdev_state != VDEV_STATE_HEALTHY) {
		vdev_close(vd);
		return (error ? error : ENXIO);
	}

	/*
	 * Recursively load DTLs and initialize all labels.
	 */
	if ((error = vdev_dtl_load(vd)) != 0 ||
	    (error = vdev_label_init(vd, txg, isreplacing ?
	    VDEV_LABEL_REPLACE : VDEV_LABEL_CREATE)) != 0) {
		vdev_close(vd);
		return (error);
	}

	return (0);
}