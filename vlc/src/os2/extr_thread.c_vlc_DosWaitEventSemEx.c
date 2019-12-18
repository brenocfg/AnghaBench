#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vlc_thread {scalar_t__ cancel_event; int /*<<< orphan*/  killable; } ;
typedef  int ULONG ;
struct TYPE_3__ {int ulUser; void* hsemCur; } ;
typedef  TYPE_1__ SEMRECORD ;
typedef  void* HSEM ;
typedef  int /*<<< orphan*/  HMUX ;
typedef  scalar_t__ HEV ;

/* Variables and functions */
 int /*<<< orphan*/  DCMW_WAIT_ANY ; 
 int /*<<< orphan*/  DosCloseMuxWaitSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosCreateMuxWaitSem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int DosSleep (int) ; 
 int DosWaitEventSem (scalar_t__,int) ; 
 int DosWaitMuxWaitSem (int /*<<< orphan*/ ,int,int*) ; 
 int ERROR_INTERRUPT ; 
 int NO_ERROR ; 
 scalar_t__ NULLHANDLE ; 
 int /*<<< orphan*/  vlc_cancel_self (struct vlc_thread*) ; 
 struct vlc_thread* vlc_thread_self () ; 

__attribute__((used)) static ULONG vlc_DosWaitEventSemEx( HEV hev, ULONG ulTimeout )
{
    HMUX      hmux;
    SEMRECORD asr[ 2 ];
    ULONG     ulUser;
    int       n;
    ULONG     rc;

    struct vlc_thread *th = vlc_thread_self ();
    if( th == NULL || !th->killable )
    {
        /* Main thread - cannot be cancelled anyway
         * Alien thread - out of our control
         * Cancel disabled thread - ignore cancel
         */
        if( hev != NULLHANDLE )
            return DosWaitEventSem( hev, ulTimeout );

        return DosSleep( ulTimeout );
    }

    n = 0;
    if( hev != NULLHANDLE )
    {
        asr[ n ].hsemCur = ( HSEM )hev;
        asr[ n ].ulUser  = 0;
        n++;
    }
    asr[ n ].hsemCur = ( HSEM )th->cancel_event;
    asr[ n ].ulUser  = 0xFFFF;
    n++;

    DosCreateMuxWaitSem( NULL, &hmux, n, asr, DCMW_WAIT_ANY );
    rc = DosWaitMuxWaitSem( hmux, ulTimeout, &ulUser );
    DosCloseMuxWaitSem( hmux );
    if( rc )
        return rc;

    if( ulUser == 0xFFFF )
    {
        vlc_cancel_self( th );
        return ERROR_INTERRUPT;
    }

    return NO_ERROR;
}