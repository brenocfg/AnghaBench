#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dwSize; TYPE_1__* lpSessionDesc; } ;
struct TYPE_9__ {int /*<<< orphan*/  lpConn; } ;
struct TYPE_8__ {int dwSize; } ;
typedef  TYPE_2__* LPDPLAYX_LOBBYDATA ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  DPSESSIONDESC2 ;
typedef  TYPE_3__ DPLCONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_INVALIDPARAMS ; 
 int /*<<< orphan*/  DPERR_NOTLOBBIED ; 
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_CopyConnStructA (int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 int /*<<< orphan*/  DPLAYX_IsAppIdLobbied (scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  DPLAYX_PrivHeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLAYX_PrivHeapFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_SizeOfLobbyDataA (TYPE_3__ const*) ; 
 int /*<<< orphan*/  DP_OK ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 

HRESULT DPLAYX_SetConnectionSettingsA
( DWORD dwFlags,
  DWORD dwAppID,
  const DPLCONNECTION *lpConn )
{
  LPDPLAYX_LOBBYDATA lpDplData;

  /* Parameter check */
  if( dwFlags || !lpConn )
  {
    ERR("invalid parameters.\n");
    return DPERR_INVALIDPARAMS;
  }

  /* Store information */
  if(  lpConn->dwSize != sizeof(DPLCONNECTION) )
  {
    ERR(": old/new DPLCONNECTION type? Size=%08x\n", lpConn->dwSize );

    return DPERR_INVALIDPARAMS;
  }

  DPLAYX_AcquireSemaphore();

  if ( ! DPLAYX_IsAppIdLobbied( dwAppID, &lpDplData ) )
  {
    DPLAYX_ReleaseSemaphore();

    return DPERR_NOTLOBBIED;
  }

  if(  (!lpConn->lpSessionDesc ) ||
       ( lpConn->lpSessionDesc->dwSize != sizeof( DPSESSIONDESC2 ) )
    )
  {
    DPLAYX_ReleaseSemaphore();

    ERR("DPSESSIONDESC passed in? Size=%u\n",
        lpConn->lpSessionDesc?lpConn->lpSessionDesc->dwSize:0 );

    return DPERR_INVALIDPARAMS;
  }

  /* Free the existing memory */
  DPLAYX_PrivHeapFree( lpDplData->lpConn );

  lpDplData->lpConn = DPLAYX_PrivHeapAlloc( HEAP_ZERO_MEMORY,
                                            DPLAYX_SizeOfLobbyDataA( lpConn ) );

  DPLAYX_CopyConnStructA( lpDplData->lpConn, lpConn );


  DPLAYX_ReleaseSemaphore();

  /* FIXME: Send a message - I think */

  return DP_OK;
}