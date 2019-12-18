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
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_ID ; 
 int /*<<< orphan*/  VLC_H2_CANCEL ; 
 struct vlc_h2_frame* vlc_h2_frame_rst_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vlc_h2_frame *rst_stream(void)
{
    return vlc_h2_frame_rst_stream(STREAM_ID, VLC_H2_CANCEL);
}