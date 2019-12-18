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
struct vlc_http_stream {int dummy; } ;
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_req_create (char*,char*,char*,char*) ; 
 struct vlc_http_stream* vlc_http_stream_open (int /*<<< orphan*/ ,struct vlc_http_msg*) ; 

__attribute__((used)) static struct vlc_http_stream *stream_open(void)
{
    struct vlc_http_msg *m = vlc_http_req_create("GET", "https",
                                                 "www.example.com", "/");
    assert(m != NULL);

    struct vlc_http_stream *s = vlc_http_stream_open(conn, m);
    vlc_http_msg_destroy(m);
    return s;
}