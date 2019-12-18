#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subpicture_updater_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_private; int /*<<< orphan*/  updater; } ;
typedef  TYPE_1__ subpicture_t ;
typedef  int /*<<< orphan*/  subpicture_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* subpicture_New (int /*<<< orphan*/ *) ; 

__attribute__((used)) static subpicture_t *SubpicClone( subpicture_t *p_source, subpicture_updater_t *updater )
{
    subpicture_t *p_subpic;
    subpicture_updater_t subpic_updater;
    subpicture_private_t *p_subpic_private;

    p_subpic = subpicture_New( updater );

    if( !p_subpic )
    {
        return NULL;
    }

    /* save private members */
    subpic_updater = p_subpic->updater;
    p_subpic_private = p_subpic->p_private;

    /* copy the entire struct */
    memcpy( p_subpic, p_source, sizeof( subpicture_t ) );

    /* restore private members */
    p_subpic->updater = subpic_updater;
    p_subpic->p_private = p_subpic_private;

    return p_subpic;
}