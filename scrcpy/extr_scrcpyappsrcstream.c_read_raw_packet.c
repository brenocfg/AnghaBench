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
typedef  int /*<<< orphan*/  uint8_t ;
struct stream {int /*<<< orphan*/  socket; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  errno ; 
 int net_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
read_raw_packet(void *opaque, uint8_t *buf, int buf_size) {
    struct stream *stream = opaque;
    ssize_t r = net_recv(stream->socket, buf, buf_size);
    if (r == -1) {
        return AVERROR(errno);
    }
    if (r == 0) {
        return AVERROR_EOF;
    }
    return r;
}