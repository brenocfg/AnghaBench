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
struct atkbdc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atkbdc_kbd_read (struct atkbdc_softc*) ; 

__attribute__((used)) static void
atkbdc_kbd_poll(struct atkbdc_softc *sc)
{
	atkbdc_kbd_read(sc);
}