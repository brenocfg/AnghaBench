#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_5__ {int i_urls; char** ppsz_urls; } ;
typedef  TYPE_2__ services_discovery_sys_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  config_PutPsz (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void SaveUrls( services_discovery_t *p_sd )
{
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    int i;
    char *psz_urls;
    int len = 0;

    for( i=0; i < p_sys->i_urls; i++ )
        len += strlen( p_sys->ppsz_urls[i] ) + 1;

    psz_urls = (char*) calloc( len, sizeof(char) );

    for( i=0; i < p_sys->i_urls; i++ )
    {
        strcat( psz_urls, p_sys->ppsz_urls[i] );
        if( i < p_sys->i_urls - 1 ) strcat( psz_urls, "|" );
    }

    config_PutPsz( "podcast-urls", psz_urls );

    free( psz_urls );
}