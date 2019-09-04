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
struct pending_message {int /*<<< orphan*/  entry; scalar_t__ msg; } ;
typedef  int /*<<< orphan*/  pTW_IDENTITY ;
struct TYPE_3__ {scalar_t__ ui_window; scalar_t__ event_window; int /*<<< orphan*/  pending_messages; } ;
typedef  TYPE_1__ activeDS ;
typedef  scalar_t__ TW_UINT16 ;
typedef  int /*<<< orphan*/  TW_MEMREF ;

/* Variables and functions */
 scalar_t__ DSM_parent ; 
 int /*<<< orphan*/  DSM_twCC ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct pending_message* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MSG_CLOSEDSREQ ; 
 scalar_t__ MSG_DEVICEEVENT ; 
 scalar_t__ MSG_XFERREADY ; 
 int /*<<< orphan*/  PostMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TWCC_BADPROTOCOL ; 
 int /*<<< orphan*/  TWCC_LOWMEMORY ; 
 scalar_t__ TWRC_FAILURE ; 
 scalar_t__ TWRC_SUCCESS ; 
 int /*<<< orphan*/  event_message ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

TW_UINT16 TWAIN_ControlNull (pTW_IDENTITY pOrigin, pTW_IDENTITY pDest, activeDS *pSource, TW_UINT16 MSG, TW_MEMREF pData)
{
    struct pending_message *message;

    TRACE ("DG_CONTROL/DAT_NULL MSG=%i\n", MSG);

    if (MSG != MSG_CLOSEDSREQ &&
        MSG != MSG_DEVICEEVENT &&
        MSG != MSG_XFERREADY)
    {
        DSM_twCC = TWCC_BADPROTOCOL;
        return TWRC_FAILURE;
    }

    message = HeapAlloc(GetProcessHeap(), 0, sizeof(*message));
    if (!message)
    {
        DSM_twCC = TWCC_LOWMEMORY;
        return TWRC_FAILURE;
    }

    message->msg = MSG;
    list_add_tail(&pSource->pending_messages, &message->entry);

    /* Delphi twain only sends us messages from one window, and it
       doesn't even give us the real handle to that window. Other
       applications might decide to forward messages sent to DSM_parent
       or to the one supplied to ENABLEDS. So let's try very hard to
       find a window that will work. */
    if (DSM_parent)
        PostMessageW(DSM_parent, event_message, 0, 0);
    if (pSource->ui_window && pSource->ui_window != DSM_parent)
        PostMessageW(pSource->ui_window, event_message, 0, 0);
    if (pSource->event_window && pSource->event_window != pSource->ui_window &&
        pSource->event_window != DSM_parent)
        PostMessageW(pSource->event_window, event_message, 0, 0);
    PostMessageW(0, event_message, 0, 0);

    return TWRC_SUCCESS;
}