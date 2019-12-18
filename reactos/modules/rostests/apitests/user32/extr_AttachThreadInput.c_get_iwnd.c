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
struct TYPE_2__ {scalar_t__ hWnd; } ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 TYPE_1__* data ; 

__attribute__((used)) static int get_iwnd(HWND hWnd)
{
    if(hWnd == data[0].hWnd) return 0;
    else if(hWnd == data[1].hWnd) return 1;
    else if(hWnd == data[2].hWnd) return 2;
    else if(hWnd == data[3].hWnd) return 3;
    else if(hWnd == data[4].hWnd) return 4;
    else return -1;
}