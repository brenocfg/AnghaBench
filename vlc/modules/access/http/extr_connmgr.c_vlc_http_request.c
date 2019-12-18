#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* psz_host; int i_port; } ;
typedef  TYPE_1__ vlc_url_t ;
struct vlc_http_stream {int dummy; } ;
struct vlc_http_msg {int dummy; } ;
struct vlc_http_mgr {struct vlc_http_conn* conn; int /*<<< orphan*/  logger; int /*<<< orphan*/ * creds; } ;
struct vlc_http_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vlc_UrlClean (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_UrlParse (TYPE_1__*,char*) ; 
 struct vlc_http_stream* vlc_h1_request (int /*<<< orphan*/ ,char const*,unsigned int,int,struct vlc_http_msg const*,int,struct vlc_http_conn**) ; 
 int /*<<< orphan*/  vlc_http_conn_release (struct vlc_http_conn*) ; 
 struct vlc_http_msg* vlc_http_mgr_reuse (struct vlc_http_mgr*,char const*,unsigned int,struct vlc_http_msg const*) ; 
 struct vlc_http_msg* vlc_http_msg_get_initial (struct vlc_http_stream*) ; 
 char* vlc_http_proxy_find (char const*,unsigned int,int) ; 

__attribute__((used)) static struct vlc_http_msg *vlc_http_request(struct vlc_http_mgr *mgr,
                                             const char *host, unsigned port,
                                             const struct vlc_http_msg *req)
{
    if (mgr->creds != NULL && mgr->conn != NULL)
        return NULL; /* switch from HTTPS to HTTP not implemented */

    struct vlc_http_msg *resp = vlc_http_mgr_reuse(mgr, host, port, req);
    if (resp != NULL)
        return resp;

    struct vlc_http_conn *conn;
    struct vlc_http_stream *stream;

    char *proxy = vlc_http_proxy_find(host, port, false);
    if (proxy != NULL)
    {
        vlc_url_t url;

        vlc_UrlParse(&url, proxy);
        free(proxy);

        if (url.psz_host != NULL)
            stream = vlc_h1_request(mgr->logger, url.psz_host,
                                    url.i_port ? url.i_port : 80, true, req,
                                    true, &conn);
        else
            stream = NULL;

        vlc_UrlClean(&url);
    }
    else
        stream = vlc_h1_request(mgr->logger, host, port ? port : 80, false,
                                req, true, &conn);

    if (stream == NULL)
        return NULL;

    resp = vlc_http_msg_get_initial(stream);
    if (resp == NULL)
    {
        vlc_http_conn_release(conn);
        return NULL;
    }

    mgr->conn = conn;
    return resp;
}