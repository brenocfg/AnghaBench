#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  album_cache; int /*<<< orphan*/  lock; scalar_t__ downloader; scalar_t__ network; scalar_t__ local; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_1__ input_fetcher_t ;

/* Variables and functions */
 int /*<<< orphan*/  StartDownloader ; 
 int /*<<< orphan*/  StartSearchLocal ; 
 int /*<<< orphan*/  StartSearchNetwork ; 
 int /*<<< orphan*/  WorkerInit (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  background_worker_Delete (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_dictionary_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

input_fetcher_t* input_fetcher_New( vlc_object_t* owner )
{
    input_fetcher_t* fetcher = malloc( sizeof( *fetcher ) );

    if( unlikely( !fetcher ) )
        return NULL;

    fetcher->owner = owner;

    WorkerInit( fetcher, &fetcher->local, StartSearchLocal );
    WorkerInit( fetcher, &fetcher->network, StartSearchNetwork );
    WorkerInit( fetcher, &fetcher->downloader, StartDownloader );

    if( unlikely( !fetcher->local || !fetcher->network || !fetcher->downloader ) )
    {
        if( fetcher->local )
            background_worker_Delete( fetcher->local );

        if( fetcher->network )
            background_worker_Delete( fetcher->network );

        if( fetcher->downloader )
            background_worker_Delete( fetcher->downloader );

        free( fetcher );
        return NULL;
    }

    vlc_mutex_init( &fetcher->lock );
    vlc_dictionary_init( &fetcher->album_cache, 0 );

    return fetcher;
}