#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__* PANSI_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  AddToRingBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bIsDebugPrint ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  restore_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_flags (int /*<<< orphan*/ ) ; 

ULONG PICE_KdpPrintString(PANSI_STRING String)
{
	ULONG ulRingBufferLock;

  save_flags(ulRingBufferLock);
  cli();

  /* CH: What is bIsDebugPrint used for? */
  bIsDebugPrint = FALSE;

	DPRINT((0,"PICE_KdpPrintString\n\n\n"));
  AddToRingBuffer(String->Buffer);
  restore_flags(ulRingBufferLock);
}