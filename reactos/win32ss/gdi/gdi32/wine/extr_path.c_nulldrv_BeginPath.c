#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct path_physdev {int /*<<< orphan*/  HasPathHook; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* pCreateDC ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  physDev; } ;
typedef  struct path_physdev* PHYSDEV ;
typedef  TYPE_1__ DC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,struct path_physdev*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  find_dc_driver (TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* get_nulldrv_dc (struct path_physdev*) ; 
 struct path_physdev* get_path_physdev (int /*<<< orphan*/ ) ; 
 TYPE_2__ path_driver ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL nulldrv_BeginPath( PHYSDEV dev )
{
    DC *dc = get_nulldrv_dc( dev );
    struct path_physdev *physdev;

    if (!path_driver.pCreateDC( &dc->physDev, NULL, NULL, NULL, NULL ))
    {
        return FALSE;
    }
    physdev = get_path_physdev( find_dc_driver( dc, &path_driver ));
    physdev->HasPathHook = TRUE;
    DPRINT("nulldrv_BeginPath dev %p\n",dev);
    DPRINT("nulldrv_BeginPath pd %p\n",physdev);
    return TRUE;
}