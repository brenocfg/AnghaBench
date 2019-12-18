#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ i_start; scalar_t__ i_stop; } ;
typedef  TYPE_1__ webvtt_cue_t ;

/* Variables and functions */

__attribute__((used)) static int cue_Compare( const void *a_, const void *b_ )
{
    webvtt_cue_t *a = (webvtt_cue_t *)a_;
    webvtt_cue_t *b = (webvtt_cue_t *)b_;
    if( a->i_start == b->i_start )
    {
        if( a->i_stop > b->i_stop )
            return -1;
        else
            return ( a->i_stop < b->i_stop ) ? 1 : 0;
    }
    else return a->i_start < b->i_start ? -1 : 1;
}