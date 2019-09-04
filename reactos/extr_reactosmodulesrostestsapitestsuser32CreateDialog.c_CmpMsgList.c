#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int msgCount; TYPE_1__* msgList; } ;
typedef  TYPE_2__ tagMsgList ;
struct TYPE_6__ {scalar_t__ DlgProc; scalar_t__ msg; int cmpflag; scalar_t__ wParam; scalar_t__ lParam; scalar_t__ result; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DumpMsgList (char*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  FALSE ; 
 int MSGLST_CMP_LP ; 
 int MSGLST_CMP_RES ; 
 int MSGLST_CMP_WP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 

BOOL CmpMsgList(const tagMsgList *recvd,
                const tagMsgList *expect)
{
    int i1;
    BOOL isOk;

    isOk = TRUE;
    if (recvd->msgCount != expect->msgCount)
    {
        ok(FALSE, "%d messages expected, %d messages received!\n",
           expect->msgCount, recvd->msgCount);
        isOk = FALSE;
    }
    else
    {
        for (i1 = 0; i1 < recvd->msgCount; i1++)
        {
            if (expect->msgList[i1].DlgProc != recvd->msgList[i1].DlgProc)
                isOk = FALSE;
            if (expect->msgList[i1].msg != recvd->msgList[i1].msg)
                isOk = FALSE;
            if ((expect->msgList[i1].cmpflag & MSGLST_CMP_WP) &&
                (expect->msgList[i1].wParam != recvd->msgList[i1].wParam))
                isOk = FALSE;
            if ((expect->msgList[i1].cmpflag & MSGLST_CMP_LP) &&
                (expect->msgList[i1].lParam != recvd->msgList[i1].lParam))
                isOk = FALSE;
            if ((expect->msgList[i1].cmpflag & MSGLST_CMP_RES) &&
                (expect->msgList[i1].result != recvd->msgList[i1].result))
                isOk = FALSE;
            if (!isOk)
            {
                ok(FALSE, "Message #%.3d not equal\n", i1);
                break;
            }
        }
    }

    if (!isOk)
    {
        DumpMsgList("RECEIVED", recvd);
        DumpMsgList("EXPECTED", expect);
        return FALSE;
    }

    ok(TRUE, "\n");
    return TRUE;
}