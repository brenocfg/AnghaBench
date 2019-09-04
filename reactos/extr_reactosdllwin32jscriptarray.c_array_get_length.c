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
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSCLASS_ARRAY ; 
 TYPE_1__* array_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned array_get_length(jsdisp_t *array)
{
    assert(is_class(array, JSCLASS_ARRAY));
    return array_from_jsdisp(array)->length;
}