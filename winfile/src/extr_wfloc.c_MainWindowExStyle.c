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
typedef  long DWORD ;

/* Variables and functions */
 scalar_t__ DefaultLayoutRTL () ; 
 long WS_EX_LAYOUTRTL ; 
 long WS_EX_NOINHERITLAYOUT ; 
 scalar_t__ bMirrorContent ; 

DWORD MainWindowExStyle()
{
    DWORD exStyle = 0L;

    if (DefaultLayoutRTL())
    {
        exStyle = WS_EX_LAYOUTRTL;
        if (!bMirrorContent)
            exStyle |= WS_EX_NOINHERITLAYOUT;
    }
    else
    {
        exStyle = bMirrorContent ? WS_EX_LAYOUTRTL : 0;
    }

    return exStyle;
}