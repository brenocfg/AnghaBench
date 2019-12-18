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
struct TYPE_3__ {int b_configured; int b_seen; int /*<<< orphan*/  fmt; void* i_last_pts; void* i_first_pts; int /*<<< orphan*/ * es; scalar_t__ i_next_block_flags; scalar_t__ i_id; scalar_t__ i_skip; } ;
typedef  TYPE_1__ ps_track_t ;

/* Variables and functions */
 int PS_TK_COUNT ; 
 int /*<<< orphan*/  UNKNOWN_ES ; 
 void* VLC_TICK_INVALID ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ps_track_init( ps_track_t tk[PS_TK_COUNT] )
{
    int i;
    for( i = 0; i < PS_TK_COUNT; i++ )
    {
        tk[i].b_configured = false;
        tk[i].b_seen = false;
        tk[i].i_skip = 0;
        tk[i].i_id   = 0;
        tk[i].i_next_block_flags = 0;
        tk[i].es     = NULL;
        tk[i].i_first_pts = VLC_TICK_INVALID;
        tk[i].i_last_pts = VLC_TICK_INVALID;
        es_format_Init( &tk[i].fmt, UNKNOWN_ES, 0 );
    }
}