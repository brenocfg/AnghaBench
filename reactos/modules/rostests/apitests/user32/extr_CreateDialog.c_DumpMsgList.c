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
struct TYPE_5__ {int msgCount; TYPE_1__* msgList; } ;
typedef  TYPE_2__ tagMsgList ;
struct TYPE_4__ {int msg; int /*<<< orphan*/  result; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; scalar_t__ DlgProc; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void DumpMsgList(const char* lstName, const tagMsgList *ml)
{
    const char *dlgProcName;
    int i1;

    printf("%s\n", lstName);
    for (i1 = 0; i1 < ml->msgCount; i1++)
    {
        dlgProcName = (ml->msgList[i1].DlgProc)  ? "DlgProc" : "WndProc";
        printf("#%.3d %s, msg 0x%x, wParam 0x%Ix, lParam 0x%Ix, result %d\n",
               i1,
               dlgProcName,
               ml->msgList[i1].msg,
               ml->msgList[i1].wParam,
               ml->msgList[i1].lParam,
               ml->msgList[i1].result);
    }
}