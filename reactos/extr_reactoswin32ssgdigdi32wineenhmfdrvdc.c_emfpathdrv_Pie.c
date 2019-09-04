#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* funcs; } ;
struct TYPE_10__ {scalar_t__ (* pPie ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* PHYSDEV ;
typedef  int /*<<< orphan*/  INT ;
typedef  int BOOL ;

/* Variables and functions */
 TYPE_2__* GET_NEXT_PHYSDEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_emfdev (TYPE_2__*) ; 
 int /*<<< orphan*/  pPie ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL emfpathdrv_Pie( PHYSDEV dev, INT left, INT top, INT right, INT bottom,
                            INT xstart, INT ystart, INT xend, INT yend )
{
    PHYSDEV emfdev = get_emfdev( dev );
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pPie );

    return (emfdev->funcs->pPie( emfdev, left, top, right, bottom, xstart, ystart, xend, yend ) &&
            next->funcs->pPie( next, left, top, right, bottom, xstart, ystart, xend, yend ));
}