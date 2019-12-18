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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* nscdec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int ParseLine ( demux_t *p_demux, char *psz_line )
{
    char        *psz_bol;
    char        *psz_value;

    psz_bol = psz_line;
    /* Remove unnecessary tabs or spaces at the beginning of line */
    while( *psz_bol == ' ' || *psz_bol == '\t' ||
           *psz_bol == '\n' || *psz_bol == '\r' )
    {
        psz_bol++;
    }
    psz_value = strchr( psz_bol, '=' );
    if( psz_value == NULL )
    {
        return 0; /* a [Address] or [Formats] line or something else we will ignore */
    }
    *psz_value = '\0';
    psz_value++;
 
    if( !strncasecmp( psz_value, "0x", 2 ) )
    {
        int i_value;
        sscanf( psz_value, "%x", &i_value );
        msg_Dbg( p_demux, "%s = %d", psz_bol, i_value );
    }
    else if( !strncasecmp( psz_bol, "Format", 6 ) )
    {
        msg_Dbg( p_demux, "%s = asf header", psz_bol );
    }
    else
    {
        /* This should be NSC encoded strings in the values */
        char *psz_out;
        psz_out = nscdec( (vlc_object_t *)p_demux, psz_value );
        if( psz_out )
        {
            msg_Dbg( p_demux, "%s = %s", psz_bol, psz_out );
            free( psz_out );
        }
    }
    return VLC_SUCCESS;
}