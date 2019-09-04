#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  char UCHAR ;
struct TYPE_14__ {TYPE_1__* DebugInfo; } ;
struct TYPE_13__ {scalar_t__ numAddresses; char* nbname; int /*<<< orphan*/ * addresses; } ;
struct TYPE_12__ {TYPE_8__ cs; scalar_t__ fd; } ;
struct TYPE_11__ {int ncb_rto; int ncb_sto; int /*<<< orphan*/  ncb_name; } ;
struct TYPE_10__ {scalar_t__* Spare; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_2__* PNCB ;
typedef  TYPE_3__ NetBTSession ;
typedef  int /*<<< orphan*/  NetBTAdapter ;
typedef  TYPE_4__ NBNameCacheEntry ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_8__*) ; 
 char NRC_BADDR ; 
 char NRC_CMDTMO ; 
 char NRC_ENVNOTDEF ; 
 char NRC_GOODRET ; 
 char NRC_INVADDRESS ; 
 char NRC_NAMERR ; 
 char NRC_OSRESNOTAV ; 
 char NetBTInternalFindName (int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__ const**) ; 
 char NetBTSessionReq (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PORT_NBSS ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  TRACE (char*,char,...) ; 
 scalar_t__ WSASocketA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSA_FLAG_OVERLAPPED ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static UCHAR NetBTCall(void *adapt, PNCB ncb, void **sess)
{
    NetBTAdapter *adapter = adapt;
    UCHAR ret;
    const NBNameCacheEntry *cacheEntry = NULL;

    TRACE("adapt %p, ncb %p\n", adapt, ncb);

    if (!adapter) return NRC_ENVNOTDEF;
    if (!ncb) return NRC_INVADDRESS;
    if (!sess) return NRC_BADDR;

    ret = NetBTInternalFindName(adapter, ncb, &cacheEntry);
    if (ret == NRC_GOODRET)
    {
        if (cacheEntry && cacheEntry->numAddresses > 0)
        {
            SOCKET fd;

            fd = WSASocketA(PF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0,
             WSA_FLAG_OVERLAPPED);
            if (fd != INVALID_SOCKET)
            {
                DWORD timeout;
                struct sockaddr_in sin;

                if (ncb->ncb_rto > 0)
                {
                    timeout = ncb->ncb_rto * 500;
                    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout,
                     sizeof(timeout));
                }
                if (ncb->ncb_sto > 0)
                {
                    timeout = ncb->ncb_sto * 500;
                    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout,
                     sizeof(timeout));
                }

                memset(&sin, 0, sizeof(sin));
                memcpy(&sin.sin_addr, &cacheEntry->addresses[0],
                 sizeof(sin.sin_addr));
                sin.sin_family = AF_INET;
                sin.sin_port   = htons(PORT_NBSS);
                /* FIXME: use nonblocking mode for the socket, check the
                 * cancel flag periodically
                 */
                if (connect(fd, (struct sockaddr *)&sin, sizeof(sin))
                 == SOCKET_ERROR)
                    ret = NRC_CMDTMO;
                else
                {
                    static const UCHAR fakedCalledName[] = "*SMBSERVER";
                    const UCHAR *calledParty = cacheEntry->nbname[0] == '*'
                     ? fakedCalledName : cacheEntry->nbname;

                    ret = NetBTSessionReq(fd, calledParty, ncb->ncb_name);
                    if (ret != NRC_GOODRET && calledParty[0] == '*')
                    {
                        FIXME("NBT session to \"*SMBSERVER\" refused,\n");
                        FIXME("should try finding name using ASTAT\n");
                    }
                }
                if (ret != NRC_GOODRET)
                    closesocket(fd);
                else
                {
                    NetBTSession *session = HeapAlloc(
                     GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(NetBTSession));

                    if (session)
                    {
                        session->fd = fd;
                        InitializeCriticalSection(&session->cs);
                        session->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": NetBTSession.cs");
                        *sess = session;
                    }
                    else
                    {
                        ret = NRC_OSRESNOTAV;
                        closesocket(fd);
                    }
                }
            }
            else
                ret = NRC_OSRESNOTAV;
        }
        else
            ret = NRC_NAMERR;
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}