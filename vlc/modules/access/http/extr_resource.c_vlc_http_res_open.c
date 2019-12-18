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
struct vlc_http_resource {int negotiate; TYPE_1__* cbs; int /*<<< orphan*/  path; int /*<<< orphan*/  host; int /*<<< orphan*/  manager; int /*<<< orphan*/  port; int /*<<< orphan*/  secure; } ;
struct vlc_http_msg {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* response_validate ) (struct vlc_http_resource*,struct vlc_http_msg*,void*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct vlc_http_resource*,struct vlc_http_msg*,void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_mgr_get_jar (int /*<<< orphan*/ ) ; 
 struct vlc_http_msg* vlc_http_mgr_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vlc_http_msg*) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 int /*<<< orphan*/  vlc_http_msg_get_cookies (struct vlc_http_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vlc_http_msg* vlc_http_msg_get_final (struct vlc_http_msg*) ; 
 int vlc_http_msg_get_status (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_res_req (struct vlc_http_resource*,void*) ; 

struct vlc_http_msg *vlc_http_res_open(struct vlc_http_resource *res,
                                       void *opaque)
{
    struct vlc_http_msg *req;
retry:
    req = vlc_http_res_req(res, opaque);
    if (unlikely(req == NULL))
        return NULL;

    struct vlc_http_msg *resp = vlc_http_mgr_request(res->manager, res->secure,
                                                    res->host, res->port, req);
    vlc_http_msg_destroy(req);

    resp = vlc_http_msg_get_final(resp);
    if (resp == NULL)
        return NULL;

    vlc_http_msg_get_cookies(resp, vlc_http_mgr_get_jar(res->manager),
                             res->host, res->path);

    int status = vlc_http_msg_get_status(resp);
    if (status < 200 || status >= 599)
        goto fail;

    if (status == 406 && res->negotiate)
    {   /* Not Acceptable: Content negotiation failed. Normally it means
         * one (or more) Accept or Accept-* header line does not match any
         * representation of the entity. So we set a flag to remove those
         * header lines (unless they accept everything), and retry.
         * In principles, it could be any header line, and the server can
         * pass Vary to clarify. It cannot be caused by If-*, Range, TE or the
         * other transfer- rather than representation-affecting header lines.
         */
        vlc_http_msg_destroy(resp);
        res->negotiate = false;
        goto retry;
    }

    if (res->cbs->response_validate(res, resp, opaque))
        goto fail;

    return resp;
fail:
    vlc_http_msg_destroy(resp);
    return NULL;
}