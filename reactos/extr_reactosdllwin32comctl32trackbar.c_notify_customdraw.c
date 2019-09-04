#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  idFrom; } ;
struct TYPE_8__ {int dwDrawStage; TYPE_1__ hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  hwndNotify; } ;
typedef  TYPE_2__ TRACKBAR_INFO ;
typedef  TYPE_3__ NMCUSTOMDRAW ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static inline int 
notify_customdraw (const TRACKBAR_INFO *infoPtr, NMCUSTOMDRAW *pnmcd, int stage)
{
    pnmcd->dwDrawStage = stage;
    return SendMessageW (infoPtr->hwndNotify, WM_NOTIFY, 
		         pnmcd->hdr.idFrom, (LPARAM)pnmcd);
}