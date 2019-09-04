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
struct window {int dummy; } ;

/* Variables and functions */
 int alerts_check_activity (struct window*) ; 
 int alerts_check_bell (struct window*) ; 
 int alerts_check_silence (struct window*) ; 

__attribute__((used)) static int
alerts_check_all(struct window *w)
{
	int	alerts;

	alerts	= alerts_check_bell(w);
	alerts |= alerts_check_activity(w);
	alerts |= alerts_check_silence(w);
	return (alerts);
}