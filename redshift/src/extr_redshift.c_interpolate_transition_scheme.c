#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  night; int /*<<< orphan*/  day; } ;
typedef  TYPE_1__ transition_scheme_t ;
typedef  int /*<<< orphan*/  color_setting_t ;

/* Variables and functions */
 double CLAMP (double,double,double) ; 
 int /*<<< orphan*/  interpolate_color_settings (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,double,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
interpolate_transition_scheme(
	const transition_scheme_t *transition,
	double alpha,
	color_setting_t *result)
{
	const color_setting_t *day = &transition->day;
	const color_setting_t *night = &transition->night;

	alpha = CLAMP(0.0, alpha, 1.0);
	interpolate_color_settings(night, day, alpha, result);
}