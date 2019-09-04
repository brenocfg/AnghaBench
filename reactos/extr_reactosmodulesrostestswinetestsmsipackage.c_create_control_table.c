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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ run_query (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static UINT create_control_table( MSIHANDLE hdb )
{
    UINT r = run_query(hdb,
            "CREATE TABLE `Control` ("
            "`Dialog_` CHAR(72) NOT NULL, "
            "`Control` CHAR(50) NOT NULL, "
            "`Type` CHAR(20) NOT NULL, "
            "`X` SHORT NOT NULL, "
            "`Y` SHORT NOT NULL, "
            "`Width` SHORT NOT NULL, "
            "`Height` SHORT NOT NULL, "
            "`Attributes` LONG, "
            "`Property` CHAR(50), "
            "`Text` CHAR(0) LOCALIZABLE, "
            "`Control_Next` CHAR(50), "
            "`Help` CHAR(255) LOCALIZABLE "
            "PRIMARY KEY `Dialog_`, `Control`)");
    ok(r == ERROR_SUCCESS, "Failed to create Control table: %u\n", r);
    return r;
}