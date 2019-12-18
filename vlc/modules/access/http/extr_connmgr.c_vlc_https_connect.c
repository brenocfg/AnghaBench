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
typedef  int /*<<< orphan*/  vlc_tls_t ;
typedef  int /*<<< orphan*/  vlc_tls_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/ * vlc_tls_SocketOpenTLS (int /*<<< orphan*/ *,char const*,unsigned int,char*,char const**,char**) ; 

vlc_tls_t *vlc_https_connect(vlc_tls_client_t *creds, const char *name,
                             unsigned port, bool *restrict two)
{
    if (port == 0)
        port = 443;

    /* TLS with ALPN */
    const char *alpn[] = { "h2", "http/1.1", NULL };
    char *alp;

    vlc_tls_t *tls = vlc_tls_SocketOpenTLS(creds, name, port, "https",
                                           alpn + !*two, &alp);
    if (tls != NULL)
    {
        *two = (alp != NULL) && !strcmp(alp, "h2");
        free(alp);
    }
    return tls;
}