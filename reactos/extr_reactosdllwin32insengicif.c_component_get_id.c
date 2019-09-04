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
struct cifcomponent {char* id; } ;
typedef  int /*<<< orphan*/  ICifComponent ;

/* Variables and functions */
 struct cifcomponent* impl_from_ICifComponent (int /*<<< orphan*/ *) ; 

char *component_get_id(ICifComponent *iface)
{
    struct cifcomponent *This = impl_from_ICifComponent(iface);

    return This->id;
}