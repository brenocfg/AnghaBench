#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ MuOfficeRender ;

/* Variables and functions */
 int /*<<< orphan*/  MuOfficeRender_abort (TYPE_1__*) ; 
 int /*<<< orphan*/  Pal_Mem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mu_destroy_thread (int /*<<< orphan*/ *) ; 

void MuOfficeRender_destroy(MuOfficeRender *render)
{
	if (!render)
		return;

	MuOfficeRender_abort(render);
	mu_destroy_thread(&render->thread);
	Pal_Mem_free(render);
}