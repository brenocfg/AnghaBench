#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_4__ {char* Cmd; scalar_t__ CommandGroup; int /*<<< orphan*/  Help; } ;
struct TYPE_3__ {scalar_t__ cy; scalar_t__ y; } ;
typedef  char* LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_CAPTION ; 
 int /*<<< orphan*/  COLOR_TEXT ; 
 scalar_t__ COMMAND_GROUP_HELP_ONLY ; 
 int /*<<< orphan*/  ClrLine (scalar_t__) ; 
 TYPE_2__* CmdTable ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PICE_sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PICE_strcat (char*,char*) ; 
 int /*<<< orphan*/  PICE_strlen (char*) ; 
 scalar_t__ PICE_strncmpi (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutChar (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ResetColor () ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 
 char* tempCmd ; 
 TYPE_1__* wWindow ; 

LPSTR FindCommand(LPSTR p)
{
    ULONG i,j,k=0;
    LPSTR result=NULL;

	tempCmd[0]=0;
	for(j=0,i=0;CmdTable[i].Cmd!=NULL;i++)
	{
		if(PICE_strncmpi(CmdTable[i].Cmd,p,PICE_strlen(p)) == 0 &&
           CmdTable[i].CommandGroup != COMMAND_GROUP_HELP_ONLY)
		{
			if(PICE_strlen(tempCmd))
				PICE_strcat(tempCmd,", ");
			PICE_strcat(tempCmd,CmdTable[i].Cmd);
			j++;
			k=i;
		}
	}
	if(PICE_strlen(tempCmd))
	{
		SetBackgroundColor(COLOR_CAPTION);
		SetForegroundColor(COLOR_TEXT);
		ClrLine(wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].cy);
		PutChar(tempCmd,1,wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].cy);
		if(j==1)
		{
			PICE_sprintf(tempCmd,"%s",CmdTable[k].Help);
			PutChar(tempCmd,40,wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].cy);
			result=CmdTable[k].Cmd;
		}
        ResetColor();
	}
	return result;
}