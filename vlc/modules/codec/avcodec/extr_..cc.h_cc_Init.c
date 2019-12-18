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
struct TYPE_3__ {int b_reorder; scalar_t__ i_payload_other_count; int /*<<< orphan*/  i_payload_type; scalar_t__ i_data; scalar_t__ i_708channels; scalar_t__ i_608channels; } ;
typedef  TYPE_1__ cc_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_PAYLOAD_NONE ; 

__attribute__((used)) static inline void cc_Init( cc_data_t *c )
{
    c->i_608channels = 0;
    c->i_708channels = 0;
    c->i_data = 0;
    c->b_reorder = false;
    c->i_payload_type = CC_PAYLOAD_NONE;
    c->i_payload_other_count = 0;
}