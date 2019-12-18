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
typedef  void vlc_tls_t ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  server_creds ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_tls_Close (void*) ; 
 int /*<<< orphan*/  vlc_tls_GetPollFD (void*,int /*<<< orphan*/ *) ; 
 int vlc_tls_Read (void*,char*,int,int) ; 
 int vlc_tls_SessionHandshake (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ vlc_tls_Shutdown (void*,int) ; 
 int vlc_tls_Write (void*,char*,int) ; 

__attribute__((used)) static void *tls_echo(void *data)
{
    vlc_tls_t *tls = data;
    ssize_t val;
    char buf[256];

    while ((val = vlc_tls_SessionHandshake(server_creds, tls)) > 0)
    {
        struct pollfd ufd;

        switch (val)
        {
            case 1:  ufd.events = POLLIN;  break;
            case 2:  ufd.events = POLLOUT; break;
            default: vlc_assert_unreachable();
        }

        ufd.fd = vlc_tls_GetPollFD(tls, &ufd.events);
        poll(&ufd, 1, -1);
    }

    if (val < 0)
        goto error;

    while ((val = vlc_tls_Read(tls, buf, sizeof (buf), false)) > 0)
        if (vlc_tls_Write(tls, buf, val) < val)
            goto error;

    if (val < 0 || vlc_tls_Shutdown(tls, false))
        goto error;

    vlc_tls_Close(tls);
    return tls;
error:
    vlc_tls_Close(tls);
    return NULL;
}