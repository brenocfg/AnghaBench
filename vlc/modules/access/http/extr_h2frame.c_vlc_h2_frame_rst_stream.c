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
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetDWBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_H2_FRAME_RST_STREAM ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct vlc_h2_frame* vlc_h2_frame_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_h2_frame_payload (struct vlc_h2_frame*) ; 

struct vlc_h2_frame *
vlc_h2_frame_rst_stream(uint_fast32_t stream_id, uint_fast32_t error_code)
{
    struct vlc_h2_frame *f = vlc_h2_frame_alloc(VLC_H2_FRAME_RST_STREAM, 0,
                                                stream_id, 4);
    if (likely(f != NULL))
        SetDWBE(vlc_h2_frame_payload(f), error_code);
    return f;
}