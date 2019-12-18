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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  album_cache; int /*<<< orphan*/  downloader; int /*<<< orphan*/  network; int /*<<< orphan*/  local; } ;
typedef  TYPE_1__ input_fetcher_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeCacheEntry ; 
 int /*<<< orphan*/  background_worker_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_dictionary_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void input_fetcher_Delete( input_fetcher_t* fetcher )
{
    background_worker_Delete( fetcher->local );
    background_worker_Delete( fetcher->network );
    background_worker_Delete( fetcher->downloader );

    vlc_dictionary_clear( &fetcher->album_cache, FreeCacheEntry, NULL );
    vlc_mutex_destroy( &fetcher->lock );

    free( fetcher );
}