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
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  OPEN_KEY (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_KEY (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void install_app(char *argv0)
{
	char buf[512];
	HKEY software, classes, mupdf, dotpdf, dotxps, dotepub, dotfb2;
	HKEY shell, open, command, supported_types;
	HKEY pdf_progids, xps_progids, epub_progids, fb2_progids;

	OPEN_KEY(HKEY_CURRENT_USER, "Software", software);
	OPEN_KEY(software, "Classes", classes);
	OPEN_KEY(classes, ".pdf", dotpdf);
	OPEN_KEY(dotpdf, "OpenWithProgids", pdf_progids);
	OPEN_KEY(classes, ".xps", dotxps);
	OPEN_KEY(dotxps, "OpenWithProgids", xps_progids);
	OPEN_KEY(classes, ".epub", dotepub);
	OPEN_KEY(dotepub, "OpenWithProgids", epub_progids);
	OPEN_KEY(classes, ".fb2", dotfb2);
	OPEN_KEY(dotfb2, "OpenWithProgids", fb2_progids);
	OPEN_KEY(classes, "MuPDF", mupdf);
	OPEN_KEY(mupdf, "SupportedTypes", supported_types);
	OPEN_KEY(mupdf, "shell", shell);
	OPEN_KEY(shell, "open", open);
	OPEN_KEY(open, "command", command);

	sprintf(buf, "\"%s\" \"%%1\"", argv0);

	SET_KEY(open, "FriendlyAppName", "MuPDF");
	SET_KEY(command, "", buf);
	SET_KEY(supported_types, ".pdf", "");
	SET_KEY(supported_types, ".xps", "");
	SET_KEY(supported_types, ".epub", "");
	SET_KEY(pdf_progids, "MuPDF", "");
	SET_KEY(xps_progids, "MuPDF", "");
	SET_KEY(epub_progids, "MuPDF", "");
	SET_KEY(fb2_progids, "MuPDF", "");

	RegCloseKey(dotfb2);
	RegCloseKey(dotepub);
	RegCloseKey(dotxps);
	RegCloseKey(dotpdf);
	RegCloseKey(mupdf);
	RegCloseKey(classes);
	RegCloseKey(software);
}