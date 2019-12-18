#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pi_priority_flag; int /*<<< orphan*/  pi_priority_stream_number; } ;
struct TYPE_4__ {TYPE_2__ stream_prioritization; } ;
typedef  TYPE_1__ asf_object_t ;
typedef  TYPE_2__ asf_object_stream_prioritization_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ASF_FreeObject_stream_prioritization( asf_object_t *p_obj)
{
    asf_object_stream_prioritization_t *p_sp = &p_obj->stream_prioritization;

    FREENULL( p_sp->pi_priority_stream_number );
    FREENULL( p_sp->pi_priority_flag );
}