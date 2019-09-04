#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  input ;
typedef  int WORD ;
struct TYPE_21__ {short X; } ;
struct TYPE_15__ {int X; } ;
struct TYPE_14__ {int Bottom; int Top; } ;
struct TYPE_20__ {int wAttributes; TYPE_8__ dwCursorPosition; TYPE_2__ dwSize; TYPE_1__ srWindow; } ;
struct TYPE_16__ {scalar_t__ AsciiChar; } ;
struct TYPE_17__ {TYPE_3__ uChar; int /*<<< orphan*/  bKeyDown; } ;
struct TYPE_18__ {TYPE_4__ KeyEvent; } ;
struct TYPE_19__ {scalar_t__ EventType; TYPE_5__ Event; } ;
typedef  TYPE_6__ INPUT_RECORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  TYPE_7__ CONSOLE_SCREEN_BUFFER_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int COMMON_LVB_REVERSE_VIDEO ; 
 int ENABLE_PROCESSED_INPUT ; 
 scalar_t__ FALSE ; 
 int FORMAT_MESSAGE_FROM_HMODULE ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FillConsoleOutputAttribute (int /*<<< orphan*/ ,int,int,TYPE_8__,int*) ; 
 int /*<<< orphan*/  FillConsoleOutputCharacter (int /*<<< orphan*/ ,char,int,TYPE_8__,int*) ; 
 int /*<<< orphan*/  FlushConsoleInputBuffer (int /*<<< orphan*/ ) ; 
 int FormatMessage (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_EVENT ; 
 int /*<<< orphan*/  MSG_PAGER_PROMPT ; 
 int /*<<< orphan*/  ReadConsoleInput (int /*<<< orphan*/ ,TYPE_6__*,int,int*) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetConsoleCursorPosition (int /*<<< orphan*/ ,TYPE_8__) ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ VK_CANCEL ; 
 scalar_t__ VK_ESCAPE ; 
 int /*<<< orphan*/  WriteConsoleOutputCharacter (int /*<<< orphan*/ ,char*,int,TYPE_8__,int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char tolower (scalar_t__) ; 

BOOL ConsolePager(char *pBuffer, BOOL bReset)
{
	static int	rows = 0;
	char		prompt[80];
	int			prompt_len = 0;
	HANDLE		hStdOut;
	HANDLE		hStdIn;

	//
	//	prepare the console input and output handles
	//
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdIn	= GetStdHandle(STD_INPUT_HANDLE);

	for (;;) {
		CONSOLE_SCREEN_BUFFER_INFO	info;
		INPUT_RECORD	input;
		DWORD			result;
		DWORD			mode;
		int				cols;
		char			*cur;
		char			save;

		//
		//	Get the current console screen information
		//
		GetConsoleScreenBufferInfo(hStdOut, &info);

		if (bReset || rows <= 0) {
			rows = info.srWindow.Bottom - info.srWindow.Top - 1;
		}

		cols = info.dwSize.X;

		//	console window is too small for paging

		if (rows <= 0) {
			//	print all text and exit
			printf("%s", pBuffer);
			break;
		}

		//
		//	find the tail of the text to be printed this time
		//
		cur = pBuffer;
		save = '\0';

		while (*cur) {
			if (*(cur++) == '\n' || (cols--) == 0) {
				//	reached the end of a line
				if (--rows == 0) {
					//	reached the end of a page
					//	insert a terminating NULL char
					save = *cur;
					*cur = '\0';
					break;
				}

				cols = info.dwSize.X;
			}
		}

		//	print the current page
		printf("%s", pBuffer);

		//	end of the whole text?
		if (save == '\0') {
			break;
		}

		//
		//	prompt for the next page
		//

		//	prepare the prompt text

		if (prompt_len == 0) {

			prompt_len = FormatMessage(
				FORMAT_MESSAGE_FROM_HMODULE |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, MSG_PAGER_PROMPT, 0,
				prompt, sizeof(prompt), NULL);

			if (prompt_len == 0) {
				strcpy(prompt, "Press any key to continue...");
				prompt_len = strlen(prompt);
			}
		}

		//	get the current console input mode

		GetConsoleMode(hStdIn, &mode);

		//	change the mode to receive Ctrl+C as a regular input

		SetConsoleMode(hStdIn, (mode & ~ENABLE_PROCESSED_INPUT));

		//	get the current cursor position

		GetConsoleScreenBufferInfo(hStdOut, &info);

		//	print the prompt text

		WriteConsoleOutputCharacter(hStdOut, prompt,
			prompt_len, info.dwCursorPosition, &result);

		//	reverse the text color

		FillConsoleOutputAttribute(hStdOut, 
			(WORD)(info.wAttributes | COMMON_LVB_REVERSE_VIDEO),
			prompt_len, info.dwCursorPosition, &result);

		//	move cursor to the end of the prompt text

		info.dwCursorPosition.X =
			(short)(info.dwCursorPosition.X + prompt_len);

		SetConsoleCursorPosition(hStdOut, info.dwCursorPosition);

		//	wait for a key press event

		FlushConsoleInputBuffer(hStdIn);

		do {
			ReadConsoleInput(hStdIn, &input, sizeof(input), &result);
		}
		while (input.EventType != KEY_EVENT ||
			!input.Event.KeyEvent.bKeyDown ||
			!input.Event.KeyEvent.uChar.AsciiChar);

		//	restore the original cursor position

		info.dwCursorPosition.X =
			(short)(info.dwCursorPosition.X - prompt_len);

		SetConsoleCursorPosition(hStdOut, info.dwCursorPosition);

		//	delete the prompt text

		FillConsoleOutputCharacter(hStdOut, ' ',
			prompt_len, info.dwCursorPosition, &result);

		//	restore the text attribute to norml

		FillConsoleOutputAttribute(hStdOut, info.wAttributes,
			prompt_len, info.dwCursorPosition, &result);

		//	restore the original console mode

		SetConsoleMode(hStdIn, mode);

		//	check if the input was 'q', <esc> or <Ctrl+C> ?

		if (input.Event.KeyEvent.uChar.AsciiChar == VK_CANCEL ||
			input.Event.KeyEvent.uChar.AsciiChar == VK_ESCAPE ||
			tolower(input.Event.KeyEvent.uChar.AsciiChar) == 'q') {

			//	cancelled by the user
			return FALSE;
		}

		//
		//	process the next page
		//
		*cur = save;
		pBuffer = cur;
	}

	return TRUE;
}