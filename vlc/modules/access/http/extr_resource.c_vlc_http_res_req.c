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
struct vlc_http_resource {char const* referrer; TYPE_1__* cbs; int /*<<< orphan*/  manager; int /*<<< orphan*/ * agent; int /*<<< orphan*/ * password; int /*<<< orphan*/ * username; scalar_t__ negotiate; int /*<<< orphan*/  path; int /*<<< orphan*/  authority; scalar_t__ secure; } ;
struct vlc_http_msg {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* request_format ) (struct vlc_http_resource const*,struct vlc_http_msg*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ stub1 (struct vlc_http_resource const*,struct vlc_http_msg*,void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* vlc_gettext (char*) ; 
 int /*<<< orphan*/  vlc_http_mgr_get_jar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_msg_add_agent (struct vlc_http_msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_http_msg_add_cookies (struct vlc_http_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_msg_add_creds_basic (struct vlc_http_msg*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_http_msg_add_header (struct vlc_http_msg*,char*,char*,...) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_req_create (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vlc_http_msg *
vlc_http_res_req(const struct vlc_http_resource *res, void *opaque)
{
    struct vlc_http_msg *req;

    req = vlc_http_req_create("GET", res->secure ? "https" : "http",
                              res->authority, res->path);
    if (unlikely(req == NULL))
        return NULL;

    /* Content negotiation */
    vlc_http_msg_add_header(req, "Accept", "*/*");

    if (res->negotiate)
    {
        const char *lang = vlc_gettext("C");
        if (!strcmp(lang, "C"))
            lang = "en_US";
        vlc_http_msg_add_header(req, "Accept-Language", "%s", lang);
    }

    /* Authentication */
    if (res->username != NULL && res->password != NULL)
        vlc_http_msg_add_creds_basic(req, false, res->username, res->password);

    /* Request context */
    if (res->agent != NULL)
        vlc_http_msg_add_agent(req, res->agent);

    if (res->referrer != NULL) /* TODO: validate URL */
        vlc_http_msg_add_header(req, "Referer", "%s", res->referrer);

    vlc_http_msg_add_cookies(req, vlc_http_mgr_get_jar(res->manager));

    /* TODO: vlc_http_msg_add_header(req, "TE", "gzip, deflate"); */

    if (res->cbs->request_format(res, req, opaque))
    {
        vlc_http_msg_destroy(req);
        return NULL;
    }

    return req;
}