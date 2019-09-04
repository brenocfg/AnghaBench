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
struct TYPE_3__ {int /*<<< orphan*/  dvMaxZ; int /*<<< orphan*/  dvMinZ; int /*<<< orphan*/  dvMaxY; int /*<<< orphan*/  dvMaxX; int /*<<< orphan*/  dvScaleY; int /*<<< orphan*/  dvScaleX; int /*<<< orphan*/  dwHeight; int /*<<< orphan*/  dwWidth; int /*<<< orphan*/  dwY; int /*<<< orphan*/  dwX; int /*<<< orphan*/  dwSize; } ;
typedef  TYPE_1__ D3DVIEWPORT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void _dump_D3DVIEWPORT(const D3DVIEWPORT *lpvp)
{
    TRACE("    - dwSize = %d   dwX = %d   dwY = %d\n",
            lpvp->dwSize, lpvp->dwX, lpvp->dwY);
    TRACE("    - dwWidth = %d   dwHeight = %d\n",
            lpvp->dwWidth, lpvp->dwHeight);
    TRACE("    - dvScaleX = %f   dvScaleY = %f\n",
            lpvp->dvScaleX, lpvp->dvScaleY);
    TRACE("    - dvMaxX = %f   dvMaxY = %f\n",
            lpvp->dvMaxX, lpvp->dvMaxY);
    TRACE("    - dvMinZ = %f   dvMaxZ = %f\n",
            lpvp->dvMinZ, lpvp->dvMaxZ);
}