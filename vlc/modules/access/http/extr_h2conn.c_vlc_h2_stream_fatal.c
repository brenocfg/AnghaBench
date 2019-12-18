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
struct vlc_h2_stream {int recv_end; int /*<<< orphan*/  id; int /*<<< orphan*/  conn; int /*<<< orphan*/  recv_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROTO ; 
 int vlc_h2_stream_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_h2_stream_fatal(struct vlc_h2_stream *s, uint_fast32_t code)
{
    s->recv_end = true;
    s->recv_err = EPROTO;
    return vlc_h2_stream_error(s->conn, s->id, code);
}