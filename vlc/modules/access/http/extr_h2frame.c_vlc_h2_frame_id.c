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
typedef  int uint_fast32_t ;
struct vlc_h2_frame {scalar_t__ data; } ;

/* Variables and functions */
 int GetDWBE (scalar_t__) ; 

__attribute__((used)) static uint_fast32_t vlc_h2_frame_id(const struct vlc_h2_frame *f)
{
    return GetDWBE(f->data + 5) & 0x7FFFFFFF;
}