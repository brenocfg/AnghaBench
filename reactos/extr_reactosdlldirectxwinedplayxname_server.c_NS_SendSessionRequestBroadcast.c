#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int dwMessageSize; int bReturnStatus; scalar_t__ lpMessage; int /*<<< orphan*/  lpISP; } ;
struct TYPE_8__ {int /*<<< orphan*/  wVersion; int /*<<< orphan*/  wCommandId; int /*<<< orphan*/  dwMagic; } ;
struct TYPE_11__ {int dwFlags; int /*<<< orphan*/  guidApplication; scalar_t__ dwPasswordSize; TYPE_1__ envelope; } ;
struct TYPE_10__ {int dwSPHeaderSize; TYPE_2__* lpCB; int /*<<< orphan*/  lpISP; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* EnumSessions ) (TYPE_5__*) ;} ;
typedef  TYPE_3__ SPINITDATA ;
typedef  TYPE_4__* LPDPMSG_ENUMSESSIONSREQUEST ;
typedef  int /*<<< orphan*/ * LPCGUID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_5__ DPSP_ENUMSESSIONSDATA ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int DPENUMSESSIONS_RETURNSTATUS ; 
 int /*<<< orphan*/  DPMSGCMD_ENUMSESSIONSREQUEST ; 
 int /*<<< orphan*/  DPMSGMAGIC_DPLAYMSG ; 
 int /*<<< orphan*/  DPMSGVER_DP6 ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

HRESULT NS_SendSessionRequestBroadcast( LPCGUID lpcGuid,
                                        DWORD dwFlags,
                                        const SPINITDATA *lpSpData )

{
  DPSP_ENUMSESSIONSDATA data;
  LPDPMSG_ENUMSESSIONSREQUEST lpMsg;

  TRACE( "enumerating for guid %s\n", debugstr_guid( lpcGuid ) );

  /* Get the SP to deal with sending the EnumSessions request */
  FIXME( ": not all data fields are correct\n" );

  data.dwMessageSize = lpSpData->dwSPHeaderSize + sizeof( *lpMsg ); /*FIXME!*/
  data.lpMessage = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
                              data.dwMessageSize );
  data.lpISP = lpSpData->lpISP;
  data.bReturnStatus = (dwFlags & DPENUMSESSIONS_RETURNSTATUS) != 0;


  lpMsg = (LPDPMSG_ENUMSESSIONSREQUEST)(((BYTE*)data.lpMessage)+lpSpData->dwSPHeaderSize);

  /* Setup EnumSession request message */
  lpMsg->envelope.dwMagic    = DPMSGMAGIC_DPLAYMSG;
  lpMsg->envelope.wCommandId = DPMSGCMD_ENUMSESSIONSREQUEST;
  lpMsg->envelope.wVersion   = DPMSGVER_DP6;

  lpMsg->dwPasswordSize = 0; /* FIXME: If enumerating passwords..? */
  lpMsg->dwFlags        = dwFlags;

  lpMsg->guidApplication = *lpcGuid;

  return (lpSpData->lpCB->EnumSessions)( &data );
}