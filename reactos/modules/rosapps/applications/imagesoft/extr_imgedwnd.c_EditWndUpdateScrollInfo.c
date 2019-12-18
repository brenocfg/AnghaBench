#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int /*<<< orphan*/  hSelf; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_8__ {scalar_t__ bottom; scalar_t__ right; } ;
struct TYPE_7__ {int cbSize; int fMask; int /*<<< orphan*/  nMax; scalar_t__ nPage; scalar_t__ nMin; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__* PEDIT_WND_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int IMAGE_FRAME_SIZE ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int SIF_PAGE ; 
 int SIF_RANGE ; 
 int /*<<< orphan*/  SetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID
EditWndUpdateScrollInfo(PEDIT_WND_INFO Info)
{
    SCROLLINFO si;
    RECT rcClient;

    GetClientRect(Info->hSelf,
                  &rcClient);

    si.cbSize = sizeof(si);
    si.fMask = SIF_PAGE | SIF_RANGE;
    si.nPage = rcClient.right - (2 * IMAGE_FRAME_SIZE);
    si.nMin = 0;
    si.nMax = Info->Width;

    SetScrollInfo(Info->hSelf,
                  SB_HORZ,
                  &si,
                  TRUE);

    si.nPage = rcClient.bottom - (2 * IMAGE_FRAME_SIZE);
    si.nMax = Info->Height;
    SetScrollInfo(Info->hSelf,
                  SB_VERT,
                  &si,
                  TRUE);
}