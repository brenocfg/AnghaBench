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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  KdPortGetByteEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SerialPortInfo ; 

CHAR
KdbpTryGetCharSerial(ULONG Retry)
{
    CHAR Result = -1;

    if (Retry == 0)
        while (!KdPortGetByteEx(&SerialPortInfo, (PUCHAR)&Result));
    else
        while (!KdPortGetByteEx(&SerialPortInfo, (PUCHAR)&Result) && Retry-- > 0);

    return Result;
}