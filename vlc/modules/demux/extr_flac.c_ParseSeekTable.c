#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {scalar_t__ i_byte_offset; int /*<<< orphan*/  i_time_offset; } ;
typedef  TYPE_1__ flac_seekpoint_t ;
struct TYPE_10__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_11__ {int i_seekpoint; TYPE_6__** seekpoint; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_12__ {scalar_t__ i_byte_offset; int /*<<< orphan*/  i_time_offset; } ;

/* Variables and functions */
 scalar_t__ FLAC_STREAMINFO_SIZE ; 
 scalar_t__ GetQWBE (int /*<<< orphan*/  const*) ; 
 scalar_t__ const INT64_MAX ; 
 int /*<<< orphan*/  TAB_APPEND (int,TYPE_6__**,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_tick_from_samples (scalar_t__ const,unsigned int) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static void ParseSeekTable( demux_t *p_demux, const uint8_t *p_data, size_t i_data,
                            unsigned i_sample_rate )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    flac_seekpoint_t *s;
    size_t i;

    if( i_sample_rate == 0 )
        return;

    /* */
    for( i = 0; i < (i_data-4)/18; i++ )
    {
        const int64_t i_sample = GetQWBE( &p_data[4+18*i+0] );
        int j;

        if( i_sample < 0 || i_sample >= INT64_MAX ||
            GetQWBE( &p_data[4+18*i+8] ) < FLAC_STREAMINFO_SIZE )
            break;

        s = xmalloc( sizeof (*s) );
        s->i_time_offset = vlc_tick_from_samples(i_sample, i_sample_rate);
        s->i_byte_offset = GetQWBE( &p_data[4+18*i+8] );

        /* Check for duplicate entry */
        for( j = 0; j < p_sys->i_seekpoint; j++ )
        {
            if( p_sys->seekpoint[j]->i_time_offset == s->i_time_offset ||
                p_sys->seekpoint[j]->i_byte_offset == s->i_byte_offset )
            {
                free( s );
                s = NULL;
                break;
            }
        }
        if( s )
        {
            TAB_APPEND( p_sys->i_seekpoint, p_sys->seekpoint, s );
        }
    }
    /* TODO sort it by size and remove wrong seek entry (time not increasing) */
}