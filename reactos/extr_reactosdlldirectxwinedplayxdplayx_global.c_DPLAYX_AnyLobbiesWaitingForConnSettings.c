#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_2__ {scalar_t__ dwAppID; scalar_t__ bWaitForConnectionSettings; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* lobbyData ; 
 size_t numSupportedLobbies ; 

BOOL DPLAYX_AnyLobbiesWaitingForConnSettings(void)
{
  UINT i;
  BOOL bFound = FALSE;

  DPLAYX_AcquireSemaphore();

  for( i=0; i < numSupportedLobbies; i++ )
  {
    if( ( lobbyData[ i ].dwAppID != 0 ) &&            /* lobby initialized */
        ( lobbyData[ i ].bWaitForConnectionSettings ) /* Waiting */
      )
    {
      bFound = TRUE;
      break;
    }
  }

  DPLAYX_ReleaseSemaphore();

  return bFound;
}