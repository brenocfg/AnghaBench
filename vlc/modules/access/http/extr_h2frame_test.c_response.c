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
 int /*<<< orphan*/  resp_hdrc ; 
 int /*<<< orphan*/  resp_hdrv ; 
 struct vlc_h2_frame* vlc_h2_frame_headers (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vlc_h2_frame *response(bool eos)
{
    /* Use ridiculously small MTU to test headers fragmentation */
    return vlc_h2_frame_headers(STREAM_ID, 16, eos, resp_hdrc, resp_hdrv);
}