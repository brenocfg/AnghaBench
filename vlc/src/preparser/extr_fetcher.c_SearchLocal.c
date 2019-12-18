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
struct fetcher_request {int options; int /*<<< orphan*/  item; } ;
struct TYPE_4__ {int /*<<< orphan*/  network; int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ input_fetcher_t ;

/* Variables and functions */
 int /*<<< orphan*/  FETCHER_SCOPE_LOCAL ; 
 int META_REQUEST_OPTION_FETCH_NETWORK ; 
 int /*<<< orphan*/  NotifyArtFetchEnded (struct fetcher_request*,int) ; 
 scalar_t__ SearchByScope (TYPE_1__*,struct fetcher_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ background_worker_Push (int /*<<< orphan*/ ,struct fetcher_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_SetArtNotFound (int /*<<< orphan*/ ,int) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void SearchLocal( input_fetcher_t* fetcher, struct fetcher_request* req )
{
    if( SearchByScope( fetcher, req, FETCHER_SCOPE_LOCAL ) == VLC_SUCCESS )
        return; /* done */

    if( var_InheritBool( fetcher->owner, "metadata-network-access" ) ||
        req->options & META_REQUEST_OPTION_FETCH_NETWORK )
    {
        if( background_worker_Push( fetcher->network, req, NULL, 0 ) )
            NotifyArtFetchEnded(req, false);
    }
    else
    {
        input_item_SetArtNotFound( req->item, true );
        NotifyArtFetchEnded(req, false);
    }
}