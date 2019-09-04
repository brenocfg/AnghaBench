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
struct TYPE_2__ {scalar_t__ lItemlParam; scalar_t__ uItemState; scalar_t__ dwItemSpec; int /*<<< orphan*/  rc; int /*<<< orphan*/  hdc; int /*<<< orphan*/  dwDrawStage; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  TYPE_1__ NMCUSTOMDRAW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_SendNotify (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NM_CUSTOMDRAW ; 

__attribute__((used)) static LRESULT
HEADER_SendCtrlCustomDraw(const HEADER_INFO *infoPtr, DWORD dwDrawStage, HDC hdc, const RECT *rect)
{
    NMCUSTOMDRAW nm;
    nm.dwDrawStage = dwDrawStage;
    nm.hdc = hdc;
    nm.rc = *rect;
    nm.dwItemSpec = 0;
    nm.uItemState = 0;
    nm.lItemlParam = 0;

    return HEADER_SendNotify(infoPtr, NM_CUSTOMDRAW, (NMHDR *)&nm);
}