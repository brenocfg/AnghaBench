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
struct vlc_http_stream {int dummy; } ;
struct vlc_http_msg {int dummy; } ;
struct vlc_http_conn {TYPE_1__* cbs; } ;
struct TYPE_2__ {struct vlc_http_stream* (* stream_open ) (struct vlc_http_conn*,struct vlc_http_msg const*) ;} ;

/* Variables and functions */
 struct vlc_http_stream* stub1 (struct vlc_http_conn*,struct vlc_http_msg const*) ; 

__attribute__((used)) static inline struct vlc_http_stream *
vlc_http_stream_open(struct vlc_http_conn *conn, const struct vlc_http_msg *m)
{
    return conn->cbs->stream_open(conn, m);
}