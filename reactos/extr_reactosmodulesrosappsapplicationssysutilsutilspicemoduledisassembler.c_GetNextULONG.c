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
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ ULONG ;
typedef  int UCHAR ;

/* Variables and functions */
 int GetUCHAR (scalar_t__) ; 

__attribute__((used)) static ULONG GetNextULONG(USHORT sel, UCHAR *offset, UCHAR *pCode)
{
    pCode[0] = GetUCHAR((ULONG) offset + 0) & 0xFF;
    pCode[1] = GetUCHAR((ULONG) offset + 1) & 0xFF;
    pCode[2] = GetUCHAR((ULONG) offset + 2) & 0xFF;
    pCode[3] = GetUCHAR((ULONG) offset + 3) & 0xFF;

    return( *(ULONG *) pCode );
}