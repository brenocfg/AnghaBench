#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_11__ {int i_data_peeked; char* p_peek; int /*<<< orphan*/  psz_separator; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int CheckMimeHeader (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  Peek (TYPE_1__*,int) ; 
 int SendBlock (TYPE_1__*,int) ; 
 int VLC_DEMUXER_EOF ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int MimeDemux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int         i_size, i;

    bool  b_match = CheckMimeHeader( p_demux, &i_size );

    if( i_size > 0 )
    {
        if( vlc_stream_Read( p_demux->s, NULL, i_size ) != i_size )
            return VLC_DEMUXER_EOF;
    }
    else if( i_size < 0 )
    {
        return VLC_DEMUXER_EOF;
    }
    else
    {
        // No MIME header, assume OK
        b_match = true;
    }

    if( !Peek( p_demux, true ) )
    {
        msg_Warn( p_demux, "cannot peek data" );
        return VLC_DEMUXER_EOF;
    }

    i = 0;
    i_size = strlen( p_sys->psz_separator ) + 2;
    if( p_sys->i_data_peeked < i_size )
    {
        msg_Warn( p_demux, "data shortage" );
        return VLC_DEMUXER_EOF;
    }

    for( ;; )
    {
        while( !( p_sys->p_peek[i] == '-' && p_sys->p_peek[i+1] == '-' ) )
        {
            i++;
            i_size++;
            if( i_size >= p_sys->i_data_peeked )
            {
                msg_Dbg( p_demux, "MIME boundary not found in %d bytes of "
                         "data", p_sys->i_data_peeked );

                if( !Peek( p_demux, false ) )
                {
                    msg_Warn( p_demux, "no more data is available at the "
                              "moment" );
                    return VLC_DEMUXER_EOF;
                }
            }
        }

        /* Handle old and new style of separators */
        if (!strncmp(p_sys->psz_separator, (char *)(p_sys->p_peek + i + 2),
                     strlen( p_sys->psz_separator ))
         || ((strlen(p_sys->psz_separator) > 4)
          && !strncmp(p_sys->psz_separator, "--", 2)
          && !strncmp(p_sys->psz_separator, (char *)(p_sys->p_peek + i),
                      strlen( p_sys->psz_separator))))
        {
            break;
        }

        i++;
        i_size++;
    }

    if( !b_match )
    {
        msg_Err( p_demux, "discard non-JPEG part" );
        return VLC_DEMUXER_EOF;
    }

    return SendBlock( p_demux, i );
}