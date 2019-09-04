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
typedef  int MSIHANDLE ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MsiCloseHandle (int) ; 
 scalar_t__ MsiOpenPackageA (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static UINT package_from_db(MSIHANDLE hdb, MSIHANDLE *handle)
{
    UINT res;
    CHAR szPackage[12];
    MSIHANDLE hPackage;

    sprintf(szPackage, "#%u", hdb);
    res = MsiOpenPackageA(szPackage, &hPackage);
    if (res != ERROR_SUCCESS)
    {
        MsiCloseHandle(hdb);
        return res;
    }

    res = MsiCloseHandle(hdb);
    if (res != ERROR_SUCCESS)
    {
        MsiCloseHandle(hPackage);
        return res;
    }

    *handle = hPackage;
    return ERROR_SUCCESS;
}