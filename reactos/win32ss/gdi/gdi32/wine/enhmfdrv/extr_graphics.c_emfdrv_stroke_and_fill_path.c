#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gdi_path {int dummy; } ;
typedef  int /*<<< orphan*/  emr ;
struct TYPE_4__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_3__ {int /*<<< orphan*/  rclBounds; TYPE_2__ emr; } ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ EMRSTROKEANDFILLPATH ;
typedef  int /*<<< orphan*/  DC ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_UpdateBBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  empty_bounds ; 
 int /*<<< orphan*/  free_gdi_path (struct gdi_path*) ; 
 struct gdi_path* get_gdi_flat_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_gdi_path_data (struct gdi_path*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * get_physdev_dc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_points_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL emfdrv_stroke_and_fill_path( PHYSDEV dev, INT type )
{
    DC *dc = get_physdev_dc( dev );
    EMRSTROKEANDFILLPATH emr;
    struct gdi_path *path;
    POINT *points;
    BYTE *flags;

    emr.emr.iType = type;
    emr.emr.nSize = sizeof(emr);

    if ((path = get_gdi_flat_path( dc, NULL )))
    {
        int count = get_gdi_path_data( path, &points, &flags );
        get_points_bounds( &emr.rclBounds, points, count, 0 );
        free_gdi_path( path );
    }
    else emr.rclBounds = empty_bounds;

    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return FALSE;
    if (!path) return FALSE;
    EMFDRV_UpdateBBox( dev, &emr.rclBounds );
    return TRUE;
}