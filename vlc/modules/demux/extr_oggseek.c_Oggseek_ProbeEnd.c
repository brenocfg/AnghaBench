#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ unsynced; } ;
typedef  TYPE_1__ ogg_sync_state ;
typedef  int /*<<< orphan*/  ogg_stream_state ;
typedef  int /*<<< orphan*/  ogg_page ;
typedef  scalar_t__ int64_t ;
struct TYPE_14__ {int /*<<< orphan*/  s; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_15__ {int i_streams; scalar_t__ i_length; TYPE_11__** pp_stream; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_12__ {scalar_t__ i_serial_no; int /*<<< orphan*/  b_contiguous; } ;

/* Variables and functions */
 int MAX_PAGE_SIZE ; 
 int OGGSEEK_BYTES_TO_READ ; 
 scalar_t__ Ogg_GranuleToTime (TYPE_11__*,scalar_t__,int,int) ; 
 scalar_t__ SEC_FROM_VLC_TICK (scalar_t__) ; 
 int UINT_MAX ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ __MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ogg_page_granulepos (int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_page_serialno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_init (int /*<<< orphan*/ *,int) ; 
 char* ogg_sync_buffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ogg_sync_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  ogg_sync_init (TYPE_1__*) ; 
 int ogg_sync_pageout (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_sync_pageseek (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_sync_wrote (TYPE_1__*,scalar_t__) ; 
 scalar_t__ stream_Size (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ ) ; 

void Oggseek_ProbeEnd( demux_t *p_demux )
{
    /* Temporary state */
    ogg_stream_state os;
    ogg_sync_state oy;
    ogg_page page;
    demux_sys_t *p_sys = p_demux->p_sys;
    int64_t i_pos, i_startpos, i_result, i_granule, i_lowerbound;
    int64_t i_length = 0;
    int64_t i_backup_pos = vlc_stream_Tell( p_demux->s );
    int64_t i_upperbound = stream_Size( p_demux->s );
    unsigned int i_backoffset = OGGSEEK_BYTES_TO_READ;
    assert( OGGSEEK_BYTES_TO_READ < UINT_MAX );

    const char *buffer;

    ogg_stream_init( &os, -1 );
    ogg_sync_init( &oy );

    /* Try to lookup last granule from each logical stream */
    i_lowerbound = stream_Size( p_demux->s ) - p_sys->i_streams * MAX_PAGE_SIZE * 2;
    i_lowerbound = __MAX( 0, i_lowerbound );

    i_pos = i_startpos = __MAX( i_lowerbound, i_upperbound - i_backoffset );

    if ( vlc_stream_Seek( p_demux->s, i_pos ) )
    {
        ogg_sync_clear( &oy );
        ogg_stream_clear( &os );
        return;
    }

    while( i_pos >= i_lowerbound )
    {

        while( i_pos < i_upperbound )
        {
            if ( oy.unsynced )
                i_result = ogg_sync_pageseek( &oy, &page );

            buffer = ogg_sync_buffer( &oy, OGGSEEK_BYTES_TO_READ );
            if ( buffer == NULL ) goto clean;
            i_result = vlc_stream_Read( p_demux->s, (void*) buffer, OGGSEEK_BYTES_TO_READ );
            if ( i_result < 1 ) goto clean;
            i_pos += i_result;
            ogg_sync_wrote( &oy, i_result );

            while( ogg_sync_pageout( &oy, &page ) == 1 )
            {
                i_granule = ogg_page_granulepos( &page );
                if ( i_granule == -1 ) continue;

                for ( int i=0; i< p_sys->i_streams; i++ )
                {
                    if ( p_sys->pp_stream[i]->i_serial_no != ogg_page_serialno( &page ) )
                        continue;

                    i_length = Ogg_GranuleToTime( p_sys->pp_stream[i], i_granule,
                                                  !p_sys->pp_stream[i]->b_contiguous, false );
                    if( i_length != VLC_TICK_INVALID )
                    {
                        /* We found at least a page with valid granule */
                        p_sys->i_length = __MAX( p_sys->i_length, SEC_FROM_VLC_TICK(i_length - VLC_TICK_0) );
                        goto clean;
                    }
                    break;
                }
            }
        }

        /* Otherwise increase read size, starting earlier */
        if ( i_backoffset <= ( UINT_MAX >> 1 ) )
        {
            i_backoffset <<= 1;
            i_startpos = i_upperbound - i_backoffset;
        }
        else
        {
            i_startpos -= i_backoffset;
        }
        i_pos = i_startpos;

        if ( vlc_stream_Seek( p_demux->s, i_pos ) )
            break;
    }

clean:
    vlc_stream_Seek( p_demux->s, i_backup_pos );

    ogg_sync_clear( &oy );
    ogg_stream_clear( &os );
}