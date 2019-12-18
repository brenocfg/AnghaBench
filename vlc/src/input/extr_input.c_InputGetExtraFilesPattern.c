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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  input_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_APPEND (int,char**,char*) ; 
 int /*<<< orphan*/  TAB_INIT (int,char**) ; 
 scalar_t__ asprintf (char**,char const*,char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_path (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 char* strdup (char const*) ; 
 size_t strlen (char const*) ; 
 char* vlc_path2uri (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_stat (char*,struct stat*) ; 

__attribute__((used)) static void InputGetExtraFilesPattern( input_thread_t *p_input,
                                       int *pi_list, char ***pppsz_list,
                                       const char *psz_path,
                                       const char *psz_match,
                                       const char *psz_format,
                                       int i_start, int i_stop )
{
    int i_list;
    char **ppsz_list;
    TAB_INIT( i_list, ppsz_list );

    char *psz_base = strdup( psz_path );
    if( !psz_base )
        goto exit;

    /* Remove the extension */
    char *psz_end = &psz_base[strlen(psz_base)-strlen(psz_match)];
    assert( psz_end >= psz_base);
    *psz_end = '\0';

    /* Try to list files */
    for( int i = i_start; i <= i_stop; i++ )
    {
        char *psz_probe;
        if( asprintf( &psz_probe, psz_format, psz_base, i ) < 0 )
            break;

        char *filepath = get_path( psz_probe );

        struct stat st;
        if( filepath == NULL ||
            vlc_stat( filepath, &st ) || !S_ISREG( st.st_mode ) || !st.st_size )
        {
            free( filepath );
            free( psz_probe );
            break;
        }

        msg_Dbg( p_input, "Detected extra file `%s'", filepath );

        char* psz_uri = vlc_path2uri( filepath, NULL );
        if( psz_uri )
            TAB_APPEND( i_list, ppsz_list, psz_uri );

        free( filepath );
        free( psz_probe );
    }
    free( psz_base );
exit:
    *pi_list = i_list;
    *pppsz_list = ppsz_list;
}