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
typedef  int /*<<< orphan*/  sa_share_t ;
typedef  scalar_t__ sa_handle_t ;
typedef  int /*<<< orphan*/  sa_handle_impl_t ;

/* Variables and functions */
 scalar_t__ find_share (int /*<<< orphan*/ ,char*) ; 

sa_share_t
sa_find_share(sa_handle_t handle, char *sharepath)
{
	return ((sa_share_t)find_share((sa_handle_impl_t)handle, sharepath));
}