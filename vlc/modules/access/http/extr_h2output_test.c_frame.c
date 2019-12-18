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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct vlc_h2_frame* vlc_h2_frame_data (int,unsigned char*,int,int) ; 

__attribute__((used)) static struct vlc_h2_frame *frame(unsigned char c)
{
    struct vlc_h2_frame *f = vlc_h2_frame_data(1, &c, 1, false);
    assert(f != NULL);
    return f;
}