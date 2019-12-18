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
struct TYPE_2__ {scalar_t__ visible; char* varname; int /*<<< orphan*/  (* proc ) (int,char const* const,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  (* PrefProc ) (int,char const* const,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ ISTREQ (char const* const,char*) ; 
 int /*<<< orphan*/  Show1 (int) ; 
 int gNumPrefOpts ; 
 TYPE_1__* gPrefOpts ; 
 int /*<<< orphan*/  gPrefsDirty ; 
 scalar_t__ kPrefOptObselete ; 
 scalar_t__ kPrefOptVisible ; 
 int /*<<< orphan*/  printf (char*,char const* const) ; 
 int /*<<< orphan*/  stub1 (int,char const* const,int /*<<< orphan*/ *) ; 

void
Set(const char *const tok1, const char *const tok2)
{
	int t;

	if ((tok1 == NULL) || (ISTREQ(tok1, "all"))) {
		/* Show all. */
		for (t=0; t<gNumPrefOpts; t++) {
			if (gPrefOpts[t].visible == kPrefOptVisible)
				Show1(t);
		}
	} else if (tok2 == NULL) {
		/* Show one. */
		for (t=0; t<gNumPrefOpts; t++) {
			if (ISTREQ(tok1, gPrefOpts[t].varname)) {
				if (gPrefOpts[t].visible == kPrefOptObselete) {
					(void) printf("The \"%s\" option is obselete or not implemented.\n", tok1);
				} else {
					Show1(t);
				}
				break;
			}
		}
		if (t >= gNumPrefOpts) {
			(void) printf("Unknown option \"%s\" -- try \"show all\" to list available options.\n", tok1);
		}
	} else {
		/* Set one. */
		for (t=0; t<gNumPrefOpts; t++) {
			if (ISTREQ(tok1, gPrefOpts[t].varname)) {
				if (gPrefOpts[t].visible == kPrefOptObselete) {
					(void) printf("The \"%s\" option is obselete or not implemented.\n", tok1);
				} else if (gPrefOpts[t].proc != (PrefProc) 0) {
					(*gPrefOpts[t].proc)(t, tok2, NULL);
					gPrefsDirty++;
				}
				break;
			}
		}
		if (t >= gNumPrefOpts) {
			(void) printf("Unknown option \"%s\" -- try \"show all\" to list available options.\n", tok1);
		}
	}
}