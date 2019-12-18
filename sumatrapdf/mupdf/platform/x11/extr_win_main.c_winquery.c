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
#define  IDNO 129 
#define  IDYES 128 
 int /*<<< orphan*/  MB_YESNOCANCEL ; 
 int MessageBoxA (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ) ; 
 int QUERY_NO ; 
 int QUERY_YES ; 
 int /*<<< orphan*/  hwndframe ; 

int winquery(pdfapp_t *app, const char *query)
{
	switch(MessageBoxA(hwndframe, query, "MuPDF", MB_YESNOCANCEL))
	{
	case IDYES: return QUERY_YES;
	case IDNO:
	default: return QUERY_NO;
	}
}