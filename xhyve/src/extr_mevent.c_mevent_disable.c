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
struct mevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEV_DISABLE ; 
 int mevent_update (struct mevent*,int /*<<< orphan*/ ) ; 

int
mevent_disable(struct mevent *evp)
{

	return (mevent_update(evp, MEV_DISABLE));
}