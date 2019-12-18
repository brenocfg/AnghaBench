#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ temperature; void** gamma; void* brightness; } ;
struct TYPE_6__ {scalar_t__ temperature; void** gamma; void* brightness; } ;
struct TYPE_8__ {TYPE_2__ night; TYPE_1__ day; } ;
struct TYPE_9__ {int use_fade; TYPE_3__ scheme; } ;
typedef  TYPE_4__ options_t ;

/* Variables and functions */
 void* DEFAULT_BRIGHTNESS ; 
 scalar_t__ DEFAULT_DAY_TEMP ; 
 void* DEFAULT_GAMMA ; 
 scalar_t__ DEFAULT_NIGHT_TEMP ; 
 scalar_t__ isnan (void*) ; 

void
options_set_defaults(options_t *options)
{
	if (options->scheme.day.temperature < 0) {
		options->scheme.day.temperature = DEFAULT_DAY_TEMP;
	}
	if (options->scheme.night.temperature < 0) {
		options->scheme.night.temperature = DEFAULT_NIGHT_TEMP;
	}

	if (isnan(options->scheme.day.brightness)) {
		options->scheme.day.brightness = DEFAULT_BRIGHTNESS;
	}
	if (isnan(options->scheme.night.brightness)) {
		options->scheme.night.brightness = DEFAULT_BRIGHTNESS;
	}

	if (isnan(options->scheme.day.gamma[0])) {
		options->scheme.day.gamma[0] = DEFAULT_GAMMA;
		options->scheme.day.gamma[1] = DEFAULT_GAMMA;
		options->scheme.day.gamma[2] = DEFAULT_GAMMA;
	}
	if (isnan(options->scheme.night.gamma[0])) {
		options->scheme.night.gamma[0] = DEFAULT_GAMMA;
		options->scheme.night.gamma[1] = DEFAULT_GAMMA;
		options->scheme.night.gamma[2] = DEFAULT_GAMMA;
	}

	if (options->use_fade < 0) options->use_fade = 1;
}