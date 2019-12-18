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
struct TYPE_3__ {int /*<<< orphan*/  saved_ramps; } ;
typedef  TYPE_1__ w32gdi_state_t ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 int MAX_ATTEMPTS ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetDeviceGammaRamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
w32gdi_restore(w32gdi_state_t *state)
{
	/* Open device context */
	HDC hDC = GetDC(NULL);
	if (hDC == NULL) {
		fputs(_("Unable to open device context.\n"), stderr);
		return;
	}

	/* Restore gamma ramps */
	BOOL r = FALSE;
	for (int i = 0; i < MAX_ATTEMPTS && !r; i++) {
		/* We retry a few times before giving up because some
		   buggy drivers fail on the first invocation of
		   SetDeviceGammaRamp just to succeed on the second. */
		r = SetDeviceGammaRamp(hDC, state->saved_ramps);
	}
	if (!r) fputs(_("Unable to restore gamma ramps.\n"), stderr);

	/* Release device context */
	ReleaseDC(NULL, hDC);
}