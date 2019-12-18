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
typedef  int ULONG ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int HexValue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CHAR
GspHex2MemGetContent(PVOID Context, ULONG Offset)
{
    return (CHAR)((HexValue(*((PCHAR)Context + 2 * Offset)) << 4) +
                   HexValue(*((PCHAR)Context + 2 * Offset + 1)));
}