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
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 scalar_t__ HEVC_NAL_PPS ; 
 scalar_t__ HEVC_NAL_SPS ; 
 scalar_t__ HEVC_PPS_ID_MAX ; 
 scalar_t__ HEVC_SPS_ID_MAX ; 
 scalar_t__ HEVC_VPS_ID_MAX ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,scalar_t__ const*,size_t) ; 
 scalar_t__ bs_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bs_read_ue (int /*<<< orphan*/ *) ; 
 scalar_t__ hevc_getNALType (scalar_t__ const*) ; 

bool hevc_get_xps_id(const uint8_t *p_buf, size_t i_buf, uint8_t *pi_id)
{
    if(i_buf < 3)
        return false;
    /* No need to lookup convert from emulation for that data */
    uint8_t i_nal_type = hevc_getNALType(p_buf);
    bs_t bs;
    bs_init(&bs, &p_buf[2], i_buf - 2);
    if(i_nal_type == HEVC_NAL_PPS)
    {
        *pi_id = bs_read_ue( &bs );
        if(*pi_id > HEVC_PPS_ID_MAX)
            return false;
    }
    else
    {
        *pi_id = bs_read( &bs, 4 );
        if(i_nal_type == HEVC_NAL_SPS)
        {
            if(*pi_id > HEVC_SPS_ID_MAX)
                return false;
        }
        else if(*pi_id > HEVC_VPS_ID_MAX)
            return false;
    }
    return true;
}