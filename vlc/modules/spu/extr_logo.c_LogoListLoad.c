#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int i_alpha; int i_delay; int /*<<< orphan*/  p_pic; } ;
typedef  TYPE_1__ logo_t ;
struct TYPE_6__ {int i_counter; int i_count; TYPE_1__* p_logo; scalar_t__ i_next_pic; } ;
typedef  TYPE_2__ logo_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  LoadImage (int /*<<< orphan*/ *,char*) ; 
 void* atoi (char*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static void LogoListLoad( vlc_object_t *p_this, logo_list_t *p_logo_list,
                          const char *psz_filename )
{
    char *psz_list; /* the list: <logo>[,[<delay>[,[<alpha>]]]][;...] */
    char *psz_original;
    logo_t *p_logo;         /* the parsing's result */

    p_logo_list->i_counter = 0;
    p_logo_list->i_next_pic = 0;

    psz_original = psz_list = strdup( psz_filename );

    if( !psz_list )
        return;

    /* Count the number logos == number of ';' + 1 */
    p_logo_list->i_count = 1;
    for( unsigned i = 0; i < strlen( psz_list ); i++ )
    {
        if( psz_list[i] == ';' )
            p_logo_list->i_count++;
    }

    p_logo_list->p_logo =
    p_logo              = calloc( p_logo_list->i_count, sizeof(*p_logo) );

    if( !p_logo )
    {
        free( psz_list );
        return;
    }

    /* Fill the data */
    for( unsigned i = 0; i < p_logo_list->i_count; i++ )
    {
        char *p_c  = strchr( psz_list, ';' );
        char *p_c2 = strchr( psz_list, ',' );

        p_logo[i].i_alpha = -1; /* use default settings */
        p_logo[i].i_delay = -1; /* use default settings */

        if( p_c2 && ( p_c2 < p_c || !p_c ) )
        {
            /* <logo>,<delay>[,<alpha>] type */
            if( p_c2[1] != ',' && p_c2[1] != ';' && p_c2[1] != '\0' )
                p_logo[i].i_delay = atoi( p_c2+1 );
            *p_c2 = '\0';
            if( ( p_c2 = strchr( p_c2+1, ',' ) )
                && ( p_c2 < p_c || !p_c ) && p_c2[1] != ';' && p_c2[1] != '\0' )
                p_logo[i].i_alpha = atoi( p_c2 + 1 );
        }
        else
        {
            /* <logo> type */
            if( p_c )
                *p_c = '\0';
        }

        msg_Dbg( p_this, "logo file name %s, delay %d, alpha %d",
                 psz_list, p_logo[i].i_delay, p_logo[i].i_alpha );
        p_logo[i].p_pic = LoadImage( p_this, psz_list );
        if( !p_logo[i].p_pic )
        {
            msg_Warn( p_this, "error while loading logo %s, will be skipped",
                      psz_list );
        }

        if( p_c )
            psz_list = &p_c[1];
    }

    /* initialize so that on the first update it will wrap back to 0 */
    p_logo_list->i_counter = p_logo_list->i_count - 1;

    free( psz_original );
}