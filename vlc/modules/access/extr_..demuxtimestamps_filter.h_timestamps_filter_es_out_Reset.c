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
struct TYPE_2__ {int i_size; scalar_t__* p_elems; } ;
struct tf_es_out_s {int b_discontinuity; int /*<<< orphan*/  pcrtf; TYPE_1__ es_list; } ;
struct tf_es_out_id_s {int /*<<< orphan*/  tf; } ;

/* Variables and functions */
 int /*<<< orphan*/  timestamps_filter_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timestamps_filter_es_out_Reset(struct tf_es_out_s *out)
{
    for(int i=0; i<out->es_list.i_size; i++)
    {
        struct tf_es_out_id_s *cur = (struct tf_es_out_id_s *)out->es_list.p_elems[i];
        timestamps_filter_init(&cur->tf);
    }
    timestamps_filter_init(&out->pcrtf);
    out->b_discontinuity = false;
}