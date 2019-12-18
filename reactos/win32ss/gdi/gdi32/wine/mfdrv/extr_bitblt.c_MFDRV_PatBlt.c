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
struct bitblt_coords {int /*<<< orphan*/  log_height; int /*<<< orphan*/  log_width; int /*<<< orphan*/  log_y; int /*<<< orphan*/  log_x; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  META_PATBLT ; 
 int /*<<< orphan*/  MFDRV_MetaParam6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL MFDRV_PatBlt( PHYSDEV dev, struct bitblt_coords *dst, DWORD rop )
{
    MFDRV_MetaParam6( dev, META_PATBLT, dst->log_x, dst->log_y, dst->log_width, dst->log_height,
                      HIWORD(rop), LOWORD(rop) );
    return TRUE;
}