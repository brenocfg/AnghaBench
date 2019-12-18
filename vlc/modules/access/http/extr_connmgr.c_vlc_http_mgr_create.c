#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  logger; } ;
typedef  TYPE_1__ vlc_object_t ;
struct vlc_http_mgr {int /*<<< orphan*/ * conn; struct vlc_http_cookie_jar_t* jar; int /*<<< orphan*/ * creds; TYPE_1__* obj; int /*<<< orphan*/  logger; } ;
struct vlc_http_cookie_jar_t {int dummy; } ;

/* Variables and functions */
 struct vlc_http_mgr* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct vlc_http_mgr *vlc_http_mgr_create(vlc_object_t *obj,
                                         struct vlc_http_cookie_jar_t *jar)
{
    struct vlc_http_mgr *mgr = malloc(sizeof (*mgr));
    if (unlikely(mgr == NULL))
        return NULL;

    mgr->logger = obj->logger;
    mgr->obj = obj;
    mgr->creds = NULL;
    mgr->jar = jar;
    mgr->conn = NULL;
    return mgr;
}