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
 char* APP_NAME ; 
 int DEFAULT_DELAY ; 
 int DEFAULT_REPEAT ; 
 int RC_SUCCESS ; 
 int RC_TIMEOUT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strlen (char*) ; 

__attribute__((used)) static void usage(void)
{
    fprintf(stderr, "%s - Utility to send clicks to Wine Windows.\n", APP_NAME);
    fprintf(stderr, "----------------------------------------------\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    %s action --winclass class --wintitle title [--timeout ms]\n",APP_NAME);
    fprintf(stderr, "    %*.*s     [--ctrlclas class] [--ctrlcaption caption] [--ctrlid id]\n", strlen(APP_NAME) + 3, strlen(APP_NAME) + 3, "");
    fprintf(stderr, "    %*.*s     [--position XxY] [--delay ms] [--untildeath] [--repeat ms]\n", strlen(APP_NAME) + 3, strlen(APP_NAME) + 3, "");
    fprintf(stderr, "Where action can be one of:\n");
    fprintf(stderr, "  find              Find the specified window or control\n");
    fprintf(stderr, "  button<n>         Send a click with the given X button number\n");
    fprintf(stderr, "  click|lclick      Synonym for button1 (left click)\n");
    fprintf(stderr, "  mclick            Synonym for button2 (middle click)\n");
    fprintf(stderr, "  rclick            Synonym for button3 (right click)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "The options are as follows:\n");
    fprintf(stderr, "  --timeout ms      How long to wait before failing with a code of %d\n", RC_TIMEOUT);
    fprintf(stderr, "  --winclass class  Class name of the top-level window of interest\n");
    fprintf(stderr, "  --wintitle title  Title of the top-level window of interest\n");
    fprintf(stderr, "  --ctrlclass name  Class name of the control of interest, if any\n");
    fprintf(stderr, "  --ctrlcaption cap A substring of the control's caption\n");
    fprintf(stderr, "  --ctrlid id       Id of the control\n");
    fprintf(stderr, "  --position XxY    Coordinates for the click, relative to the window / control\n");
    fprintf(stderr, "  --dragto          If given, then position specifies start click, and\n");
    fprintf(stderr, "                    dragto specifies release coords.\n");
    fprintf(stderr, "  --allow-disabled  Match the window or control even hidden or disabled\n");
    fprintf(stderr, "  --delay ms        Wait ms milliseconds before clicking. The default is %d\n", DEFAULT_DELAY);
    fprintf(stderr, "  --untildeath      Wait until the window disappears\n");
    fprintf(stderr, "  --repeat ms       Click every ms milliseconds. The default is %d\n", DEFAULT_REPEAT);
    fprintf(stderr, "\n");
    fprintf(stderr, "%s returns %d on success\n", APP_NAME, RC_SUCCESS);
    fprintf(stderr, "\n");
    fprintf(stderr, "Environment variable overrides:\n");
    fprintf(stderr, "  CXTEST_TIME_MULTIPLE  Specifies a floating multiplier applied to any\n");
    fprintf(stderr, "                        delay and timeout parameters.\n");
}