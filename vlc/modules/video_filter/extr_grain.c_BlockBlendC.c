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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLEND_SIZE ; 
 int /*<<< orphan*/  BlockBlend (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BlockBlendC(uint8_t *dst, size_t dst_pitch,
                        const uint8_t *src, size_t src_pitch,
                        const int16_t *noise)
{
    BlockBlend(dst, dst_pitch, src, src_pitch, noise,
               BLEND_SIZE, BLEND_SIZE);
}