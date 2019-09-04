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
typedef  int UINT ;
typedef  int BOOL ;

/* Variables and functions */
 int WM_DEVICECHANGE ; 
 int WM_GETICON ; 
 int WM_GETOBJECT ; 
 int WM_SYSTIMER ; 
 int WM_TIMECHANGE ; 
 int WM_TIMER ; 

__attribute__((used)) static BOOL ignore_message( UINT message )
{
    /* these are always ignored */
    return (message >= 0xc000 ||
            message == WM_GETICON ||
            message == WM_GETOBJECT ||
            message == WM_TIMER ||
            message == WM_SYSTIMER ||
            message == WM_TIMECHANGE ||
            message == WM_DEVICECHANGE);
}