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
struct TYPE_4__ {int dwSize; int /*<<< orphan*/ * lpDDSurfaceDesc; } ;
typedef  int /*<<< orphan*/ * PDD_CANCREATESURFACEDATA ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_1__ DDSURFACEDESC2 ;
typedef  int /*<<< orphan*/  DDSURFACEDESC ;
typedef  TYPE_1__ DDHAL_CANCREATESURFACEDATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DDHAL_DRIVER_HANDLED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OsThunkDdCanCreateSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  testing_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

void
test_NtGdiDdCanCreateSurface(HANDLE hDirectDrawLocal)
{
    int fails=0;
    BOOL retValue=FALSE;
    DDHAL_CANCREATESURFACEDATA pCanCreateSurface;
    DDSURFACEDESC2 desc;

    RtlZeroMemory(&pCanCreateSurface,sizeof(DDHAL_CANCREATESURFACEDATA));
    RtlZeroMemory(&desc,sizeof(DDSURFACEDESC2));

    /* crash in windows 2000 */
    retValue = OsThunkDdCanCreateSurface(NULL,NULL);
    testing_eq(retValue, DDHAL_DRIVER_HANDLED,fails,"1. NtGdiDdCanCreateSurface(NULL,NULL);\0");

    retValue = OsThunkDdCanCreateSurface(hDirectDrawLocal,NULL);
    testing_eq(retValue, DDHAL_DRIVER_HANDLED,fails,"2. NtGdiDdCanCreateSurface(hDirectDrawLocal,NULL);\0");

    retValue = OsThunkDdCanCreateSurface(hDirectDrawLocal,(PDD_CANCREATESURFACEDATA)&pCanCreateSurface);
    testing_eq(retValue, DDHAL_DRIVER_HANDLED,fails,"3. NtGdiDdCanCreateSurface(hDirectDrawLocal,pCanCreateSurface);\0");

    pCanCreateSurface.lpDDSurfaceDesc = (DDSURFACEDESC*)&desc;
    desc.dwSize = sizeof(DDSURFACEDESC2);

    retValue = OsThunkDdCanCreateSurface(hDirectDrawLocal,(PDD_CANCREATESURFACEDATA)&pCanCreateSurface);
    testing_eq(retValue, DDHAL_DRIVER_HANDLED,fails,"4. NtGdiDdCanCreateSurface(hDirectDrawLocal,pCanCreateSurface);\0");

}