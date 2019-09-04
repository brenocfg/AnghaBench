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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ attr_t ;
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 scalar_t__ ATTR_IN ; 

__attribute__((used)) static int arg_out_attrs(attr_list_t *attrs, const attr_t *attr)
{
    return attr->type != ATTR_IN;
}