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

/* Variables and functions */
 int /*<<< orphan*/  SDL_free (struct record_packet*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
record_packet_delete(struct record_packet *rec) {
    av_packet_unref(&rec->packet);
    SDL_free(rec);
}