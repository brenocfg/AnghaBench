#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  size_t ULONG ;
typedef  int UCHAR ;
struct TYPE_3__ {int Asuchar; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
typedef  scalar_t__* PUSHORT ;

/* Variables and functions */
 size_t GLOBAL_SCREEN_WIDTH ; 
 TYPE_2__ attr ; 
 scalar_t__ pScreenBufferVga ; 

void PrintGrafVga(ULONG x,ULONG y,UCHAR c)
{
    ((PUSHORT)pScreenBufferVga)[y*GLOBAL_SCREEN_WIDTH + x] = (USHORT)((attr.u.Asuchar<<8)|c);
}