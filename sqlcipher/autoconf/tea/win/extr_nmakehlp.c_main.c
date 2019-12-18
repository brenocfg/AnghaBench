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
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int CheckForCompilerFeature (char*) ; 
 int CheckForLinkerFeature (char*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 char* GetVersionFromFile (char*,char*) ; 
 int IsIn (char*,char*) ; 
 int QualifyPath (char*) ; 
 int SEM_FAILCRITICALERRORS ; 
 int SEM_NOOPENFILEERRORBOX ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  SetEnvironmentVariable (char*,char*) ; 
 int /*<<< orphan*/  SetErrorMode (int) ; 
 int SubstituteFile (char*,char*) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int snprintf (char*,int,char*,char*) ; 

int
main(
    int argc,
    char *argv[])
{
    char msg[300];
    DWORD dwWritten;
    int chars;

    /*
     * Make sure children (cl.exe and link.exe) are kept quiet.
     */

    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);

    /*
     * Make sure the compiler and linker aren't effected by the outside world.
     */

    SetEnvironmentVariable("CL", "");
    SetEnvironmentVariable("LINK", "");

    if (argc > 1 && *argv[1] == '-') {
	switch (*(argv[1]+1)) {
	case 'c':
	    if (argc != 3) {
		chars = snprintf(msg, sizeof(msg) - 1,
		        "usage: %s -c <compiler option>\n"
			"Tests for whether cl.exe supports an option\n"
			"exitcodes: 0 == no, 1 == yes, 2 == error\n", argv[0]);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, chars,
			&dwWritten, NULL);
		return 2;
	    }
	    return CheckForCompilerFeature(argv[2]);
	case 'l':
	    if (argc != 3) {
		chars = snprintf(msg, sizeof(msg) - 1,
	       		"usage: %s -l <linker option>\n"
			"Tests for whether link.exe supports an option\n"
			"exitcodes: 0 == no, 1 == yes, 2 == error\n", argv[0]);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, chars,
			&dwWritten, NULL);
		return 2;
	    }
	    return CheckForLinkerFeature(argv[2]);
	case 'f':
	    if (argc == 2) {
		chars = snprintf(msg, sizeof(msg) - 1,
			"usage: %s -f <string> <substring>\n"
			"Find a substring within another\n"
			"exitcodes: 0 == no, 1 == yes, 2 == error\n", argv[0]);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, chars,
			&dwWritten, NULL);
		return 2;
	    } else if (argc == 3) {
		/*
		 * If the string is blank, there is no match.
		 */

		return 0;
	    } else {
		return IsIn(argv[2], argv[3]);
	    }
	case 's':
	    if (argc == 2) {
		chars = snprintf(msg, sizeof(msg) - 1,
			"usage: %s -s <substitutions file> <file>\n"
			"Perform a set of string map type substutitions on a file\n"
			"exitcodes: 0\n",
			argv[0]);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, chars,
			&dwWritten, NULL);
		return 2;
	    }
	    return SubstituteFile(argv[2], argv[3]);
	case 'V':
	    if (argc != 4) {
		chars = snprintf(msg, sizeof(msg) - 1,
		    "usage: %s -V filename matchstring\n"
		    "Extract a version from a file:\n"
		    "eg: pkgIndex.tcl \"package ifneeded http\"",
		    argv[0]);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, chars,
		    &dwWritten, NULL);
		return 0;
	    }
	    printf("%s\n", GetVersionFromFile(argv[2], argv[3]));
	    return 0;
	case 'Q':
	    if (argc != 3) {
		chars = snprintf(msg, sizeof(msg) - 1,
		    "usage: %s -Q path\n"
		    "Emit the fully qualified path\n"
		    "exitcodes: 0 == no, 1 == yes, 2 == error\n", argv[0]);
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, chars,
		    &dwWritten, NULL);
		return 2;
	    }
	    return QualifyPath(argv[2]);
	}
    }
    chars = snprintf(msg, sizeof(msg) - 1,
	    "usage: %s -c|-f|-l|-Q|-s|-V ...\n"
	    "This is a little helper app to equalize shell differences between WinNT and\n"
	    "Win9x and get nmake.exe to accomplish its job.\n",
	    argv[0]);
    WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, chars, &dwWritten, NULL);
    return 2;
}