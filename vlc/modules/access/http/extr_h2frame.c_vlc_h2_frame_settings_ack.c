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
 int /*<<< orphan*/  VLC_H2_FRAME_SETTINGS ; 
 int /*<<< orphan*/  VLC_H2_SETTINGS_ACK ; 
 struct vlc_h2_frame* vlc_h2_frame_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct vlc_h2_frame *vlc_h2_frame_settings_ack(void)
{
    return vlc_h2_frame_alloc(VLC_H2_FRAME_SETTINGS, VLC_H2_SETTINGS_ACK, 0,
                              0);
}