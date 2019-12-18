#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_2__ {int default_cp; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int GetOEMCP () ; 
 int MAX_PATH ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 char* cp_to_hr (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fd_get_ega (int) ; 
 int fd_get_kbdrv (char const*) ; 
 int fd_upgrade_cp (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* get_kb () ; 
 char* kb_to_hr (char const*) ; 
 TYPE_1__* kbdrv_data ; 
 char* ms_get_ega (int) ; 
 int ms_get_kbdrv (char const*) ; 
 int /*<<< orphan*/  static_strcat (char*,char*) ; 
 int /*<<< orphan*/  static_strcpy (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

BOOL SetDOSLocale(const char* path, BOOL bFreeDOS)
{
	FILE* fd;
	char filename[MAX_PATH];
	ULONG cp;
	const char *kb;
	int kbdrv;
	const char* egadrv;

	// First handle the codepage
	kb = get_kb();
	// We have a keyboard ID, but that doesn't mean it's supported
	kbdrv = bFreeDOS?fd_get_kbdrv(kb):ms_get_kbdrv(kb);
	if (kbdrv < 0) {
		uprintf("Keyboard id '%s' is not supported - falling back to 'us'\n", kb);
		kb = "us";
		kbdrv = bFreeDOS?fd_get_kbdrv(kb):ms_get_kbdrv(kb);	// Always succeeds
	}
	uprintf("Will use DOS keyboard '%s' [%s]\n", kb, kb_to_hr(kb));

	// Now get a codepage
	cp = GetOEMCP();
	egadrv = bFreeDOS?fd_get_ega(cp):ms_get_ega(cp);
	if (egadrv == NULL) {
		// We need to use the fallback CP from the keyboard we got above, as 437 is not always available
		uprintf("Unable to find an EGA file with codepage %d [%s]\n", cp, cp_to_hr(cp));
		cp = kbdrv_data[kbdrv].default_cp;
		egadrv =  bFreeDOS?"ega.cpx":"ega.cpi";
	} else if (bFreeDOS) {
		cp = fd_upgrade_cp(cp);
	}
	uprintf("Will use codepage %d [%s]\n", cp, cp_to_hr(cp));

	if ((cp == 437) && (strcmp(kb, "us") == 0)) {
		// Nothing much to do if US/US - just notify in autoexec.bat
		static_strcpy(filename, path);
		static_strcat(filename, "\\AUTOEXEC.BAT");
		fd = fopen(filename, "w+");
		if (fd == NULL) {
			uprintf("Unable to create 'AUTOEXEC.BAT': %s.\n", WindowsErrorString());
			return FALSE;
		}
		fprintf(fd, "@echo off\n");
		fprintf(fd, "set PATH=.;\\;\\LOCALE\n");
		fprintf(fd, "echo Using %s keyboard with %s codepage [%d]\n", kb_to_hr("us"), cp_to_hr(437), 437);
		fclose(fd);
		uprintf("Successfully wrote 'AUTOEXEC.BAT'\n");
		return TRUE;
	}

	// CONFIG.SYS
	static_strcpy(filename, path);
	static_strcat(filename, "\\CONFIG.SYS");
	fd = fopen(filename, "w+");
	if (fd == NULL) {
		uprintf("Unable to create 'CONFIG.SYS': %s.\n", WindowsErrorString());
		return FALSE;
	}
	if (bFreeDOS) {
		fprintf(fd, "!MENUCOLOR=7,0\nMENU\nMENU   FreeDOS Language Selection Menu\n");
		fprintf(fd, "MENU   \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
			"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\nMENU\n");
	} else {
		fprintf(fd, "[MENU]\n");
	}
	fprintf(fd, "MENUDEFAULT=1,5\n");
	// Menu item max: 70 characters
	fprintf(fd, "%s1%c Use %s keyboard with %s codepage [%d]\n",
		bFreeDOS?"MENU ":"MENUITEM=", bFreeDOS?')':',', kb_to_hr(kb), cp_to_hr(cp), (int)cp);
	fprintf(fd, "%s2%c Use %s keyboard with %s codepage [%d]\n",
		bFreeDOS?"MENU ":"MENUITEM=", bFreeDOS?')':',', kb_to_hr("us"), cp_to_hr(437), 437);
	fprintf(fd, "%s", bFreeDOS?"MENU\n12?\n":"[1]\ndevice=\\locale\\display.sys con=(ega,,1)\n[2]\n");
	fclose(fd);
	uprintf("Successfully wrote 'CONFIG.SYS'\n");

	// AUTOEXEC.BAT
	static_strcpy(filename, path);
	static_strcat(filename, "\\AUTOEXEC.BAT");
	fd = fopen(filename, "w+");
	if (fd == NULL) {
		uprintf("Unable to create 'AUTOEXEC.BAT': %s.\n", WindowsErrorString());
		return FALSE;
	}
	fprintf(fd, "@echo off\n");
	fprintf(fd, "set PATH=.;\\;\\LOCALE\n");
	if (bFreeDOS)
		fprintf(fd, "display con=(ega,,1)\n");
	fprintf(fd, "GOTO %%CONFIG%%\n");
	fprintf(fd, ":1\n");
	fprintf(fd, "mode con codepage prepare=((%d) \\locale\\%s) > NUL\n", (int)cp, egadrv);
	fprintf(fd, "mode con codepage select=%d > NUL\n", (int)cp);
	fprintf(fd, "keyb %s,,\\locale\\%s\n", kb, kbdrv_data[kbdrv].name);
	fprintf(fd, ":2\n");
	fclose(fd);
	uprintf("Successfully wrote 'AUTOEXEC.BAT'\n");

	return TRUE;
}