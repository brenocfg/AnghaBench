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
struct TYPE_10__ {scalar_t__ (* pPolyDraw ) (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_2__* PHYSDEV ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 TYPE_2__* GET_NEXT_PHYSDEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_emfdev (TYPE_2__*) ; 
 int /*<<< orphan*/  pPolyDraw ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL emfpathdrv_PolyDraw( PHYSDEV dev, const POINT *pts, const BYTE *types, DWORD count )
{
    PHYSDEV emfdev = get_emfdev( dev );
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pPolyDraw );

    return (emfdev->funcs->pPolyDraw( emfdev, pts, types, count ) &&
            next->funcs->pPolyDraw( next, pts, types, count ));
}