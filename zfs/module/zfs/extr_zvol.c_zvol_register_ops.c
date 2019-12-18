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
typedef  int /*<<< orphan*/  zvol_platform_ops_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* ops ; 

void
zvol_register_ops(const zvol_platform_ops_t *zvol_ops)
{
	ops = zvol_ops;
}