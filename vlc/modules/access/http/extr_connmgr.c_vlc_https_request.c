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
struct vlc_http_msg {int dummy; } ;
struct vlc_http_mgr {struct vlc_http_conn* conn; int /*<<< orphan*/  logger; int /*<<< orphan*/ * creds; int /*<<< orphan*/  obj; } ;
struct vlc_http_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct vlc_http_conn* vlc_h1_conn_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct vlc_http_conn* vlc_h2_conn_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vlc_http_msg* vlc_http_mgr_reuse (struct vlc_http_mgr*,char const*,unsigned int,struct vlc_http_msg const*) ; 
 char* vlc_http_proxy_find (char const*,unsigned int,int) ; 
 int /*<<< orphan*/ * vlc_https_connect (int /*<<< orphan*/ *,char const*,unsigned int,int*) ; 
 int /*<<< orphan*/ * vlc_https_connect_proxy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,unsigned int,int*,char*) ; 
 int /*<<< orphan*/ * vlc_tls_ClientCreate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tls_Close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vlc_http_msg *vlc_https_request(struct vlc_http_mgr *mgr,
                                              const char *host, unsigned port,
                                              const struct vlc_http_msg *req)
{
    vlc_tls_t *tls;
    bool http2 = true;

    if (mgr->creds == NULL && mgr->conn != NULL)
        return NULL; /* switch from HTTP to HTTPS not implemented */

    if (mgr->creds == NULL)
    {   /* First TLS connection: load x509 credentials */
        mgr->creds = vlc_tls_ClientCreate(mgr->obj);
        if (mgr->creds == NULL)
            return NULL;
    }

    /* TODO? non-idempotent request support */
    struct vlc_http_msg *resp = vlc_http_mgr_reuse(mgr, host, port, req);
    if (resp != NULL)
        return resp; /* existing connection reused */

    char *proxy = vlc_http_proxy_find(host, port, true);
    if (proxy != NULL)
    {
        tls = vlc_https_connect_proxy(mgr->creds, mgr->creds,
                                      host, port, &http2, proxy);
        free(proxy);
    }
    else
        tls = vlc_https_connect(mgr->creds, host, port, &http2);

    if (tls == NULL)
        return NULL;

    struct vlc_http_conn *conn;

    /* For HTTPS, TLS-ALPN determines whether HTTP version 2.0 ("h2") or 1.1
     * ("http/1.1") is used.
     * NOTE: If the negotiated protocol is explicitly "http/1.1", HTTP 1.0
     * should not be used. HTTP 1.0 should only be used if ALPN is not
     * supported by the server.
     * NOTE: We do not enforce TLS version 1.2 for HTTP 2.0 explicitly.
     */
    if (http2)
        conn = vlc_h2_conn_create(mgr->logger, tls);
    else
        conn = vlc_h1_conn_create(mgr->logger, tls, false);

    if (unlikely(conn == NULL))
    {
        vlc_tls_Close(tls);
        return NULL;
    }

    mgr->conn = conn;

    return vlc_http_mgr_reuse(mgr, host, port, req);
}