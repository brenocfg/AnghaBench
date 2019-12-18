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
struct vlc_h2_stream {struct vlc_h2_stream* older; } ;
struct vlc_h2_parser {int dummy; } ;
struct vlc_h2_frame {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tls; } ;
struct vlc_h2_conn {int /*<<< orphan*/  lock; struct vlc_h2_stream* streams; TYPE_1__ conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CO (struct vlc_h2_conn*) ; 
 int /*<<< orphan*/  VLC_H2_CANCEL ; 
 int /*<<< orphan*/  cleanup_parser ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,struct vlc_h2_parser*) ; 
 int /*<<< orphan*/  vlc_h2_frame_dump (int /*<<< orphan*/ ,struct vlc_h2_frame*,char*) ; 
 struct vlc_h2_frame* vlc_h2_frame_recv (int /*<<< orphan*/ ) ; 
 int vlc_h2_parse (struct vlc_h2_parser*,struct vlc_h2_frame*) ; 
 int /*<<< orphan*/  vlc_h2_parse_destroy (struct vlc_h2_parser*) ; 
 struct vlc_h2_parser* vlc_h2_parse_init (struct vlc_h2_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_h2_parser_callbacks ; 
 int /*<<< orphan*/  vlc_h2_stream_reset (struct vlc_h2_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *vlc_h2_recv_thread(void *data)
{
    struct vlc_h2_conn *conn = data;
    struct vlc_h2_frame *frame;
    struct vlc_h2_parser *parser;
    int canc, val;

    canc = vlc_savecancel();
    parser = vlc_h2_parse_init(conn, &vlc_h2_parser_callbacks);
    if (unlikely(parser == NULL))
        goto fail;

    vlc_cleanup_push(cleanup_parser, parser);
    do
    {
        vlc_restorecancel(canc);
        frame = vlc_h2_frame_recv(conn->conn.tls);
        canc = vlc_savecancel();

        if (frame == NULL)
        {
            vlc_http_dbg(CO(conn), "connection shutdown");
            break;
        }

        vlc_h2_frame_dump(CO(conn), frame, "in");
        vlc_mutex_lock(&conn->lock);
        val = vlc_h2_parse(parser, frame);
        vlc_mutex_unlock(&conn->lock);
    }
    while (val == 0);

    vlc_cleanup_pop();
    vlc_h2_parse_destroy(parser);
fail:
    /* Terminate any remaining stream */
    vlc_mutex_lock(&conn->lock);
    for (struct vlc_h2_stream *s = conn->streams; s != NULL; s = s->older)
        vlc_h2_stream_reset(s, VLC_H2_CANCEL);
    vlc_mutex_unlock(&conn->lock);
    return NULL;
}