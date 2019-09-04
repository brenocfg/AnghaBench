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
typedef  scalar_t__ uint64_t ;
struct receiver_state {int remaining; } ;
struct stream {int /*<<< orphan*/  socket; struct receiver_state receiver_state; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  LOGE (char*) ; 
 scalar_t__ NO_PTS ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  SDL_assert_release (int) ; 
 int buffer_read32be (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_read64be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int net_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int net_recv_all (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  receiver_state_push_meta (struct receiver_state*,scalar_t__) ; 

__attribute__((used)) static int
read_packet_with_meta(void *opaque, uint8_t *buf, int buf_size) {
    struct stream *stream = opaque;
    struct receiver_state *state = &stream->receiver_state;

    // The video stream contains raw packets, without time information. When we
    // record, we retrieve the timestamps separately, from a "meta" header
    // added by the server before each raw packet.
    //
    // The "meta" header length is 12 bytes:
    // [. . . . . . . .|. . . .]. . . . . . . . . . . . . . . ...
    //  <-------------> <-----> <-----------------------------...
    //        PTS        packet        raw packet
    //                    size
    //
    // It is followed by <packet_size> bytes containing the packet/frame.

    if (!state->remaining) {
#define HEADER_SIZE 12
        uint8_t header[HEADER_SIZE];
        ssize_t r = net_recv_all(stream->socket, header, HEADER_SIZE);
        if (r == -1) {
            return AVERROR(errno);
        }
        if (r == 0) {
            return AVERROR_EOF;
        }
        // no partial read (net_recv_all())
        SDL_assert_release(r == HEADER_SIZE);

        uint64_t pts = buffer_read64be(header);
        state->remaining = buffer_read32be(&header[8]);

        if (pts != NO_PTS && !receiver_state_push_meta(state, pts)) {
            LOGE("Could not store PTS for recording");
            // we cannot save the PTS, the recording would be broken
            return AVERROR(ENOMEM);
        }
    }

    SDL_assert(state->remaining);

    if (buf_size > state->remaining) {
        buf_size = state->remaining;
    }

    ssize_t r = net_recv(stream->socket, buf, buf_size);
    if (r == -1) {
        return AVERROR(errno);
    }
    if (r == 0) {
        return AVERROR_EOF;
    }

    SDL_assert(state->remaining >= r);
    state->remaining -= r;

    return r;
}