#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* pDeleteDC ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_1__* funcs; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* pAbortPath ) (TYPE_2__*) ;} ;
typedef  TYPE_2__* PHYSDEV ;
typedef  int /*<<< orphan*/  DC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_2__* GET_NEXT_PHYSDEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ emfpath_driver ; 
 TYPE_2__* get_emfdev (TYPE_2__*) ; 
 int /*<<< orphan*/ * get_physdev_dc (TYPE_2__*) ; 
 int /*<<< orphan*/  pAbortPath ; 
 int /*<<< orphan*/  pop_dc_driver (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

__attribute__((used)) static BOOL emfpathdrv_AbortPath( PHYSDEV dev )
{
    PHYSDEV emfdev = get_emfdev( dev );
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pAbortPath );
    DC *dc = get_physdev_dc( dev );

    emfpath_driver.pDeleteDC( pop_dc_driver( dc, &emfpath_driver ));
    emfdev->funcs->pAbortPath( emfdev );
    return next->funcs->pAbortPath( next );
}