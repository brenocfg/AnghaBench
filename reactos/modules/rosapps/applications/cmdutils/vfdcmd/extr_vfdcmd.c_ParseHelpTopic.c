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
struct TYPE_2__ {char const* keyword; } ;

/* Variables and functions */
 int CMD_MATCH_MULTI ; 
 int CMD_MATCH_NONE ; 
 TYPE_1__* HelpMsg ; 
 int /*<<< orphan*/  MSG_AMBIGUOUS_COMMAND ; 
 int /*<<< orphan*/  MSG_UNKNOWN_COMMAND ; 
 int /*<<< orphan*/  PrintMessage (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  _strnicmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t strlen (char const*) ; 

int ParseHelpTopic(const char *topic)
{
	size_t	len;
	int		idx;
	int		match;

	if (*topic == '\0') {

		//	empty command

		return CMD_MATCH_NONE;
	}

	//	find a match
	len = strlen(topic);
	idx = 0;
	match = CMD_MATCH_NONE;

	while (HelpMsg[idx].keyword) {

		if (strlen(HelpMsg[idx].keyword) >= len &&
			!_strnicmp(topic, HelpMsg[idx].keyword, len)) {

			if (match == CMD_MATCH_NONE) {		//	first match
				match = idx;
			}
			else {								//	multiple matches
				if (match != CMD_MATCH_MULTI) {	//	first time
					PrintMessage(MSG_AMBIGUOUS_COMMAND, topic);
					printf("> %s ", HelpMsg[match].keyword);
					match = CMD_MATCH_MULTI;
				}

				printf("%s ", HelpMsg[idx].keyword);
			}
		}

		idx++;
	}

	if (match == CMD_MATCH_NONE) {				//	match not found
		PrintMessage(MSG_UNKNOWN_COMMAND, topic);
	}
	else if (match == CMD_MATCH_MULTI) {		//	multiple matches
		printf("\n");
	}

	return match;
}