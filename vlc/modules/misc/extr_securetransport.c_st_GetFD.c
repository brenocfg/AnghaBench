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
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_2__ {int /*<<< orphan*/ * sock; } ;
typedef  TYPE_1__ vlc_tls_st_t ;

/* Variables and functions */
 int vlc_tls_GetPollFD (int /*<<< orphan*/ *,short*) ; 

__attribute__((used)) static int st_GetFD (vlc_tls_t *session, short *restrict events)
{
    vlc_tls_st_t *sys = (vlc_tls_st_t *)session;
    vlc_tls_t *sock = sys->sock;

    return vlc_tls_GetPollFD(sock, events);
}