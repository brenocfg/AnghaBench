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
struct vlc_http_msg {int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_stream_read_headers (int /*<<< orphan*/ *) ; 

struct vlc_http_msg *vlc_http_msg_iterate(struct vlc_http_msg *m)
{
    struct vlc_http_msg *next = vlc_http_stream_read_headers(m->payload);

    m->payload = NULL;
    vlc_http_msg_destroy(m);
    return next;
}