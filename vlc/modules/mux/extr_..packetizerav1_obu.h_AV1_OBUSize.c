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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int AV1_OBUHasExtensionField (scalar_t__ const*) ; 
 int /*<<< orphan*/  AV1_OBUHasSizeField (scalar_t__ const*) ; 
 int INT64_C (int) ; 
 int leb128 (scalar_t__ const*,size_t,scalar_t__*) ; 

__attribute__((used)) static uint32_t AV1_OBUSize(const uint8_t *p_buf, size_t i_buf, uint8_t *pi_len)
{
    if(!AV1_OBUHasSizeField(p_buf))
    {
        if(AV1_OBUHasExtensionField(p_buf) && i_buf < 2)
            return false;
        return i_buf - 1 - AV1_OBUHasExtensionField(p_buf);
    }

    if(AV1_OBUHasExtensionField(p_buf))
    {
        if(i_buf == 1)
        {
            *pi_len = 0;
            return 0;
        }
        /* skip extension header */
        p_buf += 1;
        i_buf -= 1;
    }
    uint64_t i_size = leb128(&p_buf[1], i_buf - 1, pi_len);
    if(i_size > (INT64_C(1) << 32) - 1)
    {
        *pi_len = 0;
        return 0;
    }
    return i_size;
}