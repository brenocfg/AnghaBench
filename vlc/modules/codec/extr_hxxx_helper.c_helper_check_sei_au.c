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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ i_previous_nal_type; } ;
struct hxxx_helper {TYPE_1__ hevc; } ;

/* Variables and functions */
 scalar_t__ HEVC_NAL_IRAP_VCL23 ; 
 scalar_t__ HEVC_NAL_PREF_SEI ; 
 int /*<<< orphan*/  helper_clear_sei (struct hxxx_helper*) ; 

__attribute__((used)) static void
helper_check_sei_au(struct hxxx_helper *hh, uint8_t i_nal_type)
{
    if ((i_nal_type <= HEVC_NAL_IRAP_VCL23 &&
         hh->hevc.i_previous_nal_type != HEVC_NAL_PREF_SEI) ||
        (i_nal_type == HEVC_NAL_PREF_SEI &&
         hh->hevc.i_previous_nal_type != HEVC_NAL_PREF_SEI))
        helper_clear_sei(hh);
    hh->hevc.i_previous_nal_type = i_nal_type;
}