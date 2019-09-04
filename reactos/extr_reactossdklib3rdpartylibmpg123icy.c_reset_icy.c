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
struct icy_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_icy (struct icy_meta*) ; 
 int /*<<< orphan*/  init_icy (struct icy_meta*) ; 

void reset_icy(struct icy_meta *icy)
{
	clear_icy(icy);
	init_icy(icy);
}