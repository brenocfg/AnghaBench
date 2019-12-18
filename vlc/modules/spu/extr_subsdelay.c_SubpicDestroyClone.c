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
struct TYPE_4__ {int /*<<< orphan*/ * p_region; } ;
typedef  TYPE_1__ subpicture_t ;

/* Variables and functions */
 int /*<<< orphan*/  subpicture_Delete (TYPE_1__*) ; 

__attribute__((used)) static void SubpicDestroyClone( subpicture_t *p_subpic )
{
    p_subpic->p_region = NULL; /* don't destroy region */
    subpicture_Delete( p_subpic );
}