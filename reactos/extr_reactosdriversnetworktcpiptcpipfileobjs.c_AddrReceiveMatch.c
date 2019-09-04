#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PIP_ADDRESS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ AddrIsBroadcastMatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AddrIsEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AddrIsUnspecified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN AddrReceiveMatch(
   PIP_ADDRESS LocalAddress,
   PIP_ADDRESS RemoteAddress)
{
   if (AddrIsEqual(LocalAddress, RemoteAddress))
   {
       /* Unicast address match */
       return TRUE;
   }

   if (AddrIsBroadcastMatch(LocalAddress, RemoteAddress))
   {
       /* Broadcast address match */
       return TRUE;
   }

   if (AddrIsUnspecified(LocalAddress))
   {
       /* Local address unspecified */
       return TRUE;
   }

   if (AddrIsUnspecified(RemoteAddress))
   {
       /* Remote address unspecified */
       return TRUE;
   }

   return FALSE;
}