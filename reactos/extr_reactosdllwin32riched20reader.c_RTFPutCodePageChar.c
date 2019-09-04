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
struct TYPE_3__ {int dwCPOutputCount; int dwMaxCPOutputCount; int* cpOutputBuffer; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 int* heap_realloc (int*,int) ; 

__attribute__((used)) static void
RTFPutCodePageChar(RTF_Info *info, int c)
{
        /* Use dynamic buffer here because it's the best way to handle
         * MBCS codepages without having to worry about partial chars */
        if (info->dwCPOutputCount >= info->dwMaxCPOutputCount)
        {
                info->dwMaxCPOutputCount *= 2;
                info->cpOutputBuffer = heap_realloc(info->cpOutputBuffer, info->dwMaxCPOutputCount);
        }
        info->cpOutputBuffer[info->dwCPOutputCount++] = c;
}