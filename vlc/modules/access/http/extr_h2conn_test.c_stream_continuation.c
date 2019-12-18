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

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_DEFAULT_MAX_FRAME ; 
 int /*<<< orphan*/  conn_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_frame_headers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const***) ; 

__attribute__((used)) static void stream_continuation(uint_fast32_t id)
{
    const char *h[][2] = {
        { ":status", "100" },
    };

    conn_send(vlc_h2_frame_headers(id, VLC_H2_DEFAULT_MAX_FRAME, false, 1, h));
}