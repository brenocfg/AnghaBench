#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cchBuffer; scalar_t__ pchNext; scalar_t__ pchBuffer; scalar_t__ pchEndRead; scalar_t__ pchEndWrite; int /*<<< orphan*/  lDiskOffset; int /*<<< orphan*/  lBufOffset; } ;
struct TYPE_4__ {int /*<<< orphan*/  bBufferLoaded; TYPE_2__ info; int /*<<< orphan*/  ioProc; } ;
typedef  TYPE_1__* LPWINE_MMIO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MMIOM_READ ; 
 int /*<<< orphan*/  MMIOM_SEEK ; 
 scalar_t__ SEEK_CUR ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ send_message (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG	MMIO_GrabNextBuffer(LPWINE_MMIO wm, int for_read)
{
    LONG	size = wm->info.cchBuffer;

    TRACE("bo=%x do=%x of=%lx\n",
	  wm->info.lBufOffset, wm->info.lDiskOffset,
	  send_message(wm->ioProc, &wm->info, MMIOM_SEEK, 0, SEEK_CUR, FALSE));

    wm->info.lBufOffset = wm->info.lDiskOffset;
    wm->info.pchNext = wm->info.pchBuffer;
    wm->info.pchEndRead = wm->info.pchBuffer;
    wm->info.pchEndWrite = wm->info.pchBuffer + wm->info.cchBuffer;

    wm->bBufferLoaded = TRUE;
    if (for_read) {
	size = send_message(wm->ioProc, &wm->info, MMIOM_READ,
                            (LPARAM)wm->info.pchBuffer, size, FALSE);
	if (size > 0)
	    wm->info.pchEndRead += size;
        else
            wm->bBufferLoaded = FALSE;
    }

    return size;
}