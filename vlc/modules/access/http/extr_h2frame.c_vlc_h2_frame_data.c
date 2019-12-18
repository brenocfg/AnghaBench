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
typedef  int /*<<< orphan*/  uint8_t ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_DATA_END_STREAM ; 
 int /*<<< orphan*/  VLC_H2_FRAME_DATA ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 struct vlc_h2_frame* vlc_h2_frame_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vlc_h2_frame_payload (struct vlc_h2_frame*) ; 

struct vlc_h2_frame *
vlc_h2_frame_data(uint_fast32_t stream_id, const void *buf, size_t len,
                  bool eos)
{
    struct vlc_h2_frame *f;
    uint8_t flags = eos ? VLC_H2_DATA_END_STREAM : 0;

    f = vlc_h2_frame_alloc(VLC_H2_FRAME_DATA, flags, stream_id, len);
    if (likely(f != NULL))
        memcpy(vlc_h2_frame_payload(f), buf, len);
    return f;
}