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
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {scalar_t__ cy; } ;
typedef  int* LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BACKGROUND ; 
 int /*<<< orphan*/  COLOR_FOREGROUND ; 
 int /*<<< orphan*/  Clear (size_t) ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisableScroll (size_t) ; 
 int /*<<< orphan*/  EnableScroll (size_t) ; 
 int GLOBAL_SCREEN_WIDTH ; 
 int /*<<< orphan*/  PICE_sprintf (char*,char*,scalar_t__) ; 
 int PICE_strlen (char*) ; 
 int /*<<< orphan*/  Print (size_t,char*) ; 
 int /*<<< orphan*/  ResetColor () ; 
 size_t SOURCE_WINDOW ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 
 char* tempCmd ; 
 TYPE_1__* wWindow ; 

void DisplaySourceFile(LPSTR pSrcLine,LPSTR pSrcEnd,ULONG ulLineNumber,ULONG ulLineNumberToInvert)
{
    ULONG i;
    LPSTR pTemp;
    ULONG j = ulLineNumber-1;

    DPRINT((0,"DisplaySourceFile(%.8X,%u,%u)\n",pSrcLine,ulLineNumber,ulLineNumberToInvert));

    // go to line
    while(j--)
    {
        // goto end of current line
        while(*pSrcLine!=0x0a && *pSrcLine!=0x0d)
            pSrcLine++;

        // skip over the line end
        if(*pSrcLine == 0x0d)
            pSrcLine++;
        if(*pSrcLine == 0x0a)
            pSrcLine++;
    }

    Clear(SOURCE_WINDOW);
    DisableScroll(SOURCE_WINDOW);
    for(i=0;i<wWindow[SOURCE_WINDOW].cy;i++)
    {
        pTemp = tempCmd;

        if(pSrcLine<pSrcEnd)
        {
            PICE_sprintf(tempCmd,".%.5u ",ulLineNumber+i);
            pTemp = tempCmd + PICE_strlen(tempCmd);

            while(pSrcLine<pSrcEnd && *pSrcLine!=0x0a && *pSrcLine!=0x0d)
            {
                if(*pSrcLine==0x9) // TAB
                {
                    *pTemp++ = 0x20;
                    *pTemp++ = 0x20;
                    *pTemp++ = 0x20;
                    *pTemp++ = 0x20;
                    pSrcLine++;
                }
                else
                {
                    *pTemp++ = *pSrcLine++;
                }
            }

            if(pSrcLine<pSrcEnd)
            {
                // skip over the line end
                if(*pSrcLine == 0x0d)
                    pSrcLine++;
                if(*pSrcLine == 0x0a)
                    pSrcLine++;
            }

            *pTemp++ = '\n';
            *pTemp = 0;

            if(PICE_strlen(tempCmd)>GLOBAL_SCREEN_WIDTH-1)
            {
                tempCmd[GLOBAL_SCREEN_WIDTH-2]='\n';
                tempCmd[GLOBAL_SCREEN_WIDTH-1]=0;
            }

            if( (ulLineNumberToInvert!=-1) &&
               ((int)(ulLineNumberToInvert-ulLineNumber)>=0) &&
               ((ulLineNumberToInvert-ulLineNumber)<wWindow[SOURCE_WINDOW].cy) &&
               (i==(ulLineNumberToInvert-ulLineNumber)) )
            {
                SetForegroundColor(COLOR_BACKGROUND);
                SetBackgroundColor(COLOR_FOREGROUND);
            }

            Print(SOURCE_WINDOW,tempCmd);

            if( (ulLineNumberToInvert!=-1) &&
               ((int)(ulLineNumberToInvert-ulLineNumber)>=0) &&
               ((ulLineNumberToInvert-ulLineNumber)<wWindow[SOURCE_WINDOW].cy) &&
               (i==(ulLineNumberToInvert-ulLineNumber)) )
            {
                ResetColor();
            }

        }
        else
        {
            Print(SOURCE_WINDOW,"---- End of source file --------------\n");
            break;
        }
    }
    EnableScroll(SOURCE_WINDOW);
}