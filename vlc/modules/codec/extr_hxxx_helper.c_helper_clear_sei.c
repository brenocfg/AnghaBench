#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {size_t i_sei_count; TYPE_1__* sei_list; } ;
struct hxxx_helper {scalar_t__ i_codec; TYPE_2__ hevc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * b; } ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_HEVC ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
helper_clear_sei(struct hxxx_helper *hh)
{
    if (hh->i_codec != VLC_CODEC_HEVC)
        return;

    for (uint8_t i=0; i<hh->hevc.i_sei_count; i++)
    {
        if(hh->hevc.sei_list[i].b)
        {
            block_Release(hh->hevc.sei_list[i].b);
            hh->hevc.sei_list[i].b = NULL;
        }
    }
    hh->hevc.i_sei_count = 0;
}