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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct background_worker_config {int /*<<< orphan*/  pf_hold; int /*<<< orphan*/  pf_release; int /*<<< orphan*/  pf_stop; int /*<<< orphan*/  pf_probe; int /*<<< orphan*/  pf_start; int /*<<< orphan*/  max_threads; int /*<<< orphan*/  default_timeout; } ;
struct TYPE_7__ {int /*<<< orphan*/  fetcher; int /*<<< orphan*/  deactivated; int /*<<< orphan*/ * owner; int /*<<< orphan*/  worker; } ;
typedef  TYPE_1__ input_preparser_t ;

/* Variables and functions */
 int /*<<< orphan*/  PreparserCloseInput ; 
 int /*<<< orphan*/  PreparserOpenInput ; 
 int /*<<< orphan*/  PreparserProbeInput ; 
 int /*<<< orphan*/  ReqHoldVoid ; 
 int /*<<< orphan*/  ReqReleaseVoid ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  background_worker_New (TYPE_1__*,struct background_worker_config*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  input_fetcher_New (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

input_preparser_t* input_preparser_New( vlc_object_t *parent )
{
    input_preparser_t* preparser = malloc( sizeof *preparser );

    struct background_worker_config conf = {
        .default_timeout = VLC_TICK_FROM_MS(var_InheritInteger( parent, "preparse-timeout" )),
        .max_threads = var_InheritInteger( parent, "preparse-threads" ),
        .pf_start = PreparserOpenInput,
        .pf_probe = PreparserProbeInput,
        .pf_stop = PreparserCloseInput,
        .pf_release = ReqReleaseVoid,
        .pf_hold = ReqHoldVoid
    };


    if( likely( preparser ) )
        preparser->worker = background_worker_New( preparser, &conf );

    if( unlikely( !preparser || !preparser->worker ) )
    {
        free( preparser );
        return NULL;
    }

    preparser->owner = parent;
    preparser->fetcher = input_fetcher_New( parent );
    atomic_init( &preparser->deactivated, false );

    if( unlikely( !preparser->fetcher ) )
        msg_Warn( parent, "unable to create art fetcher" );

    return preparser;
}