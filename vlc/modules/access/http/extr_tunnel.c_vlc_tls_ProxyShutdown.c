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
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ vlc_tls_proxy_t ;

/* Variables and functions */
 int vlc_tls_Shutdown (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vlc_tls_ProxyShutdown(vlc_tls_t *tls, bool duplex)
{
    vlc_tls_proxy_t *proxy = (vlc_tls_proxy_t *)tls;

    return vlc_tls_Shutdown(proxy->sock, duplex);
}