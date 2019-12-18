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
struct TYPE_5__ {int /*<<< orphan*/  p_error_correction_data; int /*<<< orphan*/  p_type_specific_data; } ;
struct TYPE_4__ {TYPE_2__ stream_properties; } ;
typedef  TYPE_1__ asf_object_t ;
typedef  TYPE_2__ asf_object_stream_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ASF_FreeObject_stream_properties( asf_object_t *p_obj )
{
    asf_object_stream_properties_t *p_sp = &p_obj->stream_properties;

    FREENULL( p_sp->p_type_specific_data );
    FREENULL( p_sp->p_error_correction_data );
}