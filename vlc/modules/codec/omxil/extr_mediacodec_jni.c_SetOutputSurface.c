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
typedef  int /*<<< orphan*/  mc_api ;

/* Variables and functions */
 int MC_API_ERROR ; 

__attribute__((used)) static int SetOutputSurface(mc_api *api, void *p_surface, void *p_jsurface)
{
    (void) api; (void) p_surface; (void) p_jsurface;

    return MC_API_ERROR;
}