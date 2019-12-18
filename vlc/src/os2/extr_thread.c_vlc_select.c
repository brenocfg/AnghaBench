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
struct vlc_thread {scalar_t__ cancel_sock; } ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int MAX (int,scalar_t__) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  vlc_testcancel () ; 
 struct vlc_thread* vlc_thread_self () ; 

__attribute__((used)) static int vlc_select( int nfds, fd_set *rdset, fd_set *wrset, fd_set *exset,
                       struct timeval *timeout )
{
    struct vlc_thread *th = vlc_thread_self( );

    int rc;

    if( th )
    {
        FD_SET( th->cancel_sock, rdset );

        nfds = MAX( nfds, th->cancel_sock + 1 );
    }

    rc = select( nfds, rdset, wrset, exset, timeout );

    vlc_testcancel();

    return rc;

}