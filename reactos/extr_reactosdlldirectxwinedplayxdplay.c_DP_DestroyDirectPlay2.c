#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  lpISP; TYPE_1__* lpCB; } ;
struct TYPE_11__ {TYPE_8__* lpCB; } ;
struct TYPE_15__ {scalar_t__ hEnumSessionThread; scalar_t__ hServiceProvider; scalar_t__ hDPLobbyProvider; TYPE_3__ spData; struct TYPE_15__* lpSessionDesc; TYPE_2__ dplspData; int /*<<< orphan*/  lpNameServerData; } ;
struct TYPE_14__ {int /*<<< orphan*/  lpISP; } ;
struct TYPE_13__ {TYPE_8__* dp2; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* Shutdown ) () ;int /*<<< orphan*/  (* ShutdownEx ) (TYPE_6__*) ;} ;
typedef  TYPE_4__* LPVOID ;
typedef  TYPE_4__ IDirectPlayImpl ;
typedef  TYPE_6__ DPSP_SHUTDOWNDATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  IDirectPlaySP_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NS_DeleteSessionCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TerminateThread (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static BOOL DP_DestroyDirectPlay2( LPVOID lpDP )
{
  IDirectPlayImpl *This = lpDP;

  if( This->dp2->hEnumSessionThread != INVALID_HANDLE_VALUE )
  {
    TerminateThread( This->dp2->hEnumSessionThread, 0 );
    CloseHandle( This->dp2->hEnumSessionThread );
  }

  /* Finish with the SP - have it shutdown */
  if( This->dp2->spData.lpCB->ShutdownEx )
  {
    DPSP_SHUTDOWNDATA data;

    TRACE( "Calling SP ShutdownEx\n" );

    data.lpISP = This->dp2->spData.lpISP;

    (*This->dp2->spData.lpCB->ShutdownEx)( &data );
  }
  else if (This->dp2->spData.lpCB->Shutdown ) /* obsolete interface */
  {
    TRACE( "Calling obsolete SP Shutdown\n" );
    (*This->dp2->spData.lpCB->Shutdown)();
  }

  /* Unload the SP (if it exists) */
  if( This->dp2->hServiceProvider != 0 )
  {
    FreeLibrary( This->dp2->hServiceProvider );
  }

  /* Unload the Lobby Provider (if it exists) */
  if( This->dp2->hDPLobbyProvider != 0 )
  {
    FreeLibrary( This->dp2->hDPLobbyProvider );
  }

  /* FIXME: Need to delete receive and send msgs queue contents */

  NS_DeleteSessionCache( This->dp2->lpNameServerData );

  HeapFree( GetProcessHeap(), 0, This->dp2->dplspData.lpCB);
  HeapFree( GetProcessHeap(), 0, This->dp2->lpSessionDesc );

  IDirectPlaySP_Release( This->dp2->spData.lpISP );

  /* Delete the contents */
  HeapFree( GetProcessHeap(), 0, This->dp2 );

  return TRUE;
}