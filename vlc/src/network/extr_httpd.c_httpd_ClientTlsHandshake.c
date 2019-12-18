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
struct TYPE_5__ {int /*<<< orphan*/  p_tls; } ;
typedef  TYPE_1__ httpd_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_state; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ httpd_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPD_CLIENT_DEAD ; 
 int /*<<< orphan*/  HTTPD_CLIENT_RECEIVING ; 
 int /*<<< orphan*/  HTTPD_CLIENT_TLS_HS_IN ; 
 int /*<<< orphan*/  HTTPD_CLIENT_TLS_HS_OUT ; 
 int vlc_tls_SessionHandshake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void httpd_ClientTlsHandshake(httpd_host_t *host, httpd_client_t *cl)
{
    switch (vlc_tls_SessionHandshake(host->p_tls, cl->sock))
    {
        case -1: cl->i_state = HTTPD_CLIENT_DEAD;       break;
        case 0:  cl->i_state = HTTPD_CLIENT_RECEIVING;  break;
        case 1:  cl->i_state = HTTPD_CLIENT_TLS_HS_IN;  break;
        case 2:  cl->i_state = HTTPD_CLIENT_TLS_HS_OUT; break;
    }
}