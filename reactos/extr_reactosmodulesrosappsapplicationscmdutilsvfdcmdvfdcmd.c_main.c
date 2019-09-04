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

/* Variables and functions */
 int InteractiveConsole () ; 
 int /*<<< orphan*/  MSG_WRONG_PLATFORM ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ) ; 
 int ProcessCommandLine (int,char const**) ; 
 int VFD_NG ; 
 int /*<<< orphan*/  VfdIsValidPlatform () ; 
 int _CRTDBG_LEAK_CHECK_DF ; 
 int _CRTDBG_REPORT_FLAG ; 
 int _CrtSetDbgFlag (int) ; 

int main(int argc, const char **argv)
{
#ifdef _DEBUG

	//	output vfd.exe command reference text

	if (*(argv + 1) && !_stricmp(*(argv + 1), "doc")) {
		int idx = 0;
		char *buf = "";

		printf("\r\n  VFD.EXE Command Reference\r\n");

		while (HelpMsg[idx].keyword) {
			int len = strlen(HelpMsg[idx].keyword);

			printf(
				"\r\n\r\n"
				"====================\r\n"
				"%*s\r\n"
				"====================\r\n"
				"\r\n",
				(20 + len) / 2, HelpMsg[idx].keyword);

			FormatMessage(
				FORMAT_MESSAGE_FROM_HMODULE |
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_ARGUMENT_ARRAY,
				NULL, HelpMsg[idx].help, 0,
				(LPTSTR)&buf, 0, (va_list *)&help_progname);
			
			printf("%s", buf);

			LocalFree(buf);

			idx++;
		}

		return 0;
	}
#endif

	//	Reports memory leaks at process termination

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	//	Check the operating system version

	if (!VfdIsValidPlatform()) {
		PrintMessage(MSG_WRONG_PLATFORM);
		return VFD_NG;
	}

	if (argc < 2) {
		//	If no parameter is given, enter the interactive mode

		return InteractiveConsole();
	}
	else {
		//	Perform a single operation

		return ProcessCommandLine(argc - 1, argv + 1);
	}
}