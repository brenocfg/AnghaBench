#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cbs; } ;
struct tf_es_out_s {int b_discontinuity; TYPE_1__ es_out; int /*<<< orphan*/  es_list; int /*<<< orphan*/  pcrtf; TYPE_1__* original_es_out; } ;
typedef  TYPE_1__ es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct tf_es_out_s*) ; 
 struct tf_es_out_s* malloc (int) ; 
 int /*<<< orphan*/  timestamps_filter_es_out_cbs ; 
 int /*<<< orphan*/  timestamps_filter_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static es_out_t * timestamps_filter_es_out_New(es_out_t *orig)
{
    struct tf_es_out_s *tf = malloc(sizeof(*tf));
    if(!tf)
    {
        free(tf);
        return NULL;
    }
    tf->original_es_out = orig;
    tf->b_discontinuity = false;
    timestamps_filter_init(&tf->pcrtf);
    ARRAY_INIT(tf->es_list);

    tf->es_out.cbs = &timestamps_filter_es_out_cbs;

    return &tf->es_out;
}