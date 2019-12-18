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
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  input_item_slave_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLAVE_PRIORITY_USER ; 
 int /*<<< orphan*/  SLAVE_TYPE_AUDIO ; 
 int /*<<< orphan*/  TAB_APPEND (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_slave_New (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* var_GetNonEmptyString (int /*<<< orphan*/ *,char*) ; 
 char* vlc_path2uri (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void GetVarSlaves( input_thread_t *p_input,
                          input_item_slave_t ***ppp_slaves, int *p_slaves )
{
    char *psz = var_GetNonEmptyString( p_input, "input-slave" );
    if( !psz )
        return;

    input_item_slave_t **pp_slaves = *ppp_slaves;
    int i_slaves = *p_slaves;

    char *psz_org = psz;
    while( psz && *psz )
    {
        while( *psz == ' ' || *psz == '#' )
            psz++;

        char *psz_delim = strchr( psz, '#' );
        if( psz_delim )
            *psz_delim++ = '\0';

        if( *psz == 0 )
            break;

        char *uri = strstr(psz, "://")
                                   ? strdup( psz ) : vlc_path2uri( psz, NULL );
        psz = psz_delim;
        if( uri == NULL )
            continue;

        input_item_slave_t *p_slave =
            input_item_slave_New( uri, SLAVE_TYPE_AUDIO, SLAVE_PRIORITY_USER );
        free( uri );

        if( unlikely( p_slave == NULL ) )
            break;
        TAB_APPEND(i_slaves, pp_slaves, p_slave);
    }
    free( psz_org );

    *ppp_slaves = pp_slaves; /* in case of realloc */
    *p_slaves = i_slaves;
}