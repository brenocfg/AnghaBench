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
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_3__ {int argc; } ;
typedef  TYPE_1__ ArgumentsInstance ;

/* Variables and functions */
 TYPE_1__* arguments_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned Arguments_idx_length(jsdisp_t *jsdisp)
{
    ArgumentsInstance *arguments = arguments_from_jsdisp(jsdisp);
    return arguments->argc;
}