#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ EMFDRV_PDEVICE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ get_emfdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL emfpathdrv_DeleteDC( PHYSDEV dev )
{
    EMFDRV_PDEVICE *physdev = (EMFDRV_PDEVICE *)get_emfdev( dev );

    physdev->path = FALSE;
    return TRUE;
}