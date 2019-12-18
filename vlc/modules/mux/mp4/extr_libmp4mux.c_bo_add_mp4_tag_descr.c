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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void bo_add_mp4_tag_descr(bo_t *box, uint8_t tag, uint32_t size)
{
    bo_add_8(box, tag);
    for (int i = 3; i>0; i--)
        bo_add_8(box, (size>>(7*i)) | 0x80);
    bo_add_8(box, size & 0x7F);
}