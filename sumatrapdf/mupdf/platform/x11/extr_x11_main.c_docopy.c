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
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  XSetSelectionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* copylatin1 ; 
 int /*<<< orphan*/  copytime ; 
 char* copyutf8 ; 
 int /*<<< orphan*/  fz_runetochar (char*,int) ; 
 int /*<<< orphan*/  gapp ; 
 int justcopied ; 
 int /*<<< orphan*/  pdfapp_oncopy (int /*<<< orphan*/ *,unsigned short*,int) ; 
 int /*<<< orphan*/  xdpy ; 
 int /*<<< orphan*/  xwin ; 

__attribute__((used)) static void docopy(pdfapp_t *app, Atom copy_target)
{
	unsigned short copyucs2[16 * 1024];
	char *latin1 = copylatin1;
	char *utf8 = copyutf8;
	unsigned short *ucs2;
	int ucs;

	pdfapp_oncopy(&gapp, copyucs2, 16 * 1024);

	for (ucs2 = copyucs2; ucs2[0] != 0; ucs2++)
	{
		ucs = ucs2[0];

		utf8 += fz_runetochar(utf8, ucs);

		if (ucs < 256)
			*latin1++ = ucs;
		else
			*latin1++ = '?';
	}

	*utf8 = 0;
	*latin1 = 0;

	XSetSelectionOwner(xdpy, copy_target, xwin, copytime);

	justcopied = 1;
}