#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* iep; } ;
typedef  TYPE_1__ pp_entry_t ;
struct TYPE_15__ {char* filename; struct TYPE_15__* prev; struct TYPE_15__* next; TYPE_1__* ppp; } ;
typedef  TYPE_2__ includelogicentry_t ;
struct TYPE_13__ {int state; char* ppp; int /*<<< orphan*/  seen_junk; } ;
struct TYPE_16__ {int should_pop; int line_number; char* filename; char* include_filename; int char_number; int if_depth; int /*<<< orphan*/  bufferstate; int /*<<< orphan*/  filehandle; TYPE_5__* define; int /*<<< orphan*/  ncontinuations; TYPE_10__ incl; } ;
typedef  TYPE_3__ bufferstackentry_t ;
struct TYPE_19__ {char* input; int line_number; int char_number; int /*<<< orphan*/  file; scalar_t__ debug; } ;
struct TYPE_18__ {scalar_t__ expanding; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* bufferstack ; 
 size_t bufferstackidx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  macro_add_expansion () ; 
 int /*<<< orphan*/  ncontinuations ; 
 TYPE_10__ pp_incl_state ; 
 TYPE_2__* pp_includelogiclist ; 
 int /*<<< orphan*/  pp_internal_error (char*,int,char*) ; 
 scalar_t__ pp_macexp ; 
 TYPE_8__ pp_status ; 
 int /*<<< orphan*/  pp_writestring (char*,int,char*) ; 
 TYPE_2__* pp_xmalloc (int) ; 
 TYPE_1__* pplookup (char*) ; 
 int /*<<< orphan*/  ppy__switch_to_buffer (int /*<<< orphan*/ ) ; 
 scalar_t__ ppy_debug ; 
 int /*<<< orphan*/  printf (char*,size_t,int /*<<< orphan*/ ,TYPE_5__*,int,int,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_4__* wpp_callbacks ; 
 scalar_t__ yy_current_state () ; 
 int /*<<< orphan*/  yy_pop_state () ; 

__attribute__((used)) static bufferstackentry_t *pop_buffer(void)
{
	if(bufferstackidx < 0)
		pp_internal_error(__FILE__, __LINE__, "Bufferstack underflow?");

	if(bufferstackidx == 0)
		return NULL;

	bufferstackidx--;

	if(bufferstack[bufferstackidx].define)
		bufferstack[bufferstackidx].define->expanding = 0;
	else
	{
		includelogicentry_t *iep = NULL;

		if(!bufferstack[bufferstackidx].should_pop)
		{
			wpp_callbacks->close(pp_status.file);
			pp_writestring("# %d \"%s\" 2\n", bufferstack[bufferstackidx].line_number, bufferstack[bufferstackidx].filename);

			/* We have EOF, check the include logic */
			if(pp_incl_state.state == 2 && !pp_incl_state.seen_junk && pp_incl_state.ppp)
			{
				pp_entry_t *ppp = pplookup(pp_incl_state.ppp);
				if(ppp)
				{
					iep = pp_xmalloc(sizeof(includelogicentry_t));
					if (iep)
					{
						iep->ppp = ppp;
						ppp->iep = iep;
						iep->filename = bufferstack[bufferstackidx].include_filename;
						iep->prev = NULL;
						iep->next = pp_includelogiclist;
						if(iep->next)
							iep->next->prev = iep;
						pp_includelogiclist = iep;
						if(pp_status.debug)
							fprintf(stderr, "pop_buffer: %s:%d: includelogic added, include_ppp='%s', file='%s'\n",
                                                                bufferstack[bufferstackidx].filename, bufferstack[bufferstackidx].line_number, pp_incl_state.ppp, iep->filename);
					}
				}
			}
			free(pp_incl_state.ppp);
			pp_incl_state	= bufferstack[bufferstackidx].incl;

		}
		if (bufferstack[bufferstackidx].include_filename)
		{
			free(pp_status.input);
			pp_status.input = bufferstack[bufferstackidx].filename;
		}
		pp_status.line_number = bufferstack[bufferstackidx].line_number;
		pp_status.char_number = bufferstack[bufferstackidx].char_number;
		ncontinuations = bufferstack[bufferstackidx].ncontinuations;
		if (!iep)
			free(bufferstack[bufferstackidx].include_filename);
	}

	if(ppy_debug)
		printf("pop_buffer(%d): %p %p (%d, %d, %d) %p %d\n",
			bufferstackidx,
			bufferstack[bufferstackidx].bufferstate,
			bufferstack[bufferstackidx].define,
			bufferstack[bufferstackidx].line_number,
			bufferstack[bufferstackidx].char_number,
			bufferstack[bufferstackidx].if_depth,
			bufferstack[bufferstackidx].filename,
			bufferstack[bufferstackidx].should_pop);

	pp_status.file = bufferstack[bufferstackidx].filehandle;
	ppy__switch_to_buffer(bufferstack[bufferstackidx].bufferstate);

	if(bufferstack[bufferstackidx].should_pop)
	{
		if(yy_current_state() == pp_macexp)
			macro_add_expansion();
		else
			pp_internal_error(__FILE__, __LINE__, "Pop buffer and state without macro expansion state");
		yy_pop_state();
	}

	return &bufferstack[bufferstackidx];
}