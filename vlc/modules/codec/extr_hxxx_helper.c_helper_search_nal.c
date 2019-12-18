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
struct hxxx_helper_nal {TYPE_1__* b; } ;
struct TYPE_2__ {size_t i_buffer; int /*<<< orphan*/  p_buffer; } ;

/* Variables and functions */
 scalar_t__ memcmp (void const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline const struct hxxx_helper_nal *
helper_search_nal(const struct hxxx_helper_nal *p_nal_list, size_t i_nal_count,
                  size_t i_nal_max, const void *p_nal_buf, size_t i_nal_buf)
{
    size_t i_nal_nb = 0;
    for (size_t i = 0; i < i_nal_max && i_nal_count > i_nal_nb; ++i)
    {
        const struct hxxx_helper_nal *p_nal = &p_nal_list[i];
        if (p_nal->b == NULL)
            continue;
        i_nal_nb++;
        const int i_diff = i_nal_buf - p_nal->b->i_buffer;
        if (i_diff == 0 && memcmp(p_nal_buf, p_nal->b->p_buffer, i_nal_buf) == 0)
            return p_nal;
    }
    return NULL;
}