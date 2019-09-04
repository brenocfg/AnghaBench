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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  db; int /*<<< orphan*/  ProductCode; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_MACHINE ; 
 int /*<<< orphan*/  MSIINSTALLCONTEXT_USERUNMANAGED ; 
 int msi_get_property_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_locate_product (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szAllUsers ; 

UINT msi_set_context(MSIPACKAGE *package)
{
    UINT r = msi_locate_product( package->ProductCode, &package->Context );
    if (r != ERROR_SUCCESS)
    {
        int num = msi_get_property_int( package->db, szAllUsers, 0 );
        if (num == 1 || num == 2)
            package->Context = MSIINSTALLCONTEXT_MACHINE;
        else
            package->Context = MSIINSTALLCONTEXT_USERUNMANAGED;
    }
    return ERROR_SUCCESS;
}