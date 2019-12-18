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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  input_thread_t ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strrchr (char const*,char) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stat (char*,struct stat*) ; 

__attribute__((used)) static char *input_SubtitleFile2Uri( input_thread_t *p_input,
                                     const char *psz_subtitle )
{
    /* if we are provided a subtitle.sub file,
     * see if we don't have a subtitle.idx and use it instead */
    char *psz_idxpath = NULL;
    char *psz_extension = strrchr( psz_subtitle, '.');
    if( psz_extension && strcmp( psz_extension, ".sub" ) == 0 )
    {
        psz_idxpath = strdup( psz_subtitle );
        if( psz_idxpath )
        {
            struct stat st;

            psz_extension = psz_extension - psz_subtitle + psz_idxpath;
            strcpy( psz_extension, ".idx" );

            if( !vlc_stat( psz_idxpath, &st ) && S_ISREG( st.st_mode ) )
            {
                msg_Dbg( p_input, "using %s as subtitle file instead of %s",
                         psz_idxpath, psz_subtitle );
                psz_subtitle = psz_idxpath;
            }
        }
    }

    char *psz_uri = vlc_path2uri( psz_subtitle, NULL );
    free( psz_idxpath );
    return psz_uri;
}