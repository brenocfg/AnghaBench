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
struct vlc_http_resource {int /*<<< orphan*/ * response; int /*<<< orphan*/  host; int /*<<< orphan*/  authority; int /*<<< orphan*/  path; int /*<<< orphan*/  username; int /*<<< orphan*/  password; int /*<<< orphan*/  agent; int /*<<< orphan*/  referrer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_http_res_deinit(struct vlc_http_resource *res)
{
    free(res->referrer);
    free(res->agent);
    free(res->password);
    free(res->username);
    free(res->path);
    free(res->authority);
    free(res->host);

    if (res->response != NULL)
        vlc_http_msg_destroy(res->response);
}