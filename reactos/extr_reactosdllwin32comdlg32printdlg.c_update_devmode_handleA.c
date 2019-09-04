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
struct TYPE_4__ {scalar_t__ dmSize; scalar_t__ dmDriverExtra; } ;
typedef  scalar_t__ SIZE_T ;
typedef  scalar_t__ LPVOID ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  TYPE_1__ DEVMODEA ;

/* Variables and functions */
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/ * GlobalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GlobalReAlloc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GlobalSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static HGLOBAL update_devmode_handleA(HGLOBAL hdm, DEVMODEA *dm)
{
    SIZE_T size = GlobalSize(hdm);
    LPVOID ptr;

    /* Increase / alloc the global memory block, when needed */
    if ((dm->dmSize + dm->dmDriverExtra) > size) {
        if (hdm)
            hdm = GlobalReAlloc(hdm, dm->dmSize + dm->dmDriverExtra, 0);
        else
            hdm = GlobalAlloc(GMEM_MOVEABLE, dm->dmSize + dm->dmDriverExtra);
    }

    if (hdm) {
        ptr = GlobalLock(hdm);
        if (ptr) {
            memcpy(ptr, dm, dm->dmSize + dm->dmDriverExtra);
            GlobalUnlock(hdm);
        }
        else
        {
            GlobalFree(hdm);
            hdm = NULL;
        }
    }
    return hdm;
}