#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; char* buf; } ;
typedef  TYPE_1__ WSABUF ;
typedef  int UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  recv_success; } ;
struct TYPE_11__ {scalar_t__ fd; scalar_t__ bytesPending; int /*<<< orphan*/  cs; } ;
struct TYPE_10__ {int ncb_length; scalar_t__ ncb_buffer; } ;
typedef  TYPE_2__* PNCB ;
typedef  TYPE_3__ NetBTSession ;
typedef  TYPE_4__ NetBTAdapter ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int NBR_GETWORD (int*) ; 
 int NBSS_EXTENSION ; 
 int NBSS_HDRSIZE ; 
 int NBSS_KEEPALIVE ; 
 int NBSS_MSG ; 
 scalar_t__ NCB_CANCELLED (TYPE_2__*) ; 
 int NRC_BADDR ; 
 int NRC_CMDCAN ; 
 int NRC_ENVNOTDEF ; 
 int NRC_GOODRET ; 
 int NRC_INCOMP ; 
 int NRC_SABORT ; 
 int NRC_SNUMOUT ; 
 int /*<<< orphan*/  NetBIOSHangupSession (TYPE_2__*) ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 int WSARecv (scalar_t__,TYPE_1__*,size_t,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UCHAR NetBTRecv(void *adapt, void *sess, PNCB ncb)
{
    NetBTAdapter *adapter = adapt;
    NetBTSession *session = sess;
    UCHAR buffer[NBSS_HDRSIZE], ret;
    int r;
    WSABUF wsaBufs[2];
    DWORD bufferCount, bytesReceived, flags;

    TRACE("adapt %p, session %p, NCB %p\n", adapt, session, ncb);

    if (!adapter) return NRC_ENVNOTDEF;
    if (!ncb) return NRC_BADDR;
    if (!ncb->ncb_buffer) return NRC_BADDR;
    if (!session) return NRC_SNUMOUT;
    if (session->fd == INVALID_SOCKET) return NRC_SNUMOUT;

    EnterCriticalSection(&session->cs);
    bufferCount = 0;
    if (session->bytesPending == 0)
    {
        bufferCount++;
        wsaBufs[0].len = NBSS_HDRSIZE;
        wsaBufs[0].buf = (char*)buffer;
    }
    wsaBufs[bufferCount].len = ncb->ncb_length;
    wsaBufs[bufferCount].buf = (char*)ncb->ncb_buffer;
    bufferCount++;

    flags = 0;
    /* FIXME: should poll a bit so I can check the cancel flag */
    r = WSARecv(session->fd, wsaBufs, bufferCount, &bytesReceived, &flags,
     NULL, NULL);
    if (r == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
    {
        LeaveCriticalSection(&session->cs);
        ERR("Receive error, WSAGetLastError() returns %d\n", WSAGetLastError());
        NetBIOSHangupSession(ncb);
        ret = NRC_SABORT;
    }
    else if (NCB_CANCELLED(ncb))
    {
        LeaveCriticalSection(&session->cs);
        ret = NRC_CMDCAN;
    }
    else
    {
        if (bufferCount == 2)
        {
            if (buffer[0] == NBSS_KEEPALIVE)
            {
                LeaveCriticalSection(&session->cs);
                FIXME("Oops, received a session keepalive and lost my place\n");
                /* need to read another session header until we get a session
                 * message header. */
                NetBIOSHangupSession(ncb);
                ret = NRC_SABORT;
                goto error;
            }
            else if (buffer[0] != NBSS_MSG)
            {
                LeaveCriticalSection(&session->cs);
                FIXME("Received unexpected session msg type %d\n", buffer[0]);
                NetBIOSHangupSession(ncb);
                ret = NRC_SABORT;
                goto error;
            }
            else
            {
                if (buffer[1] & NBSS_EXTENSION)
                {
                    LeaveCriticalSection(&session->cs);
                    FIXME("Received a message that's too long for my taste\n");
                    NetBIOSHangupSession(ncb);
                    ret = NRC_SABORT;
                    goto error;
                }
                else
                {
                    session->bytesPending = NBSS_HDRSIZE
                     + NBR_GETWORD(&buffer[2]) - bytesReceived;
                    ncb->ncb_length = bytesReceived - NBSS_HDRSIZE;
                    LeaveCriticalSection(&session->cs);
                }
            }
        }
        else
        {
            if (bytesReceived < session->bytesPending)
                session->bytesPending -= bytesReceived;
            else
                session->bytesPending = 0;
            LeaveCriticalSection(&session->cs);
            ncb->ncb_length = bytesReceived;
        }
        if (session->bytesPending > 0)
            ret = NRC_INCOMP;
        else
        {
            ret = NRC_GOODRET;
            adapter->recv_success++;
        }
    }
error:
    TRACE("returning 0x%02x\n", ret);
    return ret;
}