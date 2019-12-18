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
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

vlc_http_cookie_jar_t * vlc_http_cookies_new(void)
{
    vlc_http_cookie_jar_t * jar = malloc( sizeof( vlc_http_cookie_jar_t ) );
    if ( unlikely(jar == NULL) )
        return NULL;

    vlc_array_init( &jar->cookies );
    vlc_mutex_init( &jar->lock );

    return jar;
}