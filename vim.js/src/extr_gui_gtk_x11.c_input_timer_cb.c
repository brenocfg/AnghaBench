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
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gint ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TRUE ; 

__attribute__((used)) static gint
input_timer_cb(gpointer data)
{
    int *timed_out = (int *) data;

    /* Just inform the caller about the occurrence of it */
    *timed_out = TRUE;

    return FALSE;		/* don't happen again */
}