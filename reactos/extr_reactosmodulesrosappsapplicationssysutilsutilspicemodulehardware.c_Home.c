#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
struct TYPE_2__ {scalar_t__ usCurY; scalar_t__ usCurX; } ;

/* Variables and functions */
 TYPE_1__* wWindow ; 

void Home(USHORT Window)
{
	wWindow[Window].usCurX=0;
    wWindow[Window].usCurY=0;

}