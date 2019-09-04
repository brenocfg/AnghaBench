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
struct TYPE_3__ {int ref; int /*<<< orphan*/  state; int /*<<< orphan*/  control; int /*<<< orphan*/  update; int /*<<< orphan*/  get_param; int /*<<< orphan*/  close; int /*<<< orphan*/  stream_info; int /*<<< orphan*/  streamed; int /*<<< orphan*/  open_flags; } ;
typedef  int /*<<< orphan*/ * PCMSG_STREAM_INFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CryptMsgUpdateFunc ;
typedef  int /*<<< orphan*/  CryptMsgGetParamFunc ;
typedef  int /*<<< orphan*/  CryptMsgControlFunc ;
typedef  int /*<<< orphan*/  CryptMsgCloseFunc ;
typedef  TYPE_1__ CryptMsgBase ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MsgStateInit ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void CryptMsgBase_Init(CryptMsgBase *msg, DWORD dwFlags,
 PCMSG_STREAM_INFO pStreamInfo, CryptMsgCloseFunc close,
 CryptMsgGetParamFunc get_param, CryptMsgUpdateFunc update,
 CryptMsgControlFunc control)
{
    msg->ref = 1;
    msg->open_flags = dwFlags;
    if (pStreamInfo)
    {
        msg->streamed = TRUE;
        msg->stream_info = *pStreamInfo;
    }
    else
    {
        msg->streamed = FALSE;
        memset(&msg->stream_info, 0, sizeof(msg->stream_info));
    }
    msg->close = close;
    msg->get_param = get_param;
    msg->update = update;
    msg->control = control;
    msg->state = MsgStateInit;
}