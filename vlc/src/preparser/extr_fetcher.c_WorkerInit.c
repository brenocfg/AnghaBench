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
struct background_worker_config {int (* pf_start ) (void*,void*,void**) ;int /*<<< orphan*/  pf_hold; int /*<<< orphan*/  pf_release; int /*<<< orphan*/  pf_stop; int /*<<< orphan*/  pf_probe; int /*<<< orphan*/  max_threads; int /*<<< orphan*/  default_timeout; } ;
struct background_worker {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ input_fetcher_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseWorker ; 
 int /*<<< orphan*/  ProbeWorker ; 
 int /*<<< orphan*/  RequestHold ; 
 int /*<<< orphan*/  RequestRelease ; 
 struct background_worker* background_worker_New (TYPE_1__*,struct background_worker_config*) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void WorkerInit( input_fetcher_t* fetcher,
    struct background_worker** worker, int( *starter )( void*, void*, void** ) )
{
    struct background_worker_config conf = {
        .default_timeout = 0,
        .max_threads = var_InheritInteger( fetcher->owner, "fetch-art-threads" ),
        .pf_start = starter,
        .pf_probe = ProbeWorker,
        .pf_stop = CloseWorker,
        .pf_release = RequestRelease,
        .pf_hold = RequestHold };

    *worker = background_worker_New( fetcher, &conf );
}