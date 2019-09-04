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
struct xsave_limits {int dummy; } ;

/* Variables and functions */
 struct xsave_limits const vmm_xsave_limits ; 

const struct xsave_limits *
vmm_get_xsave_limits(void)
{
	return (&vmm_xsave_limits);
}