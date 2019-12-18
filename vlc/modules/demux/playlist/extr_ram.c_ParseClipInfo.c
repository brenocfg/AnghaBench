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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* vlc_uri_decode_duplicate (char*) ; 

__attribute__((used)) static void ParseClipInfo( const char *psz_clipinfo, char **ppsz_artist, char **ppsz_title,
                           char **ppsz_album, char **ppsz_genre, char **ppsz_year,
                           char **ppsz_cdnum, char **ppsz_comments )
{
    char *psz_option_next, *psz_option_start, *psz_param, *psz_value, *psz_suboption;
    char *psz_temp_clipinfo = strdup( psz_clipinfo );
    psz_option_start = strchr( psz_temp_clipinfo, '"' );
    if( !psz_option_start )
    {
        free( psz_temp_clipinfo );
        return;
    }

    psz_option_start++;
    psz_option_next = psz_option_start;
    while( 1 ) /* Process each sub option */
    {
        /* Get the sub option */
        psz_option_start = psz_option_next;
        psz_option_next = strchr( psz_option_start, '|' );
        if( psz_option_next )
            *psz_option_next = '\0';
        else
            psz_option_next = strchr( psz_option_start, '"' );
        if( psz_option_next )
            *psz_option_next = '\0';
        else
            psz_option_next = strchr( psz_option_start, '\0' );
        if( psz_option_next == psz_option_start )
            break;

        psz_suboption = strdup( psz_option_start );
        if( !psz_suboption )
            break;

        /* Parse out param and value */
        psz_param = psz_suboption;
        if( strchr( psz_suboption, '=' ) )
        {
            psz_value = strchr( psz_suboption, '=' ) + 1;
            *( strchr( psz_suboption, '=' ) ) = '\0';
        }
        else
        {
            free( psz_suboption );
            break;
        }
        /* Put into args */
        if( !strcmp( psz_param, "artist name" ) )
            *ppsz_artist = vlc_uri_decode_duplicate( psz_value );
        else if( !strcmp( psz_param, "title" ) )
            *ppsz_title = vlc_uri_decode_duplicate( psz_value );
        else if( !strcmp( psz_param, "album name" ) )
            *ppsz_album = vlc_uri_decode_duplicate( psz_value );
        else if( !strcmp( psz_param, "genre" ) )
            *ppsz_genre = vlc_uri_decode_duplicate( psz_value );
        else if( !strcmp( psz_param, "year" ) )
            *ppsz_year = vlc_uri_decode_duplicate( psz_value );
        else if( !strcmp( psz_param, "cdnum" ) )
            *ppsz_cdnum = vlc_uri_decode_duplicate( psz_value );
        else if( !strcmp( psz_param, "comments" ) )
            *ppsz_comments = vlc_uri_decode_duplicate( psz_value );

        free( psz_suboption );
        psz_option_next++;
    }

    free( psz_temp_clipinfo );
}