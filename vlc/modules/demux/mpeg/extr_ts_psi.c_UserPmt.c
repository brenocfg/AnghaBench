#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_28__ {int i_number; unsigned long i_pid_pcr; int /*<<< orphan*/  e_streams; int /*<<< orphan*/  handle; } ;
typedef  TYPE_4__ ts_pmt_t ;
struct TYPE_27__ {TYPE_20__* p_stream; TYPE_1__* p_pat; TYPE_4__* p_pmt; } ;
struct TYPE_29__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_5__ ts_pid_t ;
struct TYPE_30__ {int b_packetized; int i_group; unsigned long i_id; int i_cat; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_6__ es_format_t ;
struct TYPE_31__ {int /*<<< orphan*/  out; TYPE_8__* p_sys; } ;
typedef  TYPE_7__ demux_t ;
struct TYPE_32__ {int b_user_pmt; int /*<<< orphan*/  i_pmt_es; scalar_t__ b_es_id_pid; } ;
typedef  TYPE_8__ demux_sys_t ;
struct TYPE_26__ {int /*<<< orphan*/  id; TYPE_6__ fmt; } ;
struct TYPE_25__ {TYPE_2__* p_es; int /*<<< orphan*/  transport; } ;
struct TYPE_24__ {int /*<<< orphan*/  programs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_APPEND (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int AUDIO_ES ; 
 TYPE_5__* GetPID (TYPE_8__*,unsigned long) ; 
 int /*<<< orphan*/  PIDFillFormat (TYPE_7__*,TYPE_20__*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PIDRelease (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  PIDSetup (TYPE_7__*,int /*<<< orphan*/ ,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  PMTCallBack ; 
 int SPU_ES ; 
 int TS_USER_PMT_NUMBER ; 
 scalar_t__ TYPE_FREE ; 
 int /*<<< orphan*/  TYPE_PMT ; 
 int /*<<< orphan*/  TYPE_STREAM ; 
 int UNKNOWN_ES ; 
 int VIDEO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dvbpsi_pmt_attach (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  es_format_Change (TYPE_6__*,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_7__*,char*,unsigned long,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 
 void* strtol (char*,char**,int /*<<< orphan*/ ) ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 

int UserPmt( demux_t *p_demux, const char *psz_fmt )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    char *psz_dup = strdup( psz_fmt );
    char *psz = psz_dup;
    int  i_number;

    if( !psz_dup )
        return VLC_ENOMEM;

    /* Parse PID */
    unsigned long i_pid = strtoul( psz, &psz, 0 );
    if( i_pid < 2 || i_pid >= 8192 )
        goto error;

    /* Parse optional program number */
    i_number = 0;
    if( *psz == ':' )
        i_number = strtol( &psz[1], &psz, 0 );

    /* */
    ts_pid_t *pmtpid = GetPID(p_sys, i_pid);

    msg_Dbg( p_demux, "user pmt specified (pid=%lu,number=%d)", i_pid, i_number );
    if ( !PIDSetup( p_demux, TYPE_PMT, pmtpid, GetPID(p_sys, 0) ) )
        goto error;

    /* Dummy PMT */
    ts_pmt_t *p_pmt = pmtpid->u.p_pmt;
    p_pmt->i_number   = i_number != 0 ? i_number : TS_USER_PMT_NUMBER;
    if( !dvbpsi_pmt_attach( p_pmt->handle,
                            ((i_number != TS_USER_PMT_NUMBER ? i_number : 1)),
                            PMTCallBack, p_demux ) )
    {
        PIDRelease( p_demux, pmtpid );
        goto error;
    }

    ARRAY_APPEND( GetPID(p_sys, 0)->u.p_pat->programs, pmtpid );

    psz = strchr( psz, '=' );
    if( psz )
        psz++;
    while( psz && *psz )
    {
        char *psz_next = strchr( psz, ',' );

        if( psz_next )
            *psz_next++ = '\0';

        i_pid = strtoul( psz, &psz, 0 );
        if( *psz != ':' || i_pid < 2 || i_pid >= 8192 )
            goto next;

        char *psz_opt = &psz[1];
        if( !strcmp( psz_opt, "pcr" ) )
        {
            p_pmt->i_pid_pcr = i_pid;
        }
        else if( GetPID(p_sys, i_pid)->type == TYPE_FREE )
        {
            ts_pid_t *pid = GetPID(p_sys, i_pid);

            char *psz_arg = strchr( psz_opt, '=' );
            if( psz_arg )
                *psz_arg++ = '\0';

            if ( !PIDSetup( p_demux, TYPE_STREAM, pid, pmtpid ) )
                continue;

            ARRAY_APPEND( p_pmt->e_streams, pid );

            if( p_pmt->i_pid_pcr <= 0 )
                p_pmt->i_pid_pcr = i_pid;

            es_format_t *fmt = &pid->u.p_stream->p_es->fmt;

            if( psz_arg && strlen( psz_arg ) == 4 )
            {
                const vlc_fourcc_t i_codec = VLC_FOURCC( psz_arg[0], psz_arg[1],
                                                         psz_arg[2], psz_arg[3] );
                int i_cat = UNKNOWN_ES;

                if( !strcmp( psz_opt, "video" ) )
                    i_cat = VIDEO_ES;
                else if( !strcmp( psz_opt, "audio" ) )
                    i_cat = AUDIO_ES;
                else if( !strcmp( psz_opt, "spu" ) )
                    i_cat = SPU_ES;

                es_format_Change( fmt, i_cat, i_codec );
                fmt->b_packetized = false;
            }
            else
            {
                const int i_stream_type = strtol( psz_opt, NULL, 0 );
                PIDFillFormat( p_demux, pid->u.p_stream, i_stream_type, &pid->u.p_stream->transport );
            }

            fmt->i_group = i_number;
            if( p_sys->b_es_id_pid )
                fmt->i_id = i_pid;

            if( fmt->i_cat != UNKNOWN_ES )
            {
                msg_Dbg( p_demux, "  * es pid=%lu fcc=%4.4s", i_pid,
                         (char*)&fmt->i_codec );
                pid->u.p_stream->p_es->id = es_out_Add( p_demux->out, fmt );
                p_sys->i_pmt_es++;
            }
        }

    next:
        psz = psz_next;
    }

    p_sys->b_user_pmt = true;
    free( psz_dup );
    return VLC_SUCCESS;

error:
    free( psz_dup );
    return VLC_EGENERIC;
}