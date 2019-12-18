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
 int /*<<< orphan*/  CharactersToWrite ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  Message ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ StandardOutput ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WriteConsole (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WrittenCharacters ; 
 int /*<<< orphan*/  d ; 
 int h ; 
 int m ; 
 int s ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int) ; 

int
main (int argc, char * argv [])
{
	StandardOutput = GetStdHandle (STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == StandardOutput)
	{
		return (EXIT_FAILURE);
	}
	while (TRUE)
	{
		/* Prepare the message and update it */
		CharactersToWrite =
			wsprintf (
				Message,
				"Alive for %dd %dh %d' %d\"   \r",
				d, h, m, s
				);
		WriteConsole (
			StandardOutput,
			Message,
			CharactersToWrite,
			& WrittenCharacters,
			NULL
			);
		/* suspend the execution for 1s */
		Sleep (1000);
		/* increment seconds */
		++ s;
		if (60 == s) { s = 0; ++ m; }
		if (60 == m) { m = 0; ++ h; }
		if (24 == h) { h = 0; ++ d; }
	}
	return (EXIT_SUCCESS);
}