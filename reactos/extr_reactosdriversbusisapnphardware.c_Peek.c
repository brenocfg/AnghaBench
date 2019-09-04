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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/ ***** USHORT ;
typedef  int /*<<< orphan*/ ***** ULONG ;
typedef  scalar_t__ PVOID ;
typedef  int PUCHAR ;

/* Variables and functions */
 int /*<<< orphan*/ ***** PeekByte (int) ; 

__attribute__((used)) static
VOID
Peek(PUCHAR ReadDataPort, PVOID Buffer, ULONG Length)
{
  USHORT i, byte;

  for (i = 0; i < Length; i++)
  {
    byte = PeekByte(ReadDataPort);
    if (Buffer)
       *((PUCHAR)Buffer + i) = byte;
  }
}