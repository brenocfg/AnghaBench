#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct vlc_h2_frame* first; } ;
struct TYPE_3__ {struct vlc_h2_frame* first; } ;
struct vlc_h2_output {TYPE_2__ queue; TYPE_1__ prio; } ;
struct vlc_h2_frame {struct vlc_h2_frame* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 

__attribute__((used)) static void vlc_h2_output_flush_unlocked(struct vlc_h2_output *out)
{
    for (struct vlc_h2_frame *f = out->prio.first, *n; f != NULL; f = n)
    {
        n = f->next;
        free(f);
    }
    for (struct vlc_h2_frame *f = out->queue.first, *n; f != NULL; f = n)
    {
        n = f->next;
        free(f);
    }
}