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
typedef  int /*<<< orphan*/  uint_fast32_t ;
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_msg_add_agent (struct vlc_http_msg*,char*) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 int /*<<< orphan*/  vlc_http_msg_h2_frame (struct vlc_http_msg*,int /*<<< orphan*/ ,int) ; 
 struct vlc_http_msg* vlc_http_resp_create (int) ; 

__attribute__((used)) static void stream_reply(uint_fast32_t id, bool nodata)
{
    struct vlc_http_msg *m = vlc_http_resp_create(200);
    assert(m != NULL);
    vlc_http_msg_add_agent(m, "VLC-h2-tester");

    conn_send(vlc_http_msg_h2_frame(m, id, nodata));
    vlc_http_msg_destroy(m);
}