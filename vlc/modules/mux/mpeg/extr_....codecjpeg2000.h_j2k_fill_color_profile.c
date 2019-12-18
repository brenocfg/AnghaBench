#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_transfer_func_t ;
typedef  int /*<<< orphan*/  video_color_space_t ;
typedef  int /*<<< orphan*/  video_color_primaries_t ;
typedef  enum j2k_color_specs_e { ____Placeholder_j2k_color_specs_e } j2k_color_specs_e ;
struct TYPE_2__ {int /*<<< orphan*/  space; int /*<<< orphan*/  transfer; int /*<<< orphan*/  primaries; } ;

/* Variables and functions */
 int J2K_COLOR_SPEC_SMPTE_2084 ; 
 int J2K_COLOR_SPEC_UNKNOWN ; 
 TYPE_1__* j2k_color_specifications ; 

__attribute__((used)) static inline void j2k_fill_color_profile( enum j2k_color_specs_e e,
                                           video_color_primaries_t *primaries,
                                           video_transfer_func_t *transfer,
                                           video_color_space_t *space )
{
    if( e > J2K_COLOR_SPEC_UNKNOWN && e <= J2K_COLOR_SPEC_SMPTE_2084 )
    {
        *primaries = j2k_color_specifications[e].primaries;
        *transfer = j2k_color_specifications[e].transfer;
        *space = j2k_color_specifications[e].space;
    }
}