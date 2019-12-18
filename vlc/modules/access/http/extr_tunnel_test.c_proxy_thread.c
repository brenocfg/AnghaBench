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

/* Variables and functions */
 int /*<<< orphan*/  SOCK_CLOEXEC ; 
 int accept4 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_count ; 
 int /*<<< orphan*/  proxy_client_process (int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *proxy_thread(void *data)
{
    int *lfd = data;

    for (;;)
    {
        int cfd = accept4(*lfd, NULL, NULL, SOCK_CLOEXEC);
        if (cfd == -1)
            continue;

        int canc = vlc_savecancel();
        proxy_client_process(cfd);
        vlc_close(cfd);
        connection_count++;
        vlc_restorecancel(canc);
    }
    vlc_assert_unreachable();
}