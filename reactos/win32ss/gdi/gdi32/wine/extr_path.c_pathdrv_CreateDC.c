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
struct path_physdev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DEVMODEW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct path_physdev* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  path_driver ; 
 int /*<<< orphan*/  push_dc_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL pathdrv_CreateDC( PHYSDEV *dev, LPCWSTR driver, LPCWSTR device,
                              LPCWSTR output, const DEVMODEW *devmode )
{
    struct path_physdev *physdev = HeapAlloc( GetProcessHeap(), 0, sizeof(*physdev) );
    DPRINT("pathdrv_CreateDC dev %p\n",dev);
    if (!physdev) return FALSE;
    push_dc_driver( dev, &physdev->dev, &path_driver );
    return TRUE;
}