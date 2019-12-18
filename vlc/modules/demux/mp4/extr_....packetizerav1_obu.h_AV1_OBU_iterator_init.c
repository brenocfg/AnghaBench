#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  const* p_tail; int /*<<< orphan*/  const* p_head; } ;
typedef  TYPE_1__ AV1_OBU_iterator_ctx_t ;

/* Variables and functions */

__attribute__((used)) static inline void AV1_OBU_iterator_init(AV1_OBU_iterator_ctx_t *p_ctx,
                                         const uint8_t *p_data, size_t i_data)
{
    p_ctx->p_head = p_data;
    p_ctx->p_tail = p_data + i_data;
}