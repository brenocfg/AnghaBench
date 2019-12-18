#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ VDEV_AUX_OPEN_FAILED ; 
 scalar_t__ VDEV_STATE_CANT_OPEN ; 

__attribute__((used)) static int
vdev_missing(uint64_t state, uint64_t aux, uint64_t errs)
{
	return (state == VDEV_STATE_CANT_OPEN &&
	    aux == VDEV_AUX_OPEN_FAILED);
}