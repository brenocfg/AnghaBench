#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fetcher_request {int /*<<< orphan*/  userdata; int /*<<< orphan*/  item; TYPE_1__* cbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* on_art_fetch_ended ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void NotifyArtFetchEnded( struct fetcher_request* req, bool fetched )
{
    if (req->cbs && req->cbs->on_art_fetch_ended)
        req->cbs->on_art_fetch_ended(req->item, fetched, req->userdata);
}