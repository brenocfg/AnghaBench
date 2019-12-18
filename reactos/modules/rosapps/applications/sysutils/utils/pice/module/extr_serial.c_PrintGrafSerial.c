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
typedef  size_t ULONG ;
typedef  void* UCHAR ;

/* Variables and functions */
 size_t GLOBAL_SCREEN_WIDTH ; 
 void** flush_buffer ; 
 size_t g_x ; 
 size_t g_y ; 
 void** pScreenBufferSerial ; 
 scalar_t__ ulFlushBufferPos ; 

void PrintGrafSerial(ULONG x,ULONG y,UCHAR c)
{
    // put this into memory
    pScreenBufferSerial[y*GLOBAL_SCREEN_WIDTH + x] = c;

    // put this into cache
    if(ulFlushBufferPos == 0)
    {
        g_x = x;
        g_y = y;
    }

    flush_buffer[ulFlushBufferPos++] = c;
}