#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  psz_channel; } ;
typedef  TYPE_1__ scan_list_entry_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  scan_list_dvbv5_entry_fill (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  scan_list_entry_Delete (TYPE_1__*) ; 
 TYPE_1__* scan_list_entry_New () ; 
 scalar_t__ scan_list_entry_add (TYPE_1__***,TYPE_1__*) ; 
 int /*<<< orphan*/  scan_token_strip (char const**,size_t*) ; 
 int /*<<< orphan*/  strndup (char const*,size_t) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/ * vlc_fopen (char const*,char*) ; 

scan_list_entry_t * scan_list_dvbv5_load( vlc_object_t *p_obj, const char *psz_source, size_t *pi_count )
{
    FILE *p_file = vlc_fopen( psz_source, "r" );
    if( !p_file )
    {
        msg_Err( p_obj, "failed to open dvbv5 file (%s)", psz_source );
        return NULL;
    }

    scan_list_entry_t *p_list = NULL;
    scan_list_entry_t **pp_list_last = &p_list;
    scan_list_entry_t *p_entry = NULL;
    *pi_count = 0;

    char *psz_line = NULL;
    size_t i_len = 0;
    ssize_t i_read;
    bool b_error = false;

    while ( (i_read = getline( &psz_line, &i_len, p_file )) != -1 && !b_error )
    {
        const char *p = psz_line;

        for ( ; *p == ' ' || *p == '\t'; p++ )
            i_read--;

        switch( *p )
        {
            case 0:
            case '\n':
            case '#': /* comment line */
                continue;
            case '[':
            {
                if( p_entry && scan_list_entry_add( &pp_list_last, p_entry ) )
                    (*pi_count)++;
                p_entry = scan_list_entry_New();
                if( !p_entry )
                {
                    b_error = true;
                }
                else
                {
                    char *p_end = strstr( p, "]" );
                    if( !p_end )
                        b_error = true;
                    else
                    {
                        const char *psz_name = p + 1;
                        size_t i_len_name = p_end - p - 1;
                        scan_token_strip( &psz_name, &i_len_name );
                        p_entry->psz_channel = strndup( psz_name, i_len_name );
                    }
                }
                break;
            }

            default:
            {
                if( p_entry )
                    scan_list_dvbv5_entry_fill( p_entry, p, i_read );
                break;
            }
        }

    }

    if( p_entry )
    {
        if( b_error )
            scan_list_entry_Delete( p_entry );
        else if( scan_list_entry_add( &pp_list_last, p_entry ) )
            (*pi_count)++;
    }

    free( psz_line );
    fclose( p_file );

    return p_list;
}