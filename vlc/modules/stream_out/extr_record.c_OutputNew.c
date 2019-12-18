#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_sout; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {int i_id; int /*<<< orphan*/  p_out; TYPE_3__** id; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  id; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,char*,...) ; 
 char* config_StringEscape (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  sout_StreamChainNew (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_StreamIdAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_1__*) ; 

__attribute__((used)) static int OutputNew( sout_stream_t *p_stream,
                      const char *psz_muxer, const char *psz_prefix, const char *psz_extension  )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    char *psz_file = NULL, *psz_tmp = NULL;
    char *psz_output = NULL;
    int i_count;

    if( asprintf( &psz_tmp, "%s%s%s",
                  psz_prefix, psz_extension ? "." : "", psz_extension ? psz_extension : "" ) < 0 )
    {
        goto error;
    }

    psz_file = config_StringEscape( psz_tmp );
    if( !psz_file )
    {
        free( psz_tmp );
        goto error;
    }
    free( psz_tmp );

    if( asprintf( &psz_output,
                  "std{access=file{no-append,no-format,no-overwrite},"
                  "mux=%s,dst='%s'}", psz_muxer, psz_file ) < 0 )
    {
        psz_output = NULL;
        goto error;
    }

    /* Create the output */
    msg_Dbg( p_stream, "Using record output `%s'", psz_output );

    p_sys->p_out = sout_StreamChainNew( p_stream->p_sout, psz_output, NULL, NULL );

    if( !p_sys->p_out )
        goto error;

    /* Add es */
    i_count = 0;
    for( int i = 0; i < p_sys->i_id; i++ )
    {
        sout_stream_id_sys_t *id = p_sys->id[i];

        id->id = sout_StreamIdAdd( p_sys->p_out, &id->fmt );
        if( id->id )
            i_count++;
    }

    if( psz_file && psz_extension )
        var_SetString( vlc_object_instance(p_stream), "record-file", psz_file );

    free( psz_file );
    free( psz_output );

    return i_count;

error:

    free( psz_file );
    free( psz_output );
    return -1;

}