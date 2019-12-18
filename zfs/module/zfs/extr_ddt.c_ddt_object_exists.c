#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
struct TYPE_3__ {int /*<<< orphan*/ ** ddt_object; } ;
typedef  TYPE_1__ ddt_t ;
typedef  int boolean_t ;

/* Variables and functions */

boolean_t
ddt_object_exists(ddt_t *ddt, enum ddt_type type, enum ddt_class class)
{
	return (!!ddt->ddt_object[type][class]);
}