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
struct TYPE_3__ {int /*<<< orphan*/  (* pDeleteDC ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  DC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * get_physdev_dc (int /*<<< orphan*/ ) ; 
 TYPE_1__ path_driver ; 
 int /*<<< orphan*/  pop_dc_driver (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL pathdrv_AbortPath( PHYSDEV dev )
{
    DC *dc = get_physdev_dc( dev );
    DPRINT("pathdrv_AbortPath dev %p\n",dev);
    path_driver.pDeleteDC( pop_dc_driver( dc, &path_driver ));
    return TRUE;
}