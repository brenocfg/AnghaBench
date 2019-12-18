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
struct fetcher_request {int /*<<< orphan*/  item; int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct fetcher_request*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RequestRelease( void* req_ )
{
    struct fetcher_request* req = req_;

    if( !vlc_atomic_rc_dec( &req->rc ) )
        return;

    input_item_Release( req->item );
    free( req );
}