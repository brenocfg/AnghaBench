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
struct hxxx_helper {int i_nal_length_size; int b_is_xvcC; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  helper_nal_length_valid (struct hxxx_helper*) ; 
 int helper_process_hvcC_hevc (struct hxxx_helper*,void const*,size_t) ; 
 int hevc_getNALLengthSize (void const*) ; 
 int hevc_helper_parse_nal (struct hxxx_helper*,void const*,size_t,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ hevc_ishvcC (void const*,size_t) ; 
 scalar_t__ hxxx_extra_isannexb (void const*,size_t) ; 

__attribute__((used)) static int
hevc_helper_set_extra(struct hxxx_helper *hh, const void *p_extra,
                      size_t i_extra)
{
    if (hevc_ishvcC(p_extra, i_extra))
    {
        hh->i_nal_length_size = hevc_getNALLengthSize(p_extra);
        if (!helper_nal_length_valid(hh))
            return VLC_EGENERIC;
        hh->b_is_xvcC = true;

        return helper_process_hvcC_hevc( hh, p_extra, i_extra );
    }
    else if (hxxx_extra_isannexb(p_extra, i_extra))
    {
        hh->i_nal_length_size = 4;
        bool unused;
        return i_extra == 0 ? VLC_SUCCESS :
               hevc_helper_parse_nal(hh, p_extra, i_extra, 0, &unused);
    }
    else
        return VLC_EGENERIC;
}