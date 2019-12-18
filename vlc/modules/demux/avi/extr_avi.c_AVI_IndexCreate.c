#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_15__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;
typedef  scalar_t__ uint32_t ;
struct TYPE_27__ {int /*<<< orphan*/  s; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_32__ {scalar_t__ i_chunk_pos; scalar_t__ i_chunk_size; } ;
struct TYPE_28__ {unsigned int i_track; TYPE_4__** track; scalar_t__ b_odml; TYPE_7__ ck_root; int /*<<< orphan*/  i_movi_lastchunk_pos; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_25__ {int /*<<< orphan*/  i_size; } ;
struct TYPE_26__ {scalar_t__ i_cat; int /*<<< orphan*/  i_codec; } ;
struct TYPE_29__ {TYPE_15__ idx; TYPE_1__ fmt; } ;
typedef  TYPE_4__ avi_track_t ;
struct TYPE_30__ {size_t i_stream; scalar_t__ i_cat; int i_fourcc; scalar_t__ i_pos; scalar_t__ i_size; int /*<<< orphan*/  i_peek; } ;
typedef  TYPE_5__ avi_packet_t ;
struct TYPE_31__ {int i_id; scalar_t__ i_pos; scalar_t__ i_length; scalar_t__ i_lengthtotal; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_6__ avi_entry_t ;
typedef  TYPE_7__ avi_chunk_list_t ;

/* Variables and functions */
#define  AVIFOURCC_JUNK 131 
#define  AVIFOURCC_RIFF 130 
#define  AVIFOURCC_idx1 129 
 int AVIFOURCC_movi ; 
#define  AVIFOURCC_rec 128 
 TYPE_7__* AVI_ChunkFind (TYPE_7__*,int,int,int) ; 
 int /*<<< orphan*/  AVI_GetKeyFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AVI_PacketGetHeader (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ AVI_PacketNext (TYPE_2__*) ; 
 int /*<<< orphan*/  AVI_PacketSearch (TYPE_2__*) ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ __MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  avi_index_Append (TYPE_15__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  avi_index_Init (TYPE_15__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int stream_Size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_dialog_display_progress (TYPE_2__*,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_dialog_is_cancelled (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_release (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_update_progress (TYPE_2__*,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  vlc_stream_Seek (int /*<<< orphan*/ ,scalar_t__) ; 
 double vlc_stream_Tell (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void AVI_IndexCreate( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    avi_chunk_list_t *p_riff;
    avi_chunk_list_t *p_movi;

    unsigned int i_stream;
    uint32_t i_movi_end;

    vlc_tick_t i_dialog_update;
    vlc_dialog_id *p_dialog_id = NULL;

    p_riff = AVI_ChunkFind( &p_sys->ck_root, AVIFOURCC_RIFF, 0, true );
    p_movi = AVI_ChunkFind( p_riff, AVIFOURCC_movi, 0, true );

    if( !p_movi )
    {
        msg_Err( p_demux, "cannot find p_movi" );
        return;
    }

    for( i_stream = 0; i_stream < p_sys->i_track; i_stream++ )
        avi_index_Init( &p_sys->track[i_stream]->idx );

    i_movi_end = __MIN( (uint32_t)(p_movi->i_chunk_pos + p_movi->i_chunk_size),
                        stream_Size( p_demux->s ) );

    vlc_stream_Seek( p_demux->s, p_movi->i_chunk_pos + 12 );
    msg_Warn( p_demux, "creating index from LIST-movi, will take time !" );


    /* Only show dialog if AVI is > 10MB */
    i_dialog_update = vlc_tick_now();
    if( stream_Size( p_demux->s ) > 10000000 )
    {
        p_dialog_id =
            vlc_dialog_display_progress( p_demux, false, 0.0, _("Cancel"),
                                         _("Broken or missing AVI Index"),
                                         _("Fixing AVI Index...") );
    }

    for( ;; )
    {
        avi_packet_t pk;

        /* Don't update/check dialog too often */
        if( p_dialog_id != NULL && vlc_tick_now() - i_dialog_update > VLC_TICK_FROM_MS(100) )
        {
            if( vlc_dialog_is_cancelled( p_demux, p_dialog_id ) )
                break;

            double f_current = vlc_stream_Tell( p_demux->s );
            double f_size    = stream_Size( p_demux->s );
            double f_pos     = f_current / f_size;
            vlc_dialog_update_progress( p_demux, p_dialog_id, f_pos );

            i_dialog_update = vlc_tick_now();
        }

        if( AVI_PacketGetHeader( p_demux, &pk ) )
            break;

        if( pk.i_stream < p_sys->i_track &&
            pk.i_cat == p_sys->track[pk.i_stream]->fmt.i_cat )
        {
            avi_track_t *tk = p_sys->track[pk.i_stream];

            avi_entry_t index;
            index.i_id      = pk.i_fourcc;
            index.i_flags   = AVI_GetKeyFlag(tk->fmt.i_codec, pk.i_peek);
            index.i_pos     = pk.i_pos;
            index.i_length  = pk.i_size;
            index.i_lengthtotal = pk.i_size;
            avi_index_Append( &tk->idx, &p_sys->i_movi_lastchunk_pos, &index );
        }
        else
        {
            switch( pk.i_fourcc )
            {
            case AVIFOURCC_idx1:
                if( p_sys->b_odml )
                {
                    avi_chunk_list_t *p_sysx;
                    p_sysx = AVI_ChunkFind( &p_sys->ck_root,
                                            AVIFOURCC_RIFF, 1, true );

                    msg_Dbg( p_demux, "looking for new RIFF chunk" );
                    if( !p_sysx || vlc_stream_Seek( p_demux->s,
                                         p_sysx->i_chunk_pos + 24 ) )
                        goto print_stat;
                    break;
                }
                goto print_stat;

            case AVIFOURCC_RIFF:
                    msg_Dbg( p_demux, "new RIFF chunk found" );
                    break;

            case AVIFOURCC_rec:
            case AVIFOURCC_JUNK:
                break;

            default:
                msg_Warn( p_demux, "need resync, probably broken avi" );
                if( AVI_PacketSearch( p_demux ) )
                {
                    msg_Warn( p_demux, "lost sync, abord index creation" );
                    goto print_stat;
                }
            }
        }

        if( ( !p_sys->b_odml && pk.i_pos + pk.i_size >= i_movi_end ) ||
            AVI_PacketNext( p_demux ) )
        {
            break;
        }
    }

print_stat:
    if( p_dialog_id != NULL )
        vlc_dialog_release( p_demux, p_dialog_id );

    for( i_stream = 0; i_stream < p_sys->i_track; i_stream++ )
    {
        msg_Dbg( p_demux, "stream[%d] creating %d index entries",
                i_stream, p_sys->track[i_stream]->idx.i_size );
    }
}