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

/* Variables and functions */
 int /*<<< orphan*/  ES_CONTINUOUS ; 
 int /*<<< orphan*/  SetThreadExecutionState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 

__attribute__((used)) static void RestoreStateOnCancel( void* p_opaque )
{
    VLC_UNUSED(p_opaque);
    SetThreadExecutionState( ES_CONTINUOUS );
}