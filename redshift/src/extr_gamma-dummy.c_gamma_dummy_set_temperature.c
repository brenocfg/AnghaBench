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
struct TYPE_3__ {int temperature; } ;
typedef  TYPE_1__ color_setting_t ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
gamma_dummy_set_temperature(
	void *state, const color_setting_t *setting, int preserve)
{
	printf(_("Temperature: %i\n"), setting->temperature);
	return 0;
}