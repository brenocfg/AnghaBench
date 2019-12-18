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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint16_t ;

/* Variables and functions */
 unsigned int GetWBE (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline unsigned xiph_CountLavcHeaders(const void *p_extra, unsigned i_extra)
{
    const uint8_t *p = (const uint8_t*) p_extra;
    const uint8_t *p_end = &p[i_extra];
    /* Check headers count */
    for (int i=0; i<3; i++)
    {
        if(p_end - p < 2)
            return 0;
        uint16_t i_size = GetWBE(p);
        if(&p[2U + i_size] > p_end)
            return 0;
        p += 2 + i_size;
    }
    return 3;
}