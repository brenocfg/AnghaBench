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
struct TYPE_4__ {scalar_t__ dwItemSpec; int /*<<< orphan*/  hdr; int /*<<< orphan*/  dwDrawStage; } ;
struct TYPE_5__ {TYPE_1__ nmcd; scalar_t__ iSubItem; } ;
typedef  TYPE_2__ NMLVCUSTOMDRAW ;
typedef  int /*<<< orphan*/  LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDDS_ITEM ; 
 int /*<<< orphan*/  CDDS_SUBITEM ; 
 int /*<<< orphan*/  NM_CUSTOMDRAW ; 
 int /*<<< orphan*/  notify_hdr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline DWORD notify_customdraw (const LISTVIEW_INFO *infoPtr, DWORD dwDrawStage, NMLVCUSTOMDRAW *lpnmlvcd)
{
    BOOL isForItem = (lpnmlvcd->nmcd.dwItemSpec != 0);
    DWORD result;

    lpnmlvcd->nmcd.dwDrawStage = dwDrawStage;
    if (isForItem) lpnmlvcd->nmcd.dwDrawStage |= CDDS_ITEM; 
    if (lpnmlvcd->iSubItem) lpnmlvcd->nmcd.dwDrawStage |= CDDS_SUBITEM;
    if (isForItem) lpnmlvcd->nmcd.dwItemSpec--;
    result = notify_hdr(infoPtr, NM_CUSTOMDRAW, &lpnmlvcd->nmcd.hdr);
    if (isForItem) lpnmlvcd->nmcd.dwItemSpec++;
    return result;
}