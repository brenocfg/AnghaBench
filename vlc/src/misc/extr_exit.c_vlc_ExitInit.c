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
struct TYPE_3__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/ * handler; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_exit_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

void vlc_ExitInit( vlc_exit_t *exit )
{
    vlc_mutex_init( &exit->lock );
    exit->handler = NULL;
    exit->opaque = NULL;
}