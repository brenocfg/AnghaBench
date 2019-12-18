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
typedef  int /*<<< orphan*/  pdfapp_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_ICONWARNING ; 
 int /*<<< orphan*/  MessageBoxA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwndframe ; 

void winprint(pdfapp_t *app)
{
	MessageBoxA(hwndframe, "The MuPDF library supports printing, but this application currently does not", "Print document", MB_ICONWARNING);
}