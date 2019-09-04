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
typedef  int /*<<< orphan*/ * PBOOLEAN ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DoubleHeight ; 
 int /*<<< orphan*/  DoubleWidth ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GraphicsConsoleBuffer ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN VgaGetDoubleVisionState(PBOOLEAN Horizontal, PBOOLEAN Vertical)
{
    if (GraphicsConsoleBuffer == NULL) return FALSE;
    if (Horizontal) *Horizontal = DoubleWidth;
    if (Vertical)   *Vertical   = DoubleHeight;
    return TRUE;
}