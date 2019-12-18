#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_8__ {scalar_t__ i_pos; TYPE_1__* tk; scalar_t__ i_used; scalar_t__ i_tk; scalar_t__ i_offset; } ;
typedef  TYPE_3__ stream_sys_t ;
struct TYPE_6__ {scalar_t__ i_end; scalar_t__ i_start; scalar_t__ date; } ;

/* Variables and functions */
 int /*<<< orphan*/  AStreamPrebufferStream (TYPE_2__*) ; 
 unsigned int STREAM_CACHE_TRACK ; 

__attribute__((used)) static void AStreamControlReset(stream_t *s)
{
    stream_sys_t *sys = s->p_sys;

    sys->i_pos = 0;

    /* Setup our tracks */
    sys->i_offset = 0;
    sys->i_tk     = 0;
    sys->i_used   = 0;

    for (unsigned i = 0; i < STREAM_CACHE_TRACK; i++)
    {
        sys->tk[i].date  = 0;
        sys->tk[i].i_start = sys->i_pos;
        sys->tk[i].i_end   = sys->i_pos;
    }

    /* Do the prebuffering */
    AStreamPrebufferStream(s);
}