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
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int zio_handle_device_injection_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
zio_handle_device_injection(vdev_t *vd, zio_t *zio, int error)
{
	return (zio_handle_device_injection_impl(vd, zio, error, INT_MAX));
}