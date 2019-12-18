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

/* Variables and functions */
 int /*<<< orphan*/  DIR_SEP_CHAR ; 
#define  EEXIST 129 
#define  ENOENT 128 
 int errno ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strrchr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_mkdir (char const*,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int) ; 

int config_CreateDir( vlc_object_t *p_this, const char *psz_dirname )
{
    if( !psz_dirname || !*psz_dirname ) return -1;

    if( vlc_mkdir( psz_dirname, 0700 ) == 0 )
        return 0;

    switch( errno )
    {
        case EEXIST:
            return 0;

        case ENOENT:
        {
            /* Let's try to create the parent directory */
            char psz_parent[strlen( psz_dirname ) + 1], *psz_end;
            strcpy( psz_parent, psz_dirname );

            psz_end = strrchr( psz_parent, DIR_SEP_CHAR );
            if( psz_end && psz_end != psz_parent )
            {
                *psz_end = '\0';
                if( config_CreateDir( p_this, psz_parent ) == 0 )
                {
                    if( !vlc_mkdir( psz_dirname, 0700 ) )
                        return 0;
                }
            }
        }
    }

    msg_Warn( p_this, "could not create %s: %s", psz_dirname,
              vlc_strerror_c(errno) );
    return -1;
}