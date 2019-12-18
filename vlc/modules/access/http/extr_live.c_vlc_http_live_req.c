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
struct vlc_http_resource {int dummy; } ;
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_http_msg_add_header (struct vlc_http_msg*,char*,char*) ; 

__attribute__((used)) static int vlc_http_live_req(const struct vlc_http_resource *res,
                             struct vlc_http_msg *req, void *opaque)
{
    vlc_http_msg_add_header(req, "Accept-Encoding", "gzip, deflate");
    (void) res;
    (void) opaque;
    return 0;
}