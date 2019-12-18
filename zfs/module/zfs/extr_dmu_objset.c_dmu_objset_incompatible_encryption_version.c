#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* os_dsl_dataset; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  ds_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_dir_incompatible_encryption_version (int /*<<< orphan*/ ) ; 

boolean_t
dmu_objset_incompatible_encryption_version(objset_t *os)
{
	return (dsl_dir_incompatible_encryption_version(
	    os->os_dsl_dataset->ds_dir));
}