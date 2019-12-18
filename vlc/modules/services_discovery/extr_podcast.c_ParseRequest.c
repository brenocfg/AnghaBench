#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_10__ {char* psz_request; int i_urls; char** ppsz_urls; int i_items; char** pp_items; int /*<<< orphan*/  b_savedurls_loaded; } ;
typedef  TYPE_2__ services_discovery_sys_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  ParseUrls (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  SaveUrls (TYPE_1__*) ; 
 int /*<<< orphan*/  TAB_APPEND (int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAB_ERASE (int,char**,int) ; 
 int /*<<< orphan*/  VLC_INPUT_OPTION_TRUSTED ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_AddOption (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_item_New (char*,char*) ; 
 int /*<<< orphan*/  input_item_Release (char*) ; 
 int /*<<< orphan*/  services_discovery_AddItem (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  services_discovery_RemoveItem (TYPE_1__*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 char* var_GetNonEmptyString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_object_parent (TYPE_1__*) ; 

__attribute__((used)) static void ParseRequest( services_discovery_t *p_sd )
{
    services_discovery_sys_t *p_sys = p_sd->p_sys;

    char *psz_request = p_sys->psz_request;

    int i;

    char *psz_tok = strchr( psz_request, ':' );
    if( !psz_tok ) return;
    *psz_tok = '\0';

    if ( ! p_sys->b_savedurls_loaded )
    {
        char *psz_urls = var_GetNonEmptyString( vlc_object_parent(p_sd),
                                                "podcast-urls" );
        ParseUrls( p_sd, psz_urls );
        free( psz_urls );
    }

    if( !strcmp( psz_request, "ADD" ) )
    {
        psz_request = psz_tok + 1;
        for( i = 0; i<p_sys->i_urls; i++ )
            if( !strcmp(p_sys->ppsz_urls[i],psz_request) )
              break;
        if( i == p_sys->i_urls )
        {
            TAB_APPEND( p_sys->i_urls, p_sys->ppsz_urls,
                        strdup( psz_request ) );

            input_item_t *p_input;
            p_input = input_item_New( psz_request, psz_request );
            input_item_AddOption( p_input, "demux=directory", VLC_INPUT_OPTION_TRUSTED );

            TAB_APPEND( p_sys->i_items, p_sys->pp_items, p_input );
            services_discovery_AddItem( p_sd, p_input );

            SaveUrls( p_sd );
        }
    }
    else if ( !strcmp( psz_request, "RM" ) )
    {
        psz_request = psz_tok + 1;
        for( i = 0; i < p_sys->i_urls; i++ )
            if( !strcmp(p_sys->ppsz_urls[i], psz_request) )
            {
                services_discovery_RemoveItem( p_sd, p_sys->pp_items[i] );
                input_item_Release( p_sys->pp_items[i] );
                TAB_ERASE(p_sys->i_urls, p_sys->ppsz_urls, i );
                TAB_ERASE(p_sys->i_items, p_sys->pp_items, i );
                break;
            }
        SaveUrls( p_sd );
    }

    free( p_sys->psz_request );
    p_sys->psz_request = NULL;
}