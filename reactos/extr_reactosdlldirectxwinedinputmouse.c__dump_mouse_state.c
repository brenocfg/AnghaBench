#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * rgbButtons; int /*<<< orphan*/  lZ; int /*<<< orphan*/  lY; int /*<<< orphan*/  lX; } ;
typedef  TYPE_1__ DIMOUSESTATE2 ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dinput ; 

__attribute__((used)) static void _dump_mouse_state(const DIMOUSESTATE2 *m_state)
{
    int i;

    if (!TRACE_ON(dinput)) return;

    TRACE("(X: %d Y: %d Z: %d", m_state->lX, m_state->lY, m_state->lZ);
    for (i = 0; i < 5; i++) TRACE(" B%d: %02x", i, m_state->rgbButtons[i]);
    TRACE(")\n");
}