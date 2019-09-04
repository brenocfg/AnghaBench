#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  filename; struct TYPE_5__* next; } ;
typedef  TYPE_1__ includelogicentry_t ;
struct TYPE_7__ {int state; char* ppp; int ifdepth; scalar_t__ seen_junk; } ;
struct TYPE_6__ {char* input; int line_number; void* file; scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  YY_BUF_SIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__ pp_incl_state ; 
 TYPE_1__* pp_includelogiclist ; 
 void* pp_open_include (char*,int,char*,char**) ; 
 TYPE_2__ pp_status ; 
 int /*<<< orphan*/  pp_writestring (char*,char*,char*) ; 
 int /*<<< orphan*/  ppy__create_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppy__switch_to_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppy_error (char*,...) ; 
 int /*<<< orphan*/  push_buffer (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

void pp_do_include(char *fname, int type)
{
	char *newpath;
	int n;
	includelogicentry_t *iep;
	void *fp;

	if(!fname)
		return;

	for(iep = pp_includelogiclist; iep; iep = iep->next)
	{
		if(!strcmp(iep->filename, fname))
		{
			/*
			 * We are done. The file was included before.
			 * If the define was deleted, then this entry would have
			 * been deleted too.
			 */
			free(fname);
			return;
		}
	}

	n = strlen(fname);

	if(n <= 2)
	{
		ppy_error("Empty include filename");
		free(fname);
		return;
	}

	/* Undo the effect of the quotation */
	fname[n-1] = '\0';

	if((fp = pp_open_include(fname+1, type, pp_status.input, &newpath)) == NULL)
	{
		ppy_error("Unable to open include file %s", fname+1);
		free(fname);
		return;
	}

	fname[n-1] = *fname;	/* Redo the quotes */
	push_buffer(NULL, newpath, fname, 0);
	pp_incl_state.seen_junk = 0;
	pp_incl_state.state = 0;
	pp_incl_state.ppp = NULL;

	if(pp_status.debug)
		fprintf(stderr, "pp_do_include: %s:%d: include_state=%d, include_ppp='%s', include_ifdepth=%d\n",
                        pp_status.input, pp_status.line_number, pp_incl_state.state, pp_incl_state.ppp, pp_incl_state.ifdepth);
	pp_status.file = fp;
	ppy__switch_to_buffer(ppy__create_buffer(NULL, YY_BUF_SIZE));

	pp_writestring("# 1 \"%s\" 1%s\n", newpath, type ? "" : " 3");
}