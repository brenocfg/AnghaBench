#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct d3dx_pass {unsigned int annotation_count; unsigned int state_count; int /*<<< orphan*/ * name; int /*<<< orphan*/ * states; int /*<<< orphan*/ * annotations; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3dx_pass*) ; 
 int /*<<< orphan*/  free_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_pass(struct d3dx_pass *pass)
{
    unsigned int i;

    TRACE("Free pass %p\n", pass);

    if (!pass)
        return;

    if (pass->annotations)
    {
        for (i = 0; i < pass->annotation_count; ++i)
            free_parameter(&pass->annotations[i], FALSE, FALSE);
        HeapFree(GetProcessHeap(), 0, pass->annotations);
        pass->annotations = NULL;
    }

    if (pass->states)
    {
        for (i = 0; i < pass->state_count; ++i)
            free_state(&pass->states[i]);
        HeapFree(GetProcessHeap(), 0, pass->states);
        pass->states = NULL;
    }

    HeapFree(GetProcessHeap(), 0, pass->name);
    pass->name = NULL;
}