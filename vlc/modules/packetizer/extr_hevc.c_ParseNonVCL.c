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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 scalar_t__ HEVC_NAL_AUD ; 
 scalar_t__ HEVC_NAL_PREF_SEI ; 
 scalar_t__ HEVC_NAL_RSV_NVCL41 ; 
 scalar_t__ HEVC_NAL_RSV_NVCL44 ; 
 scalar_t__ HEVC_NAL_UNSPEC48 ; 
 scalar_t__ HEVC_NAL_UNSPEC55 ; 
 scalar_t__ HEVC_NAL_VPS ; 
 int /*<<< orphan*/ * ParseAUHead (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseAUTail (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t * ParseNonVCL(decoder_t *p_dec, uint8_t i_nal_type, block_t *p_nalb)
{
    block_t *p_ret = NULL;

    if ( (i_nal_type >= HEVC_NAL_VPS        && i_nal_type <= HEVC_NAL_AUD) ||
          i_nal_type == HEVC_NAL_PREF_SEI ||
         (i_nal_type >= HEVC_NAL_RSV_NVCL41 && i_nal_type <= HEVC_NAL_RSV_NVCL44) ||
         (i_nal_type >= HEVC_NAL_UNSPEC48   && i_nal_type <= HEVC_NAL_UNSPEC55) )
    {
        p_ret = ParseAUHead(p_dec, i_nal_type, p_nalb);
    }
    else
    {
        p_ret = ParseAUTail(p_dec, i_nal_type, p_nalb);
    }

    return p_ret;
}