#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_t ;

/* Variables and functions */
 scalar_t__ exactMatch (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* var_CreateGetString (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void checkAccessMux( sout_stream_t *p_stream, char *psz_access,
                            char *psz_mux )
{
    if( exactMatch( psz_access, "mmsh", 4 ) && !exactMatch( psz_mux, "asfh", 4 ) )
        msg_Err( p_stream, "mmsh output is only valid with asfh mux" );
    else if( !exactMatch( psz_access, "file", 4 ) &&
             ( exactMatch( psz_mux, "mov", 3 ) || exactMatch( psz_mux, "mp4", 3 ) ) )
        msg_Err( p_stream, "mov and mp4 mux are only valid with file output" );
    else if( exactMatch( psz_access, "udp", 3 ) )
    {
        if( exactMatch( psz_mux, "ffmpeg", 6 ) || exactMatch( psz_mux, "avformat", 8 ) )
        {   /* why would you use ffmpeg's ts muxer ? YOU DON'T LOVE VLC ??? */
            char *psz_ffmpeg_mux = var_CreateGetString( p_stream, "sout-avformat-mux" );
            if( !psz_ffmpeg_mux || strncmp( psz_ffmpeg_mux, "mpegts", 6 ) )
                msg_Err( p_stream, "UDP output is only valid with TS mux" );
            free( psz_ffmpeg_mux );
        }
        else if( !exactMatch( psz_mux, "ts", 2 ) )
            msg_Err( p_stream, "UDP output is only valid with TS mux" );
    }
}