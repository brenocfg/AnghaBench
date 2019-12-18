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
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ cc_storage_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_PAYLOAD_GA94 ; 
 int /*<<< orphan*/  cc_Extract (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ; 

void cc_storage_append( cc_storage_t *p_ccs, bool b_top_field_first,
                        const uint8_t *p_buf, size_t i_buf )
{
    cc_Extract( &p_ccs->next, CC_PAYLOAD_GA94, b_top_field_first, p_buf, i_buf );
}