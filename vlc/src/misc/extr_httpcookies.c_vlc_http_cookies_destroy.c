#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cookies; } ;
typedef  TYPE_1__ vlc_http_cookie_jar_t ;

/* Variables and functions */
 int /*<<< orphan*/  cookie_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void vlc_http_cookies_destroy( vlc_http_cookie_jar_t * p_jar )
{
    if ( !p_jar )
        return;

    for( size_t i = 0; i < vlc_array_count( &p_jar->cookies ); i++ )
        cookie_destroy( vlc_array_item_at_index( &p_jar->cookies, i ) );

    vlc_array_clear( &p_jar->cookies );
    vlc_mutex_destroy( &p_jar->lock );

    free( p_jar );
}