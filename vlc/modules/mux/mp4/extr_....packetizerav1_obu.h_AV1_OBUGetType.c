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
typedef  enum av1_obu_type_e { ____Placeholder_av1_obu_type_e } av1_obu_type_e ;

/* Variables and functions */

__attribute__((used)) static inline enum av1_obu_type_e AV1_OBUGetType(const uint8_t *p_buf)
{
    return (enum av1_obu_type_e)((p_buf[0] >> 3) & 0x0F);
}