#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  AddressLength; int /*<<< orphan*/  Broadcast; } ;
typedef  int /*<<< orphan*/ * PNEIGHBOR_CACHE_ENTRY ;
typedef  TYPE_1__* PIP_INTERFACE ;
typedef  int /*<<< orphan*/  PIP_ADDRESS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARP_INCOMPLETE_TIMEOUT ; 
 scalar_t__ AddrIsEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ AddrIsUnspecified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_NCACHE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/ * NBAddNeighbor (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NBLocateNeighbor (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NBSendSolicit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUD_INCOMPLETE ; 
 int /*<<< orphan*/  NUD_PERMANENT ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

PNEIGHBOR_CACHE_ENTRY NBFindOrCreateNeighbor(
  PIP_INTERFACE Interface,
  PIP_ADDRESS Address,
  BOOLEAN NoTimeout)
/*
 * FUNCTION: Tries to find a neighbor and if unsuccesful, creates a new NCE
 * ARGUMENTS:
 *   Interface = Pointer to interface to use (in case NCE is not found)
 *   Address   = Pointer to IP address
 * RETURNS:
 *   Pointer to NCE, NULL if there is not enough free resources
 * NOTES:
 *   The NCE is referenced if found or created. The caller is
 *   responsible for dereferencing it again after use
 */
{
  PNEIGHBOR_CACHE_ENTRY NCE;

  TI_DbgPrint(DEBUG_NCACHE, ("Called. Interface (0x%X)  Address (0x%X).\n", Interface, Address));

  NCE = NBLocateNeighbor(Address, Interface);
  if (NCE == NULL)
    {
        TI_DbgPrint(MID_TRACE,("BCAST: %s\n", A2S(&Interface->Broadcast)));
        if( AddrIsEqual(Address, &Interface->Broadcast) ||
            AddrIsUnspecified(Address) ) {
            TI_DbgPrint(MID_TRACE,("Packet targeted at broadcast addr\n"));
            NCE = NBAddNeighbor(Interface, Address, NULL,
                                Interface->AddressLength, NUD_PERMANENT, 0);
        } else {
            NCE = NBAddNeighbor(Interface, Address, NULL,
                                Interface->AddressLength, NUD_INCOMPLETE, NoTimeout ? 0 : ARP_INCOMPLETE_TIMEOUT);
            if (!NCE) return NULL;
            NBSendSolicit(NCE);
        }
    }

  return NCE;
}