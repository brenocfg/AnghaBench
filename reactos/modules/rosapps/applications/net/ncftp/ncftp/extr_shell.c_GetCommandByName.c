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
typedef  int /*<<< orphan*/  bsearch_proc_t ;
typedef  int /*<<< orphan*/ * CommandPtr ;
typedef  int /*<<< orphan*/  Command ;

/* Variables and functions */
 scalar_t__ CommandExactSearchCmp ; 
 scalar_t__ CommandSubSearchCmp (char const* const,int /*<<< orphan*/ *) ; 
 scalar_t__ bsearch (char const* const,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gCommands ; 
 int gNumCommands ; 
 int /*<<< orphan*/ * kAmbiguousCommand ; 
 int /*<<< orphan*/ * kNoCommand ; 

CommandPtr
GetCommandByName(const char *const name, int wantExactMatch)
{
	CommandPtr canp, canp2;

	/* First check for an exact match.  Otherwise if you if asked for
	 * 'cd', it would match both 'cd' and 'cdup' and return an
	 * ambiguous name error, despite having the exact name for 'cd.'
	 */
	canp = (CommandPtr) bsearch(name, gCommands, gNumCommands, sizeof(Command), (bsearch_proc_t) CommandExactSearchCmp);

	if (canp == kNoCommand && !wantExactMatch) {
		/* Now see if the user typed an abbreviation unique enough
		 * to match only one name in the list.
		 */
		canp = (CommandPtr) bsearch(name, gCommands, gNumCommands, sizeof(Command), (bsearch_proc_t) CommandSubSearchCmp);

		if (canp != kNoCommand) {
			/* Check the entry above us and see if the name we're looking
			 * for would match that, too.
			 */
			if (canp != &gCommands[0]) {
				canp2 = canp - 1;
				if (CommandSubSearchCmp(name, canp2) == 0)
					return kAmbiguousCommand;
			}
			/* Check the entry below us and see if the name we're looking
			 * for would match that one.
			 */
			if (canp != &gCommands[gNumCommands - 1]) {
				canp2 = canp + 1;
				if (CommandSubSearchCmp(name, canp2) == 0)
					return kAmbiguousCommand;
			}
		}
	}
	return canp;
}