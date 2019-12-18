#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int temperature; void* brightness; void** gamma; } ;
struct TYPE_10__ {int temperature; void* brightness; void** gamma; } ;
struct TYPE_9__ {int start; int end; } ;
struct TYPE_8__ {int start; int end; } ;
struct TYPE_12__ {TYPE_4__ night; TYPE_3__ day; TYPE_2__ dusk; TYPE_1__ dawn; scalar_t__ use_time; int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_13__ {int temp_set; int use_fade; int preserve_gamma; scalar_t__ verbose; int /*<<< orphan*/  mode; int /*<<< orphan*/ * provider_args; int /*<<< orphan*/ * provider; int /*<<< orphan*/ * method_args; int /*<<< orphan*/ * method; TYPE_5__ scheme; int /*<<< orphan*/ * config_filepath; } ;
typedef  TYPE_6__ options_t ;

/* Variables and functions */
 void* NAN ; 
 int /*<<< orphan*/  PROGRAM_MODE_CONTINUAL ; 
 int /*<<< orphan*/  TRANSITION_HIGH ; 
 int /*<<< orphan*/  TRANSITION_LOW ; 

void
options_init(options_t *options)
{
	options->config_filepath = NULL;

	/* Default elevation values. */
	options->scheme.high = TRANSITION_HIGH;
	options->scheme.low = TRANSITION_LOW;

	/* Settings for day, night and transition period.
	   Initialized to indicate that the values are not set yet. */
	options->scheme.use_time = 0;
	options->scheme.dawn.start = -1;
	options->scheme.dawn.end = -1;
	options->scheme.dusk.start = -1;
	options->scheme.dusk.end = -1;

	options->scheme.day.temperature = -1;
	options->scheme.day.gamma[0] = NAN;
	options->scheme.day.brightness = NAN;

	options->scheme.night.temperature = -1;
	options->scheme.night.gamma[0] = NAN;
	options->scheme.night.brightness = NAN;

	/* Temperature for manual mode */
	options->temp_set = -1;

	options->method = NULL;
	options->method_args = NULL;

	options->provider = NULL;
	options->provider_args = NULL;

	options->use_fade = -1;
	options->preserve_gamma = 1;
	options->mode = PROGRAM_MODE_CONTINUAL;
	options->verbose = 0;
}