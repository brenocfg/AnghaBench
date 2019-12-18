#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int b_meta_changed; } ;
typedef  TYPE_1__ xds_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static bool XdsChangeString( xds_t *h, char **ppsz_dst, const char *psz_new )
{
    if( *ppsz_dst && psz_new && !strcmp( *ppsz_dst, psz_new ) )
        return false;
    if( *ppsz_dst == NULL && psz_new == NULL )
        return false;

    free( *ppsz_dst );
    if( psz_new )
        *ppsz_dst = strdup( psz_new );
    else
        *ppsz_dst = NULL;

    h->b_meta_changed = true;
    return true;
}