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
struct skiptags_sys_t {int /*<<< orphan*/ * p_tags; scalar_t__ header_skip; } ;

/* Variables and functions */
 struct skiptags_sys_t* malloc (int) ; 

__attribute__((used)) static struct skiptags_sys_t * skiptags_sys_New(void)
{
    struct skiptags_sys_t *sys = malloc(sizeof (*sys));
    if(sys)
    {
        sys->header_skip = 0;
        sys->p_tags = NULL;
    }
    return sys;
}