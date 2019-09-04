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
typedef  int /*<<< orphan*/  input ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertPathCase (char*,char*) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  GetCurrentDirectory (int,char*) ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSG_CONSOLE_HINT ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessCommandLine (int,char const**) ; 
 int /*<<< orphan*/  SetConsoleCtrlHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetConsoleTitle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCurrentDirectory (char*) ; 
 char* SystemError (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int VFD_OK ; 
 int /*<<< orphan*/  VFD_PRODUCT_DESC ; 
 int /*<<< orphan*/  Version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (char**,int) ; 
 scalar_t__ _stricmp (char*,char*) ; 
 int /*<<< orphan*/  _strnicmp (char*,char*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 char* help_progname ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 scalar_t__ toupper (char) ; 

int InteractiveConsole()
{
	char		input[1024];	//	user input buffer

	int			argc;			//	number of args in the user input
	char		*args[10];		//	args to pass to command functions

	char		sepa;			//	argument separator
	char		*p;				//	work pointer

	//	Disable the system default Ctrl+C handler

	SetConsoleCtrlHandler(NULL, TRUE);

	//	Set the console title

	SetConsoleTitle(VFD_PRODUCT_DESC);

	//	print version information and the console hint text

	Version(NULL);

	PrintMessage(MSG_CONSOLE_HINT);

	//	set interactive flag to exclude "VFD.EXE" from help text

	help_progname = "";

	//	process user input

	for (;;) {

		//	print the prompt

		printf("[VFD] ");
		fflush(stdout);

		//	read user input

		fflush(stdin);
		p = fgets(input, sizeof(input), stdin);

		if (p == NULL) {

			//	most likely <ctrl+c>

			printf("exit\n");
			break;
		}

		//	skip leading blank characters

		while (*p == ' ' || *p == '\t' || *p == '\n') {
			p++;
		}
		
		if (*p == '\0') {

			//	empty input

			continue;
		}

		//	handle external commands

		if (!_strnicmp(p, "dir", 3) ||
			!_strnicmp(p, "attrib", 6)) {

			//	special cases - frequently used commands
			//	pass these to system() even without '.'

			system(p);
			printf("\n");
			continue;
		}
		else if (*p == '.') {

			//	external command

			system(p + 1);
			printf("\n");
			continue;
		}

		//	split the input line into parameters (10 parameters max)

		argc = 0;
		ZeroMemory(args, sizeof(args));

		do {
			//	top of a parameter

			args[argc++] = p;

			//	is the parameter quoted?

			if (*p == '\"' || *p == '\'') {
				sepa = *(p++);
			}
			else {
				sepa = ' ';
			}

			//	search the end of the parameter

			while (*p && *p != '\n') {
				if (sepa == ' ') {
					if (*p == '\t' || *p == ' ') {
						break;			//	tail of a non-quoted parameter
					}
				}
				else {
					if (*p == sepa) {
						sepa = ' ';		//	close quote
					}
				}
				p++;
			}

			//	terminate the parameter

			if (*p) {
				*(p++) = '\0';
			}

			//	skip trailing blank characters

			while (*p == ' ' || *p == '\t' || *p == '\n') {
				p++;
			}

			if (*p == '\0') {

				//	end of the input line - no more args

				break;
			}
		}
		while (argc < sizeof(args) / sizeof(args[0]));

		//	check the first parameter for special commands

		if (!_stricmp(args[0], "exit") ||
			!_stricmp(args[0], "quit") ||
			!_stricmp(args[0], "bye")) {

			//	exit command

			break;
		}
		else if (!_stricmp(args[0], "cd") ||
			!_stricmp(args[0], "chdir")) {

			//	internal change directory command

			if (args[1]) {
				char path[MAX_PATH];
				int i;

				//	ignore the /d option (of the standard cd command)

				if (_stricmp(args[1], "/d")) {
					i = 1;
				}
				else {
					i = 2;
				}

				p = args[i];

				if (*p == '\"' || *p == '\'') {

					//	the parameter is quoted -- remove quotations

					p++;

					while (*p && *p != *args[i]) {
						p++;
					}

					args[i]++;		// skip a leading quote
					*p = '\0';		// remove a trailing quote
				}
				else {

					//	the parameter is not quoted
					//	-- concatenate params to allow spaces in unquoted path

					while (i < argc - 1) {
						*(args[i] + strlen(args[i])) = ' ';
						i++;
					}
				}

				//	Match the case of the path to the name on the disk
				
				ConvertPathCase(p, path);

				if (!SetCurrentDirectory(path)) {
					DWORD ret = GetLastError();

					if (ret == ERROR_FILE_NOT_FOUND) {
						ret = ERROR_PATH_NOT_FOUND;
					}

					printf("%s", SystemError(ret));
				}
			}
			else {
				if (!GetCurrentDirectory(sizeof(input), input)) {
					printf("%s", SystemError(GetLastError()));
				}
				else {
					printf("%s\n", input);
				}
			}
		}
		else if (isalpha(*args[0]) &&
			*(args[0] + 1) == ':' &&
			*(args[0] + 2) == '\0') {

			//	internal change drive command

			*args[0] = (char)toupper(*args[0]);
			*(args[0] + 2) = '\\';
			*(args[0] + 3) = '\0';

			if (!SetCurrentDirectory(args[0])) {
				printf("%s", SystemError(GetLastError()));
			}
		}
		else {

			//	perform the requested VFD command

			ProcessCommandLine(argc, (const char **)args);
		}

		printf("\n");
	}
	
	return VFD_OK;
}