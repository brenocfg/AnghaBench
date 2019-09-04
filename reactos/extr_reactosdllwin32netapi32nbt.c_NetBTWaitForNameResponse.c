#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int member_0; int member_1; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct fd_set {int dummy; } ;
typedef  int /*<<< orphan*/  fromaddr ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_5__ {int member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ WSABUF ;
typedef  scalar_t__ WORD ;
typedef  scalar_t__ UCHAR ;
struct TYPE_6__ {scalar_t__ nameQueryXID; } ;
typedef  scalar_t__ SOCKET ;
typedef  scalar_t__* PUCHAR ;
typedef  scalar_t__ (* NetBTAnswerCallback ) (void*,scalar_t__,scalar_t__,scalar_t__*,scalar_t__) ;
typedef  TYPE_2__ NetBTAdapter ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,struct fd_set*) ; 
 int /*<<< orphan*/  FD_ZERO (struct fd_set*) ; 
 int GetTickCount () ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ NBNS_CLASS_INTERNET ; 
 int NBNS_HEADER_SIZE ; 
 scalar_t__ NBNS_REPLYCODE ; 
 scalar_t__ NBNS_RESPONSE_AND_OPCODE ; 
 scalar_t__ NBNS_RESPONSE_AND_QUERY ; 
 scalar_t__ NBR_GETWORD (scalar_t__*) ; 
 scalar_t__ NRC_BADDR ; 
 scalar_t__ NRC_GOODRET ; 
 scalar_t__ NRC_NAMERR ; 
 scalar_t__ NRC_SYSTEM ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int WSARecvFrom (scalar_t__,TYPE_1__*,int,int*,int*,struct sockaddr*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ min (scalar_t__,int) ; 
 int select (scalar_t__,struct fd_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static UCHAR NetBTWaitForNameResponse(const NetBTAdapter *adapter, SOCKET fd,
 DWORD waitUntil, NetBTAnswerCallback answerCallback, void *data)
{
    BOOL found = FALSE;
    DWORD now;
    UCHAR ret = NRC_GOODRET;

    if (!adapter) return NRC_BADDR;
    if (fd == INVALID_SOCKET) return NRC_BADDR;
    if (!answerCallback) return NRC_BADDR;

    while (!found && ret == NRC_GOODRET && (int)((now = GetTickCount()) - waitUntil) < 0)
    {
        DWORD msToWait = waitUntil - now;
        struct fd_set fds;
        struct timeval timeout = { msToWait / 1000, msToWait % 1000 };
        int r;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        r = select(fd + 1, &fds, NULL, NULL, &timeout);
        if (r < 0)
            ret = NRC_SYSTEM;
        else if (r == 1)
        {
            /* FIXME: magic #, is this always enough? */
            UCHAR buffer[256];
            int fromsize;
            struct sockaddr_in fromaddr;
            WORD respXID, flags, queryCount, answerCount;
            WSABUF wsaBuf = { sizeof(buffer), (CHAR*)buffer };
            DWORD bytesReceived, recvFlags = 0;

            fromsize = sizeof(fromaddr);
            r = WSARecvFrom(fd, &wsaBuf, 1, &bytesReceived, &recvFlags,
             (struct sockaddr*)&fromaddr, &fromsize, NULL, NULL);
            if(r < 0)
            {
                ret = NRC_SYSTEM;
                break;
            }

            if (bytesReceived < NBNS_HEADER_SIZE)
                continue;

            respXID = NBR_GETWORD(buffer);
            if (adapter->nameQueryXID != respXID)
                continue;

            flags = NBR_GETWORD(buffer + 2);
            queryCount = NBR_GETWORD(buffer + 4);
            answerCount = NBR_GETWORD(buffer + 6);

            /* a reply shouldn't contain a query, ignore bad packet */
            if (queryCount > 0)
                continue;

            if ((flags & NBNS_RESPONSE_AND_OPCODE) == NBNS_RESPONSE_AND_QUERY)
            {
                if ((flags & NBNS_REPLYCODE) != 0)
                    ret = NRC_NAMERR;
                else if ((flags & NBNS_REPLYCODE) == 0 && answerCount > 0)
                {
                    PUCHAR ptr = buffer + NBNS_HEADER_SIZE;
                    BOOL shouldContinue = TRUE;
                    WORD answerIndex = 0;

                    found = TRUE;
                    /* decode one answer at a time */
                    while (ret == NRC_GOODRET && answerIndex < answerCount &&
                     ptr - buffer < bytesReceived && shouldContinue)
                    {
                        WORD rLen;

                        /* scan past name */
                        for (; ptr[0] && ptr - buffer < bytesReceived; )
                            ptr += ptr[0] + 1;
                        ptr++;
                        ptr += 2; /* scan past type */
                        if (ptr - buffer < bytesReceived && ret == NRC_GOODRET
                         && NBR_GETWORD(ptr) == NBNS_CLASS_INTERNET)
                            ptr += sizeof(WORD);
                        else
                            ret = NRC_SYSTEM; /* parse error */
                        ptr += sizeof(DWORD); /* TTL */
                        rLen = NBR_GETWORD(ptr);
                        rLen = min(rLen, bytesReceived - (ptr - buffer));
                        ptr += sizeof(WORD);
                        shouldContinue = answerCallback(data, answerCount,
                         answerIndex, ptr, rLen);
                        ptr += rLen;
                        answerIndex++;
                    }
                }
            }
        }
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}