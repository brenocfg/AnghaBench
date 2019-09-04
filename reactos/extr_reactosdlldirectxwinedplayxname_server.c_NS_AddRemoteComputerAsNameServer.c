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
typedef  TYPE_3__* lpNSCacheData ;
typedef  TYPE_4__* lpNSCache ;
struct TYPE_17__ {int /*<<< orphan*/  guidInstance; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpszSessionNameA; } ;
struct TYPE_13__ {TYPE_1__ u1; int /*<<< orphan*/  guidInstance; } ;
struct TYPE_16__ {TYPE_2__ sd; } ;
struct TYPE_15__ {TYPE_3__* present; int /*<<< orphan*/  first; } ;
struct TYPE_14__ {int /*<<< orphan*/  dwTime; TYPE_2__* data; void* lpNSAddrHdr; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  TYPE_5__* LPCDPMSG_ENUMSESSIONSREPLY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CopyMemory (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPQ_INSERT (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPQ_REMOVE_ENTRY_CB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  NS_PruneSessionCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbDeleteNSNodeFromHeap (TYPE_3__*) ; 
 int /*<<< orphan*/  cbUglyPig ; 
 TYPE_6__* data ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  timeGetTime () ; 

void NS_AddRemoteComputerAsNameServer( LPCVOID                      lpcNSAddrHdr,
                                       DWORD                        dwHdrSize,
                                       LPCDPMSG_ENUMSESSIONSREPLY   lpcMsg,
                                       LPVOID                       lpNSInfo )
{
  DWORD len;
  lpNSCache     lpCache = (lpNSCache)lpNSInfo;
  lpNSCacheData lpCacheNode;

  TRACE( "%p, %p, %p\n", lpcNSAddrHdr, lpcMsg, lpNSInfo );

  /* See if we can find this session. If we can, remove it as it's a dup */
  DPQ_REMOVE_ENTRY_CB( lpCache->first, next, data->guidInstance, cbUglyPig,
                       lpcMsg->sd.guidInstance, lpCacheNode );

  if( lpCacheNode != NULL )
  {
    TRACE( "Duplicate session entry for %s removed - updated version kept\n",
           debugstr_guid( &lpCacheNode->data->guidInstance ) );
    cbDeleteNSNodeFromHeap( lpCacheNode );
  }

  /* Add this to the list */
  lpCacheNode = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof( *lpCacheNode ) );

  if( lpCacheNode == NULL )
  {
    ERR( "no memory for NS node\n" );
    return;
  }

  lpCacheNode->lpNSAddrHdr = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
                                        dwHdrSize );
  CopyMemory( lpCacheNode->lpNSAddrHdr, lpcNSAddrHdr, dwHdrSize );

  lpCacheNode->data = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof( *(lpCacheNode->data) ) );

  if( lpCacheNode->data == NULL )
  {
    ERR( "no memory for SESSIONDESC2\n" );
    HeapFree( GetProcessHeap(), 0, lpCacheNode );
    return;
  }

  *lpCacheNode->data = lpcMsg->sd;
  len = WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)(lpcMsg+1), -1, NULL, 0, NULL, NULL );
  if ((lpCacheNode->data->u1.lpszSessionNameA = HeapAlloc( GetProcessHeap(), 0, len )))
  {
      WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)(lpcMsg+1), -1,
                           lpCacheNode->data->u1.lpszSessionNameA, len, NULL, NULL );
  }

  lpCacheNode->dwTime = timeGetTime();

  DPQ_INSERT(lpCache->first, lpCacheNode, next );

  lpCache->present = lpCacheNode;

  /* Use this message as an opportunity to weed out any old sessions so
   * that we don't enum them again
   */
  NS_PruneSessionCache( lpNSInfo );
}