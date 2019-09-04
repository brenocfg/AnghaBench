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
struct TYPE_3__ {scalar_t__ setter; scalar_t__ getter; int /*<<< orphan*/  value; scalar_t__ explicit_value; } ;
typedef  TYPE_1__ property_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsdisp_release (scalar_t__) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_property_descriptor(property_desc_t *desc)
{
    if(desc->explicit_value)
        jsval_release(desc->value);
    if(desc->getter)
        jsdisp_release(desc->getter);
    if(desc->setter)
        jsdisp_release(desc->setter);
}