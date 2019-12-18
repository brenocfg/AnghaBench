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
typedef  int /*<<< orphan*/  pdfapp_t ;

/* Variables and functions */
 int CANCEL ; 
 int DISCARD ; 
#define  IDNO 129 
#define  IDYES 128 
 int /*<<< orphan*/  MB_YESNOCANCEL ; 
 int MessageBoxA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int SAVE ; 
 int /*<<< orphan*/  hwndframe ; 

int winsavequery(pdfapp_t *app)
{
	switch(MessageBoxA(hwndframe, "File has unsaved changes. Do you want to save", "MuPDF", MB_YESNOCANCEL))
	{
	case IDYES: return SAVE;
	case IDNO: return DISCARD;
	default: return CANCEL;
	}
}