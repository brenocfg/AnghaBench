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
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * box_new (char const*) ; 

__attribute__((used)) static bo_t *GetxxxxTag(const uint8_t *p_extra, size_t i_extra,
                        const char *tag)
{
    bo_t *box = box_new(tag);
    if(!box)
        return NULL;
    bo_add_mem(box, i_extra, p_extra);
    return box;
}