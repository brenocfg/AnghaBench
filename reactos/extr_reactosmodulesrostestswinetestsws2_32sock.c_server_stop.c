#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ s; TYPE_1__* sock; } ;
typedef  TYPE_2__ server_memory ;
struct TYPE_5__ {scalar_t__ s; TYPE_2__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ExitThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 int MAX_CLIENTS ; 
 TYPE_2__* TlsGetValue (int /*<<< orphan*/ ) ; 
 scalar_t__ closesocket (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  tls ; 

__attribute__((used)) static void server_stop (void)
{
    int i;
    server_memory *mem = TlsGetValue ( tls );

    for (i = 0; i < MAX_CLIENTS; i++ )
    {
        LocalFree ( mem->sock[i].buf );
        if ( mem->sock[i].s != INVALID_SOCKET )
            closesocket ( mem->sock[i].s );
    }
    ok ( closesocket ( mem->s ) == 0, "closesocket failed\n" );
    LocalFree ( mem );
    ExitThread ( GetCurrentThreadId () );
}