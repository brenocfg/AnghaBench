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
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char const*) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_stream_FilterNew (int /*<<< orphan*/ *,char const*) ; 

stream_t *stream_FilterChainNew( stream_t *p_source, const char *psz_chain )
{
    /* Add user stream filter */
    char *chain = strdup( psz_chain );
    if( unlikely(chain == NULL) )
        return p_source;

    char *buf;
    for( const char *name = strtok_r( chain, ":", &buf );
         name != NULL;
         name = strtok_r( NULL, ":", &buf ) )
    {
        stream_t *p_filter = vlc_stream_FilterNew( p_source, name );
        if( p_filter != NULL )
            p_source = p_filter;
        else
            msg_Warn( p_source, "cannot insert stream filter %s", name );
    }
    free( chain );

    return p_source;
}