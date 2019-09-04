#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_17__ {TYPE_3__* dp2; } ;
struct TYPE_16__ {int dwFlags; } ;
struct TYPE_13__ {int wCommandId; int /*<<< orphan*/  wVersion; int /*<<< orphan*/  dwMagic; } ;
struct TYPE_15__ {int /*<<< orphan*/  dpidNewPlayerId; TYPE_2__ envelope; } ;
struct TYPE_12__ {int /*<<< orphan*/  dwSPHeaderSize; } ;
struct TYPE_14__ {int /*<<< orphan*/  lpNameServerData; TYPE_1__ spData; } ;
typedef  TYPE_4__* LPDPMSG_NEWPLAYERIDREPLY ;
typedef  TYPE_5__* LPCDPMSG_REQUESTNEWPLAYERID ;
typedef  TYPE_6__ IDirectPlayImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
#define  DPMSGCMD_ENUMSESSIONSREPLY 135 
#define  DPMSGCMD_ENUMSESSIONSREQUEST 134 
#define  DPMSGCMD_FORWARDADDPLAYER 133 
#define  DPMSGCMD_FORWARDADDPLAYERNACK 132 
#define  DPMSGCMD_GETNAMETABLEREPLY 131 
#define  DPMSGCMD_JUSTENVELOPE 130 
#define  DPMSGCMD_NEWPLAYERIDREPLY 129 
#define  DPMSGCMD_REQUESTNEWPLAYERID 128 
 int /*<<< orphan*/  DPMSGMAGIC_DPLAYMSG ; 
 int /*<<< orphan*/  DPMSGVER_DP6 ; 
 int /*<<< orphan*/  DP_MSG_ErrorReceived (TYPE_6__*,int,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_MSG_ReplyReceived (TYPE_6__*,int,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_MSG_ToSelf (TYPE_6__*,int) ; 
 int /*<<< orphan*/  DP_NextObjectId () ; 
 int /*<<< orphan*/  DP_OK ; 
 int /*<<< orphan*/  DebugBreak () ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_AddRemoteComputerAsNameServer (void const*,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_ReplyToEnumSessionsRequest (void const*,void**,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  NS_SetLocalAddr (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

HRESULT DP_HandleMessage( IDirectPlayImpl *This, const void *lpcMessageBody,
        DWORD dwMessageBodySize, const void *lpcMessageHeader, WORD wCommandId, WORD wVersion,
        void **lplpReply, DWORD *lpdwMsgSize )
{
  TRACE( "(%p)->(%p,0x%08x,%p,%u,%u)\n",
         This, lpcMessageBody, dwMessageBodySize, lpcMessageHeader, wCommandId,
         wVersion );

  switch( wCommandId )
  {
    /* Name server needs to handle this request */
    case DPMSGCMD_ENUMSESSIONSREQUEST:
      /* Reply expected */
      NS_ReplyToEnumSessionsRequest( lpcMessageBody, lplpReply, lpdwMsgSize, This );
      break;

    /* Name server needs to handle this request */
    case DPMSGCMD_ENUMSESSIONSREPLY:
      /* No reply expected */
      NS_AddRemoteComputerAsNameServer( lpcMessageHeader,
                                        This->dp2->spData.dwSPHeaderSize,
                                        lpcMessageBody,
                                        This->dp2->lpNameServerData );
      break;

    case DPMSGCMD_REQUESTNEWPLAYERID:
    {
      LPCDPMSG_REQUESTNEWPLAYERID lpcMsg = lpcMessageBody;

      LPDPMSG_NEWPLAYERIDREPLY lpReply;

      *lpdwMsgSize = This->dp2->spData.dwSPHeaderSize + sizeof( *lpReply );

      *lplpReply = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, *lpdwMsgSize );

      FIXME( "Ignoring dwFlags 0x%08x in request msg\n",
             lpcMsg->dwFlags );

      /* Setup the reply */
      lpReply = (LPDPMSG_NEWPLAYERIDREPLY)( (BYTE*)(*lplpReply) +
                                            This->dp2->spData.dwSPHeaderSize );

      lpReply->envelope.dwMagic    = DPMSGMAGIC_DPLAYMSG;
      lpReply->envelope.wCommandId = DPMSGCMD_NEWPLAYERIDREPLY;
      lpReply->envelope.wVersion   = DPMSGVER_DP6;

      lpReply->dpidNewPlayerId = DP_NextObjectId();

      TRACE( "Allocating new playerid 0x%08x from remote request\n",
             lpReply->dpidNewPlayerId );
      break;
    }

    case DPMSGCMD_GETNAMETABLEREPLY:
    case DPMSGCMD_NEWPLAYERIDREPLY:
      DP_MSG_ReplyReceived( This, wCommandId, lpcMessageBody, dwMessageBodySize );
      break;

    case DPMSGCMD_JUSTENVELOPE:
      TRACE( "GOT THE SELF MESSAGE: %p -> 0x%08x\n", lpcMessageHeader, ((const DWORD *)lpcMessageHeader)[1] );
      NS_SetLocalAddr( This->dp2->lpNameServerData, lpcMessageHeader, 20 );
      DP_MSG_ReplyReceived( This, wCommandId, lpcMessageBody, dwMessageBodySize );

    case DPMSGCMD_FORWARDADDPLAYER:
      TRACE( "Sending message to self to get my addr\n" );
      DP_MSG_ToSelf( This, 1 ); /* This is a hack right now */
      break;

    case DPMSGCMD_FORWARDADDPLAYERNACK:
      DP_MSG_ErrorReceived( This, wCommandId, lpcMessageBody, dwMessageBodySize );
      break;

    default:
      FIXME( "Unknown wCommandId %u. Ignoring message\n", wCommandId );
      DebugBreak();
      break;
  }

  /* FIXME: There is code in dplaysp.c to handle dplay commands. Move to here. */

  return DP_OK;
}