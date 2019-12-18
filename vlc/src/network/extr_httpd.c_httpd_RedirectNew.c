#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  url; int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ httpd_redirect_t ;
typedef  int /*<<< orphan*/  httpd_host_t ;
typedef  int /*<<< orphan*/  httpd_callback_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPD_MSG_DESCRIBE ; 
 int /*<<< orphan*/  HTTPD_MSG_GET ; 
 int /*<<< orphan*/  HTTPD_MSG_HEAD ; 
 int /*<<< orphan*/  HTTPD_MSG_POST ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  httpd_RedirectCallBack ; 
 int /*<<< orphan*/  httpd_UrlCatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpd_UrlNew (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

httpd_redirect_t *httpd_RedirectNew(httpd_host_t *host, const char *psz_url_dst,
                                     const char *psz_url_src)
{
    size_t dstlen = strlen(psz_url_dst);

    httpd_redirect_t *rdir = malloc(sizeof(*rdir) + dstlen);
    if (unlikely(rdir == NULL))
        return NULL;

    rdir->url = httpd_UrlNew(host, psz_url_src, NULL, NULL);
    if (!rdir->url) {
        free(rdir);
        return NULL;
    }
    memcpy(rdir->dst, psz_url_dst, dstlen + 1);

    /* Redirect apply for all HTTP request and RTSP DESCRIBE resquest */
    httpd_UrlCatch(rdir->url, HTTPD_MSG_HEAD, httpd_RedirectCallBack,
                    (httpd_callback_sys_t*)rdir);
    httpd_UrlCatch(rdir->url, HTTPD_MSG_GET, httpd_RedirectCallBack,
                    (httpd_callback_sys_t*)rdir);
    httpd_UrlCatch(rdir->url, HTTPD_MSG_POST, httpd_RedirectCallBack,
                    (httpd_callback_sys_t*)rdir);
    httpd_UrlCatch(rdir->url, HTTPD_MSG_DESCRIBE, httpd_RedirectCallBack,
                    (httpd_callback_sys_t*)rdir);

    return rdir;
}