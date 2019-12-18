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
struct TYPE_3__ {int /*<<< orphan*/ * saved_ramps; } ;
typedef  TYPE_1__ w32gdi_state_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CM_GAMMA_RAMP ; 
 int /*<<< orphan*/  COLORMGMTCAPS ; 
 int GAMMA_RAMP_SIZE ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 int GetDeviceCaps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDeviceGammaRamp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
w32gdi_start(w32gdi_state_t *state)
{
	BOOL r;

	/* Open device context */
	HDC hDC = GetDC(NULL);
	if (hDC == NULL) {
		fputs(_("Unable to open device context.\n"), stderr);
		return -1;
	}

	/* Check support for gamma ramps */
	int cmcap = GetDeviceCaps(hDC, COLORMGMTCAPS);
	if (cmcap != CM_GAMMA_RAMP) {
		fputs(_("Display device does not support gamma ramps.\n"),
		      stderr);
		return -1;
	}

	/* Allocate space for saved gamma ramps */
	state->saved_ramps = malloc(3*GAMMA_RAMP_SIZE*sizeof(WORD));
	if (state->saved_ramps == NULL) {
		perror("malloc");
		ReleaseDC(NULL, hDC);
		return -1;
	}

	/* Save current gamma ramps so we can restore them at program exit */
	r = GetDeviceGammaRamp(hDC, state->saved_ramps);
	if (!r) {
		fputs(_("Unable to save current gamma ramp.\n"), stderr);
		ReleaseDC(NULL, hDC);
		return -1;
	}

	/* Release device context */
	ReleaseDC(NULL, hDC);

	return 0;
}