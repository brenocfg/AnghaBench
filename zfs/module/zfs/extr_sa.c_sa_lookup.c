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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  sa_lock; } ;
typedef  TYPE_1__ sa_handle_t ;
typedef  int /*<<< orphan*/  sa_attr_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int sa_lookup_locked (TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int
sa_lookup(sa_handle_t *hdl, sa_attr_type_t attr, void *buf, uint32_t buflen)
{
	int error;

	mutex_enter(&hdl->sa_lock);
	error = sa_lookup_locked(hdl, attr, buf, buflen);
	mutex_exit(&hdl->sa_lock);

	return (error);
}