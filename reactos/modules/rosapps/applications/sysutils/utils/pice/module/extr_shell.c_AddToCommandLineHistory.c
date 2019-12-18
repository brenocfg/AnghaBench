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
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 size_t LINES_IN_COMMAND_BUFFER ; 
 scalar_t__ PICE_strcmpi (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PICE_strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PICE_strlen (int /*<<< orphan*/ ) ; 
 char** aszCommandLines ; 
 size_t ulCommandCurrentPos ; 
 size_t ulCommandInPos ; 
 size_t ulCommandLastPos ; 

void AddToCommandLineHistory(LPSTR s)
{
    ULONG i;

    ENTER_FUNC();
    DPRINT((0,"AddToCommandLineHistory(%s)\n",s));

    if(PICE_strlen(s))
    {
        for(i=0;i<LINES_IN_COMMAND_BUFFER;i++)
        {
            if(PICE_strcmpi(&aszCommandLines[i][1],s) == 0)
            {
                DPRINT((0,"AddToCommandLineHistory(): command line already exists\n"));
                LEAVE_FUNC();
                return;
            }
        }
        aszCommandLines[ulCommandInPos][0]=':';
        PICE_strcpy(&aszCommandLines[ulCommandInPos][1],s);
        ulCommandCurrentPos = ulCommandInPos = (ulCommandInPos +1)%LINES_IN_COMMAND_BUFFER;
        if(ulCommandInPos == ulCommandLastPos)
        {
            ulCommandLastPos = (ulCommandLastPos+1)%LINES_IN_COMMAND_BUFFER;
        }
    }

    LEAVE_FUNC();
}