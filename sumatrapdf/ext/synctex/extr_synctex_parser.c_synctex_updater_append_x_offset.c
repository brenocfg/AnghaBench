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
typedef  TYPE_1__* synctex_updater_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNCTEX_FILE ; 
 scalar_t__ SYNCTEX_fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void synctex_updater_append_x_offset(synctex_updater_t updater, char * x_offset){
	if (NULL==updater) {
		return;
	}
	if (x_offset && strlen(x_offset)) {
		updater->length += SYNCTEX_fprintf(SYNCTEX_FILE,"X Offset:%s\n",x_offset);
	}
}