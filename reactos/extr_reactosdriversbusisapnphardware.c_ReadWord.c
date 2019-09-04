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
typedef  int USHORT ;
typedef  int /*<<< orphan*/  PUCHAR ;

/* Variables and functions */
 int ReadByte (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
inline
USHORT
ReadWord(PUCHAR ReadDataPort, USHORT Address)
{
  return ((ReadByte(ReadDataPort, Address) << 8) |
          (ReadByte(ReadDataPort, Address + 1)));
}