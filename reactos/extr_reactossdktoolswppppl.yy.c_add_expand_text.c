#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* text; size_t argidx; } ;
struct TYPE_10__ {int type; TYPE_2__ subst; TYPE_1__* prev; struct TYPE_10__* next; } ;
typedef  TYPE_3__ mtext_t ;
struct TYPE_11__ {char** args; char** ppargs; int* nnls; } ;
typedef  TYPE_4__ macexpstackentry_t ;
struct TYPE_8__ {int const type; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_text (char*,int) ; 
 int curdef_idx ; 
 int* curdef_text ; 
#define  exp_concat 131 
#define  exp_stringize 130 
#define  exp_subst 129 
#define  exp_text 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  memmove (int*,char*,int) ; 
 int /*<<< orphan*/  pp_flex_debug ; 
 int /*<<< orphan*/  pp_internal_error (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static mtext_t *add_expand_text(mtext_t *mtp, macexpstackentry_t *mep, int *nnl)
{
	char *cptr;
	char *exp;
	int tag;
	int n;

	if(mtp == NULL)
		return NULL;

	switch(mtp->type)
	{
	case exp_text:
		if(pp_flex_debug)
			fprintf(stderr, "add_expand_text: exp_text: '%s'\n", mtp->subst.text);
		add_text(mtp->subst.text, strlen(mtp->subst.text));
		break;

	case exp_stringize:
		if(pp_flex_debug)
			fprintf(stderr, "add_expand_text: exp_stringize(%d): '%s'\n",
				mtp->subst.argidx,
				mep->args[mtp->subst.argidx]);
		cptr = mep->args[mtp->subst.argidx];
		add_text("\"", 1);
		while(*cptr)
		{
			if(*cptr == '"' || *cptr == '\\')
				add_text("\\", 1);
			add_text(cptr, 1);
			cptr++;
		}
		add_text("\"", 1);
		break;

	case exp_concat:
		if(pp_flex_debug)
			fprintf(stderr, "add_expand_text: exp_concat\n");
		/* Remove trailing whitespace from current expansion text */
		while(curdef_idx)
		{
			if(isspace(curdef_text[curdef_idx-1] & 0xff))
				curdef_idx--;
			else
				break;
		}
		/* tag current position and recursively expand the next part */
		tag = curdef_idx;
		mtp = add_expand_text(mtp->next, mep, nnl);

		/* Now get rid of the leading space of the expansion */
		cptr = &curdef_text[tag];
		n = curdef_idx - tag;
		while(n)
		{
			if(isspace(*cptr & 0xff))
			{
				cptr++;
				n--;
			}
			else
				break;
		}
		if(cptr != &curdef_text[tag])
		{
			memmove(&curdef_text[tag], cptr, n);
			curdef_idx -= (curdef_idx - tag) - n;
		}
		break;

	case exp_subst:
		if((mtp->next && mtp->next->type == exp_concat) || (mtp->prev && mtp->prev->type == exp_concat))
			exp = mep->args[mtp->subst.argidx];
		else
			exp = mep->ppargs[mtp->subst.argidx];
		if(exp)
		{
			add_text(exp, strlen(exp));
			*nnl -= mep->nnls[mtp->subst.argidx];
			cptr = strchr(exp, '\n');
			while(cptr)
			{
				*cptr = ' ';
				cptr = strchr(cptr+1, '\n');
			}
			mep->nnls[mtp->subst.argidx] = 0;
		}
		if(pp_flex_debug)
			fprintf(stderr, "add_expand_text: exp_subst(%d): '%s'\n", mtp->subst.argidx, exp);
		break;

	default:
		pp_internal_error(__FILE__, __LINE__, "Invalid expansion type (%d) in macro expansion\n", mtp->type);
	}
	return mtp;
}