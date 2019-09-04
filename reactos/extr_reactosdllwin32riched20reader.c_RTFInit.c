#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int cbSize; } ;
struct TYPE_8__ {char* rtfTextBuf; char* pushedTextBuf; int ansiCodePage; int unicodeLength; int codePage; int rtfClass; int pushedClass; int dwMaxCPOutputCount; TYPE_2__ fmt; scalar_t__ borderType; void* canInheritInTbl; scalar_t__ nestingLevel; int /*<<< orphan*/ * tableDef; void* cpOutputBuffer; scalar_t__ dwCPOutputCount; void* bumpLine; void* prevChar; scalar_t__ rtfLinePos; scalar_t__ rtfLineNum; void* pushedChar; scalar_t__ defFont; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 void* EOF ; 
 int /*<<< orphan*/  ERR (char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  RTFDestroyAttrs (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFSetClassCallback (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTFSetDestinationCallback (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTFSetReadHook (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadColorTbl ; 
 int /*<<< orphan*/ * ReadFontTbl ; 
 int /*<<< orphan*/ * ReadInfoGroup ; 
 int /*<<< orphan*/ * ReadObjGroup ; 
 int /*<<< orphan*/ * ReadPictGroup ; 
 int /*<<< orphan*/ * ReadStyleSheet ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int rtfBufSiz ; 
 int rtfColorTbl ; 
 int rtfFontTbl ; 
 int rtfInfo ; 
 int rtfMaxClass ; 
 int rtfMaxDestination ; 
 int rtfObject ; 
 int rtfPict ; 
 int rtfStyleSheet ; 

void RTFInit(RTF_Info *info)
{
	int	i;

	if (info->rtfTextBuf == NULL)	/* initialize the text buffers */
	{
		info->rtfTextBuf = heap_alloc (rtfBufSiz);
		info->pushedTextBuf = heap_alloc (rtfBufSiz);
		if (info->rtfTextBuf == NULL || info->pushedTextBuf == NULL) {
			ERR ("Cannot allocate text buffers.\n");
			return;
		}
		info->rtfTextBuf[0] = info->pushedTextBuf[0] = '\0';
	}

	for (i = 0; i < rtfMaxClass; i++)
		RTFSetClassCallback (info, i, NULL);
	for (i = 0; i < rtfMaxDestination; i++)
		RTFSetDestinationCallback (info, i, NULL);

	/* install built-in destination readers */
	RTFSetDestinationCallback (info, rtfFontTbl, ReadFontTbl);
	RTFSetDestinationCallback (info, rtfColorTbl, ReadColorTbl);
	RTFSetDestinationCallback (info, rtfStyleSheet, ReadStyleSheet);
	RTFSetDestinationCallback (info, rtfInfo, ReadInfoGroup);
	RTFSetDestinationCallback (info, rtfPict, ReadPictGroup);
	RTFSetDestinationCallback (info, rtfObject, ReadObjGroup);


	RTFSetReadHook (info, NULL);

	/* dump old lists if necessary */

	RTFDestroyAttrs(info);

        info->ansiCodePage = 1252; /* Latin-1; actually unused */
	info->unicodeLength = 1; /* \uc1 is the default */
	info->codePage = info->ansiCodePage;
        info->defFont = 0;

	info->rtfClass = -1;
	info->pushedClass = -1;
	info->pushedChar = EOF;

	info->rtfLineNum = 0;
	info->rtfLinePos = 0;
	info->prevChar = EOF;
        info->bumpLine = FALSE;

	info->dwCPOutputCount = 0;
        if (!info->cpOutputBuffer)
	{
		info->dwMaxCPOutputCount = 0x1000;
		info->cpOutputBuffer = heap_alloc(info->dwMaxCPOutputCount);
	}

        info->tableDef = NULL;
        info->nestingLevel = 0;
        info->canInheritInTbl = FALSE;
        info->borderType = 0;

        memset(&info->fmt, 0, sizeof(info->fmt));
        info->fmt.cbSize = sizeof(info->fmt);
}