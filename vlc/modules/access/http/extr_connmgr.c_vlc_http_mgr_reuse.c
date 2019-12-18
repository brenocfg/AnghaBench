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
struct vlc_http_mgr {int dummy; } ;
struct vlc_http_conn {int dummy; } ;

/* Variables and functions */
 struct vlc_http_conn* vlc_http_mgr_find (struct vlc_http_mgr*,char const*,unsigned int) ; 
 int /*<<< orphan*/  vlc_http_mgr_release (struct vlc_http_mgr*,struct vlc_http_conn*) ; 
 struct vlc_http_msg* vlc_http_msg_get_initial (struct vlc_http_stream*) ; 
 struct vlc_http_stream* vlc_http_stream_open (struct vlc_http_conn*,struct vlc_http_msg const*) ; 

__attribute__((used)) static
struct vlc_http_msg *vlc_http_mgr_reuse(struct vlc_http_mgr *mgr,
                                        const char *host, unsigned port,
                                        const struct vlc_http_msg *req)
{
    struct vlc_http_conn *conn = vlc_http_mgr_find(mgr, host, port);
    if (conn == NULL)
        return NULL;

    struct vlc_http_stream *stream = vlc_http_stream_open(conn, req);
    if (stream != NULL)
    {
        struct vlc_http_msg *m = vlc_http_msg_get_initial(stream);
        if (m != NULL)
            return m;

        /* NOTE: If the request were not idempotent, we would not know if it
         * was processed by the other end. Thus POST is not used/supported so
         * far, and CONNECT is treated as if it were idempotent (which works
         * fine here). */
    }
    /* Get rid of closing or reset connection */
    vlc_http_mgr_release(mgr, conn);
    return NULL;
}