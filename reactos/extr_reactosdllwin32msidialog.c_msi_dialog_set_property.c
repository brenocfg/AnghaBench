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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  msi_reset_folders (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szSourceDir ; 

__attribute__((used)) static void msi_dialog_set_property( MSIPACKAGE *package, LPCWSTR property, LPCWSTR value )
{
    UINT r = msi_set_property( package->db, property, value, -1 );
    if (r == ERROR_SUCCESS && !strcmpW( property, szSourceDir ))
        msi_reset_folders( package, TRUE );
}