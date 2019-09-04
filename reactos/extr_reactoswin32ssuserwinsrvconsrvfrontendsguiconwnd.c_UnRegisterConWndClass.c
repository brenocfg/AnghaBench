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
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_CONWND_CLASS ; 
 int /*<<< orphan*/  UnregisterClassW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN
UnRegisterConWndClass(HINSTANCE hInstance)
{
    return !!UnregisterClassW(GUI_CONWND_CLASS, hInstance);
}