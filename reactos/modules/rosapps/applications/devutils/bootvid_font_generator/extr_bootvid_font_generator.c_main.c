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
 int /*<<< orphan*/  DumpFont (char*,int,int,int) ; 
 char* FONT_NAME_DEF ; 
 int FONT_SIZE_DEF ; 
 int X_OFFSET_DEF ; 
 int Y_OFFSET_DEF ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int main(int argc, char** argv)
{
    /* Validate the arguments */
    if (argc > 5 || (argc >= 2 && strncmp(argv[1], "/?", 2) == 0))
    {
        fprintf(stdout,
                "Usage: %s \"font name\" [font size] [X-offset] [Y-offset]\n"
                "Default font name is: \"%s\"\n"
                "Default font size is: %i\n"
                "Default X-offset  is: %i\n"
                "Default Y-offset  is: %i\n",
                argv[0],
                FONT_NAME_DEF, FONT_SIZE_DEF, X_OFFSET_DEF, Y_OFFSET_DEF);

        return -1;
    }

    DumpFont((argc <= 1) ? FONT_NAME_DEF : argv[1],
             (argc <= 2) ? FONT_SIZE_DEF : atoi(argv[2]),
             (argc <= 3) ?  X_OFFSET_DEF : atoi(argv[3]),
             (argc <= 4) ?  Y_OFFSET_DEF : atoi(argv[4]));
    return 0;
}