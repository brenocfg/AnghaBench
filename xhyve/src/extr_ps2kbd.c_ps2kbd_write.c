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
typedef  int uint8_t ;
struct ps2kbd_softc {int curcmd; int enabled; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int const PS2KC_ACK ; 
 int const PS2KC_BAT_SUCCESS ; 
#define  PS2KC_DISABLE 135 
#define  PS2KC_ECHO 134 
#define  PS2KC_ENABLE 133 
#define  PS2KC_RESET_DEV 132 
#define  PS2KC_SEND_DEV_ID 131 
#define  PS2KC_SET_LEDS 130 
#define  PS2KC_SET_SCANCODE_SET 129 
#define  PS2KC_SET_TYPEMATIC 128 
 int /*<<< orphan*/  fifo_put (struct ps2kbd_softc*,int const) ; 
 int /*<<< orphan*/  fifo_reset (struct ps2kbd_softc*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void
ps2kbd_write(struct ps2kbd_softc *sc, uint8_t val)
{
	pthread_mutex_lock(&sc->mtx);
	if (sc->curcmd) {
		switch (sc->curcmd) {
		case PS2KC_SET_TYPEMATIC:
			fifo_put(sc, PS2KC_ACK);
			break;
		case PS2KC_SET_SCANCODE_SET:
			fifo_put(sc, PS2KC_ACK);
			break;
		case PS2KC_SET_LEDS:
			fifo_put(sc, PS2KC_ACK);
			break;
		default:
			fprintf(stderr, "Unhandled ps2 keyboard current "
			    "command byte 0x%02x\n", val);
			break;
		}
		sc->curcmd = 0;
	} else {
		switch (val) {
		case 0x00:
			fifo_put(sc, PS2KC_ACK);
			break;
		case PS2KC_RESET_DEV:
			fifo_reset(sc);
			fifo_put(sc, PS2KC_ACK);
			fifo_put(sc, PS2KC_BAT_SUCCESS);
			break;
		case PS2KC_DISABLE:
			sc->enabled = false;
			fifo_put(sc, PS2KC_ACK);
			break;
		case PS2KC_ENABLE:
			sc->enabled = true;
			fifo_reset(sc);
			fifo_put(sc, PS2KC_ACK);
			break;
		case PS2KC_SET_TYPEMATIC:
			sc->curcmd = val;
			fifo_put(sc, PS2KC_ACK);
			break;
		case PS2KC_SEND_DEV_ID:
			fifo_put(sc, PS2KC_ACK);
			fifo_put(sc, 0xab);
			fifo_put(sc, 0x83);
			break;
		case PS2KC_SET_SCANCODE_SET:
			sc->curcmd = val;
			fifo_put(sc, PS2KC_ACK);
			break;
		case PS2KC_ECHO:
			fifo_put(sc, PS2KC_ECHO);
			break;
		case PS2KC_SET_LEDS:
			sc->curcmd = val;
			fifo_put(sc, PS2KC_ACK);
			break;
		default:
			fprintf(stderr, "Unhandled ps2 keyboard command "
			    "0x%02x\n", val);
			break;
		}
	}
	pthread_mutex_unlock(&sc->mtx);
}