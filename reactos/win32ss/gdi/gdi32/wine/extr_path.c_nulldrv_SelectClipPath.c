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
struct TYPE_4__ {int /*<<< orphan*/  hdc; } ;
typedef  TYPE_1__* PHYSDEV ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ HRGN ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ ERROR ; 
 scalar_t__ ExtSelectClipRgn (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 scalar_t__ PathToRegion (int /*<<< orphan*/ ) ; 

BOOL nulldrv_SelectClipPath( PHYSDEV dev, INT mode )
{
    BOOL ret = FALSE;
    HRGN hrgn = PathToRegion( dev->hdc );
    DPRINT("nulldrv_SelectClipPath dev %p\n",dev);
    if (hrgn)
    {
        ret = ExtSelectClipRgn( dev->hdc, hrgn, mode ) != ERROR;
        DeleteObject( hrgn );
    }
    return ret;
//    return TRUE;
}