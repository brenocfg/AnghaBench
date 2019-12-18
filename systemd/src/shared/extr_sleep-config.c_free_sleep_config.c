#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hybrid_states; int /*<<< orphan*/  hybrid_modes; int /*<<< orphan*/  hibernate_states; int /*<<< orphan*/  hibernate_modes; int /*<<< orphan*/  suspend_states; int /*<<< orphan*/  suspend_modes; } ;
typedef  TYPE_1__ SleepConfig ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

void free_sleep_config(SleepConfig *sc) {
        if (!sc)
                return;

        strv_free(sc->suspend_modes);
        strv_free(sc->suspend_states);

        strv_free(sc->hibernate_modes);
        strv_free(sc->hibernate_states);

        strv_free(sc->hybrid_modes);
        strv_free(sc->hybrid_states);

        free(sc);
}