#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fetcher_request {int /*<<< orphan*/ * item; } ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_7__ {int /*<<< orphan*/  downloader; } ;
typedef  TYPE_1__ input_fetcher_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddAlbumCache (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CheckArt (int /*<<< orphan*/ *) ; 
 scalar_t__ CheckMeta (int /*<<< orphan*/ *) ; 
 scalar_t__ InvokeModule (TYPE_1__*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ReadAlbumCache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SearchArt (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  background_worker_Push (int /*<<< orphan*/ ,struct fetcher_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_FindArtInCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_FindArtInCacheUsingItemUID (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SearchByScope( input_fetcher_t* fetcher,
    struct fetcher_request* req, int scope )
{
    input_item_t* item = req->item;

    if( CheckMeta( item ) &&
        InvokeModule( fetcher, req->item, scope, "meta fetcher" ) )
    {
        return VLC_EGENERIC;
    }

    if( ! CheckArt( item )                         ||
        ! ReadAlbumCache( fetcher, item )          ||
        ! input_FindArtInCacheUsingItemUID( item ) ||
        ! input_FindArtInCache( item )             ||
        ! SearchArt( fetcher, item, scope ) )
    {
        AddAlbumCache( fetcher, req->item, false );
        if( !background_worker_Push( fetcher->downloader, req, NULL, 0 ) )
            return VLC_SUCCESS;
    }

    return VLC_EGENERIC;
}