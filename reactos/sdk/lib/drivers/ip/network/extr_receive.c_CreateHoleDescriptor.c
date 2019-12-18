#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* ULONG ;
struct TYPE_4__ {void* Last; void* First; } ;
typedef  TYPE_1__* PIPDATAGRAM_HOLE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IP ; 
 TYPE_1__* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPHoleList ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

PIPDATAGRAM_HOLE CreateHoleDescriptor(
  ULONG First,
  ULONG Last)
/*
 * FUNCTION: Returns a pointer to a IP datagram hole descriptor
 * ARGUMENTS:
 *     First = Offset of first octet of the hole
 *     Last  = Offset of last octet of the hole
 * RETURNS:
 *     Pointer to descriptor, NULL if there was not enough free
 *     resources
 */
{
	PIPDATAGRAM_HOLE Hole;

	TI_DbgPrint(DEBUG_IP, ("Called. First (%d)  Last (%d).\n", First, Last));

	Hole = ExAllocateFromNPagedLookasideList(&IPHoleList);
	if (!Hole) {
	    TI_DbgPrint(MIN_TRACE, ("Insufficient resources.\n"));
	    return NULL;
	}

	Hole->First = First;
	Hole->Last  = Last;

	TI_DbgPrint(DEBUG_IP, ("Returning hole descriptor at (0x%X).\n", Hole));

	return Hole;
}