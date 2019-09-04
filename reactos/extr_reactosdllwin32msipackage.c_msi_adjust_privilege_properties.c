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
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int msi_get_property_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  szAdminUser ; 
 int /*<<< orphan*/  szAllUsers ; 
 int /*<<< orphan*/  szOne ; 

void msi_adjust_privilege_properties( MSIPACKAGE *package )
{
    /* FIXME: this should depend on the user's privileges */
    if (msi_get_property_int( package->db, szAllUsers, 0 ) == 2)
    {
        TRACE("resetting ALLUSERS property from 2 to 1\n");
        msi_set_property( package->db, szAllUsers, szOne, -1 );
    }
    msi_set_property( package->db, szAdminUser, szOne, -1 );
}