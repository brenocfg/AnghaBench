#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ huser_dll; } ;
typedef  TYPE_1__ win32_gesture_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void CloseGestures( win32_gesture_sys_t *p_gesture )
{
    if (p_gesture && p_gesture->huser_dll )
        FreeLibrary( p_gesture->huser_dll );
    free( p_gesture );
}