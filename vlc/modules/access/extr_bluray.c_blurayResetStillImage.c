#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {scalar_t__ i_still_end_time; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_RESET_PCR ; 
 scalar_t__ STILL_IMAGE_NOT_SET ; 
 int /*<<< orphan*/  blurayRestartParser (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blurayResetStillImage( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if (p_sys->i_still_end_time != STILL_IMAGE_NOT_SET) {
        p_sys->i_still_end_time = STILL_IMAGE_NOT_SET;

        blurayRestartParser(p_demux, false, false);
        es_out_Control( p_demux->out, ES_OUT_RESET_PCR );
    }
}