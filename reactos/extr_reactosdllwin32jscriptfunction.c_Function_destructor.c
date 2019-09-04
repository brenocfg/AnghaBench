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
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {scalar_t__ scope_chain; scalar_t__ code; } ;
typedef  TYPE_1__ FunctionInstance ;

/* Variables and functions */
 TYPE_1__* function_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  release_bytecode (scalar_t__) ; 
 int /*<<< orphan*/  scope_release (scalar_t__) ; 

__attribute__((used)) static void Function_destructor(jsdisp_t *dispex)
{
    FunctionInstance *This = function_from_jsdisp(dispex);

    if(This->code)
        release_bytecode(This->code);
    if(This->scope_chain)
        scope_release(This->scope_chain);
    heap_free(This);
}