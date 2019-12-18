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
 int /*<<< orphan*/  vlc_http_stream_close (struct vlc_http_stream*,int) ; 
 struct vlc_http_msg* vlc_http_stream_read_headers (struct vlc_http_stream*) ; 

struct vlc_http_msg *vlc_http_msg_get_initial(struct vlc_http_stream *s)
{
    struct vlc_http_msg *m = vlc_http_stream_read_headers(s);
    if (m == NULL)
        vlc_http_stream_close(s, false);
    return m;
}