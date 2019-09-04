#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_8__ {unsigned int argc; TYPE_1__* function; struct TYPE_8__* buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  dispex; } ;
typedef  TYPE_2__ ArgumentsInstance ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 TYPE_2__* arguments_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (TYPE_2__) ; 

__attribute__((used)) static void Arguments_destructor(jsdisp_t *jsdisp)
{
    ArgumentsInstance *arguments = arguments_from_jsdisp(jsdisp);

    TRACE("(%p)\n", arguments);

    if(arguments->buf) {
        unsigned i;
        for(i = 0; i < arguments->argc; i++)
            jsval_release(arguments->buf[i]);
        heap_free(arguments->buf);
    }

    jsdisp_release(&arguments->function->dispex);
    heap_free(arguments);
}