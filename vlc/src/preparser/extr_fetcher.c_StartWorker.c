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
struct fetcher_thread {void (* pf_worker ) (int /*<<< orphan*/ *,struct fetcher_request*) ;int /*<<< orphan*/  interrupt; int /*<<< orphan*/  thread; int /*<<< orphan*/  active; int /*<<< orphan*/ * fetcher; struct background_worker* worker; struct fetcher_request* req; } ;
struct fetcher_request {int dummy; } ;
struct background_worker {int dummy; } ;
typedef  int /*<<< orphan*/  input_fetcher_t ;

/* Variables and functions */
 int /*<<< orphan*/  FetcherThread ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct fetcher_thread*) ; 
 struct fetcher_thread* malloc (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct fetcher_thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_interrupt_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int StartWorker( input_fetcher_t* fetcher,
    void( *pf_worker )( input_fetcher_t*, struct fetcher_request* ),
    struct background_worker* bg, struct fetcher_request* req, void** handle )
{
    struct fetcher_thread* th = malloc( sizeof *th );

    if( unlikely( !th ) )
        return VLC_ENOMEM;

    th->req = req;
    th->worker = bg;
    th->fetcher = fetcher;
    th->pf_worker = pf_worker;

    vlc_interrupt_init( &th->interrupt );
    atomic_init( &th->active, true );

    if( !vlc_clone( &th->thread, FetcherThread, th, VLC_THREAD_PRIORITY_LOW ) )
    {
        *handle = th;
        return VLC_SUCCESS;
    }

    vlc_interrupt_deinit( &th->interrupt );
    free( th );
    return VLC_EGENERIC;
}