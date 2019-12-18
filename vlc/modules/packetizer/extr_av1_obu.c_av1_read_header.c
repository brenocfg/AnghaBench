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
typedef  int uint8_t ;
struct av1_header_info_s {void* spatial_id; void* temporal_id; void* obu_type; } ;
typedef  scalar_t__ obu_u1_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bs_read1 (int /*<<< orphan*/ *) ; 
 int bs_remain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool av1_read_header(bs_t *p_bs, struct av1_header_info_s *p_hdr)
{
    if(bs_read1(p_bs))
        return false;
    p_hdr->obu_type = bs_read(p_bs, 4);
    const obu_u1_t obu_extension_flag = bs_read1(p_bs);
    const obu_u1_t obu_has_size_field = bs_read1(p_bs);
    if(bs_read1(p_bs))
        return false;
    if(obu_extension_flag)
    {
        if(bs_remain(p_bs) < 8)
            return false;
        p_hdr->temporal_id = bs_read(p_bs, 3);
        p_hdr->spatial_id = bs_read(p_bs, 2);
        bs_skip(p_bs, 3);
    }
    if(obu_has_size_field)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            if(bs_remain(p_bs) < 8)
                return false;
            uint8_t v = bs_read(p_bs, 8);
            if (!(v & 0x80))
                break;
            if(i == 7)
                return false;
        }
    }
    return true;
}