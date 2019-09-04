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
struct d3dx_sampler {size_t state_count; int /*<<< orphan*/ * states; } ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_sampler(struct d3dx_sampler *sampler)
{
    UINT i;

    for (i = 0; i < sampler->state_count; ++i)
    {
        free_state(&sampler->states[i]);
    }
    HeapFree(GetProcessHeap(), 0, sampler->states);
}