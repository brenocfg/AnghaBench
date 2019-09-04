#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwSize; } ;
struct TYPE_7__ {int /*<<< orphan*/  lpConn; } ;
typedef  TYPE_1__* LPDPLAYX_LOBBYDATA ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_2__ DPLCONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_INVALIDPARAMS ; 
 int /*<<< orphan*/  DPERR_NOTLOBBIED ; 
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_CopyConnStructW (int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/  DPLAYX_IsAppIdLobbied (scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  DPLAYX_PrivHeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLAYX_PrivHeapFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_SizeOfLobbyDataW (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DP_OK ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 

HRESULT DPLAYX_SetConnectionSettingsW
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
    ERR(": old/new DPLCONNECTION type? Size=%u\n", lpConn->dwSize );

    return DPERR_INVALIDPARAMS;
  }

  DPLAYX_AcquireSemaphore();

  if ( ! DPLAYX_IsAppIdLobbied( dwAppID, &lpDplData ) )
  {
    DPLAYX_ReleaseSemaphore();

    return DPERR_NOTLOBBIED;
  }

  /* Free the existing memory */
  DPLAYX_PrivHeapFree( lpDplData->lpConn );

  lpDplData->lpConn = DPLAYX_PrivHeapAlloc( HEAP_ZERO_MEMORY,
                                            DPLAYX_SizeOfLobbyDataW( lpConn ) );

  DPLAYX_CopyConnStructW( lpDplData->lpConn, lpConn );


  DPLAYX_ReleaseSemaphore();

  /* FIXME: Send a message - I think */

  return DP_OK;
}