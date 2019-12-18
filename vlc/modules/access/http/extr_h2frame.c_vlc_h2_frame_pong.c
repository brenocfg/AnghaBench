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
typedef  int /*<<< orphan*/  uint64_t ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_FRAME_PING ; 
 int /*<<< orphan*/  VLC_H2_PING_ACK ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct vlc_h2_frame* vlc_h2_frame_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_h2_frame_payload (struct vlc_h2_frame*) ; 

struct vlc_h2_frame *vlc_h2_frame_pong(uint64_t opaque)
{
    struct vlc_h2_frame *f = vlc_h2_frame_alloc(VLC_H2_FRAME_PING,
                                                VLC_H2_PING_ACK, 0, 8);
    if (likely(f != NULL))
        memcpy(vlc_h2_frame_payload(f), &opaque, 8);
    return f;
}