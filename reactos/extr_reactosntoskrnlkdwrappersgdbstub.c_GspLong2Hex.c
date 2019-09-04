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
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GspMem2Hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

VOID
GspLong2Hex(PCHAR *Address, LONG Value)
{
    LONG Save;

    Save = (((Value >> 0) & 0xff) << 24) | (((Value >> 8) & 0xff) << 16) |
           (((Value >> 16) & 0xff) << 8) | (((Value >> 24) & 0xff) << 0);

    *Address = GspMem2Hex((PCHAR)&Save, *Address, 4, FALSE);
}