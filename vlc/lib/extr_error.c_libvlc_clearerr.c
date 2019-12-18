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
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free_error () ; 
 int /*<<< orphan*/  vlc_threadvar_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void libvlc_clearerr (void)
{
    free_error ();
    vlc_threadvar_set (context, NULL);
}