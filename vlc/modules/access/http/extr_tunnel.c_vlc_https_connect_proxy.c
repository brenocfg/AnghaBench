#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  psz_password; int /*<<< orphan*/  psz_username; int /*<<< orphan*/  i_port; int /*<<< orphan*/ * psz_host; int /*<<< orphan*/ * psz_protocol; } ;
typedef  TYPE_1__ vlc_url_t ;
struct TYPE_15__ {int /*<<< orphan*/ * p; int /*<<< orphan*/ * ops; } ;
typedef  TYPE_2__ vlc_tls_t ;
struct TYPE_16__ {TYPE_2__ tls; TYPE_2__* sock; } ;
typedef  TYPE_3__ vlc_tls_proxy_t ;
typedef  int /*<<< orphan*/  vlc_tls_client_t ;
struct vlc_http_msg {int dummy; } ;
struct vlc_http_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_UrlParse (TYPE_1__*,char const*) ; 
 struct vlc_http_conn* vlc_h1_conn_create (void*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  vlc_http_conn_release (struct vlc_http_conn*) ; 
 struct vlc_http_msg* vlc_http_tunnel_open (struct vlc_http_conn*,char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_https_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * vlc_object_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 TYPE_2__* vlc_tls_ClientSessionCreate (int /*<<< orphan*/ *,TYPE_2__*,char const*,char*,char const**,char**) ; 
 int /*<<< orphan*/  vlc_tls_Close (TYPE_2__*) ; 
 TYPE_2__* vlc_tls_SocketOpenTCP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tls_proxy_ops ; 

vlc_tls_t *vlc_https_connect_proxy(void *ctx, vlc_tls_client_t *creds,
                                   const char *hostname, unsigned port,
                                   bool *restrict two, const char *proxy)
{
    vlc_url_t url;
    int canc;

    assert(proxy != NULL);

    if (port == 0)
        port = 443;

    canc = vlc_savecancel();
    vlc_UrlParse(&url, proxy);
    vlc_restorecancel(canc);

    if (url.psz_protocol == NULL || url.psz_host == NULL)
    {
        vlc_UrlClean(&url);
        return NULL;
    }

    vlc_tls_t *sock = NULL;
    bool ptwo = false;
    if (!strcasecmp(url.psz_protocol, "https"))
        sock = vlc_https_connect(creds, url.psz_host, url.i_port, &ptwo);
    else
    if (!strcasecmp(url.psz_protocol, "http"))
        sock = vlc_tls_SocketOpenTCP(creds ? vlc_object_parent(creds) : NULL,
                                     url.psz_host, url.i_port);
    else
        sock = NULL;

    if (sock == NULL)
    {
        vlc_UrlClean(&url);
        return NULL;
    }

    assert(!ptwo); /* HTTP/2 proxy not supported yet */

    vlc_tls_proxy_t *psock = malloc(sizeof (*psock));
    if (unlikely(psock == NULL))
    {
        vlc_UrlClean(&url);
        goto error;
    }

    psock->tls.ops = &vlc_tls_proxy_ops;
    psock->tls.p = NULL;
    psock->sock = sock;

    struct vlc_http_conn *conn = /*ptwo ? vlc_h2_conn_create(ctx, &psock->tls)
                               :*/ vlc_h1_conn_create(ctx, &psock->tls, false);
    if (unlikely(conn == NULL))
    {
        vlc_tls_Close(&psock->tls);
        vlc_UrlClean(&url);
        goto error;
    }

    struct vlc_http_msg *resp = vlc_http_tunnel_open(conn, hostname, port,
                                                     url.psz_username,
                                                     url.psz_password);
    vlc_UrlClean(&url);

    /* TODO: reuse connection to HTTP/2 proxy */
    vlc_http_conn_release(conn); /* psock is destroyed there too */

    if (resp == NULL)
        goto error;

    vlc_tls_t *tls;
    const char *alpn[] = { "h2", "http/1.1", NULL };
    char *alp;

    tls = vlc_tls_ClientSessionCreate(creds, sock, hostname, "https",
                                      alpn + !*two, &alp);
    if (tls == NULL)
        goto error;

    *two = (alp != NULL) && !strcmp(alp, "h2");
    free(alp);
    return tls;
error:
    vlc_tls_Close(sock);
    return NULL;
}