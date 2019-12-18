#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  result; } ;
struct TYPE_10__ {scalar_t__ msg; TYPE_1__ data; int /*<<< orphan*/  easy_handle; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* on_finished ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  curl; } ;
typedef  TYPE_2__ CurlGlue ;
typedef  TYPE_3__ CURLMsg ;

/* Variables and functions */
 scalar_t__ CURLMSG_DONE ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_3__* curl_multi_info_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void curl_glue_check_finished(CurlGlue *g) {
        CURLMsg *msg;
        int k = 0;

        assert(g);

        msg = curl_multi_info_read(g->curl, &k);
        if (!msg)
                return;

        if (msg->msg != CURLMSG_DONE)
                return;

        if (g->on_finished)
                g->on_finished(g, msg->easy_handle, msg->data.result);
}