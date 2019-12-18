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
struct record_packet {int /*<<< orphan*/  packet; } ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_free (struct record_packet*) ; 
 struct record_packet* SDL_malloc (int) ; 
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 scalar_t__ av_packet_ref (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct record_packet *
record_packet_new(const AVPacket *packet) {
    struct record_packet *rec = SDL_malloc(sizeof(*rec));
    if (!rec) {
        return NULL;
    }

    // av_packet_ref() does not initialize all fields in old FFmpeg versions
    // See <https://github.com/Genymobile/scrcpy/issues/707>
    av_init_packet(&rec->packet);

    if (av_packet_ref(&rec->packet, packet)) {
        SDL_free(rec);
        return NULL;
    }
    return rec;
}