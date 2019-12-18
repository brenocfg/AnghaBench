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
typedef  int /*<<< orphan*/  cea708_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_Window_ClearText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CEA708_Window_Init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CEA708_Window_Reset( cea708_window_t *p_w )
{
    CEA708_Window_ClearText( p_w );
    CEA708_Window_Init( p_w );
}