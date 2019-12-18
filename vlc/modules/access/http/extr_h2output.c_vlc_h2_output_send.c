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
struct vlc_h2_output {int /*<<< orphan*/  queue; } ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int vlc_h2_output_queue (struct vlc_h2_output*,int /*<<< orphan*/ *,struct vlc_h2_frame*) ; 

int vlc_h2_output_send(struct vlc_h2_output *out, struct vlc_h2_frame *f)
{
    return vlc_h2_output_queue(out, &out->queue, f);
}