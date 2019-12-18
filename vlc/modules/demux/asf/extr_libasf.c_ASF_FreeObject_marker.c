#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  asf_object_t ;
struct TYPE_3__ {size_t i_count; TYPE_2__* name; TYPE_2__* marker; } ;
typedef  TYPE_1__ asf_object_marker_t ;
struct TYPE_4__ {struct TYPE_4__* p_marker_description; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (TYPE_2__*) ; 

__attribute__((used)) static void ASF_FreeObject_marker( asf_object_t *p_obj)
{
    asf_object_marker_t *p_mk = (asf_object_marker_t *)p_obj;

    for( uint32_t i = 0; i < p_mk->i_count; i++ )
    {
        FREENULL( p_mk->marker[i].p_marker_description  );
    }
    FREENULL( p_mk->marker );
    FREENULL( p_mk->name );
}