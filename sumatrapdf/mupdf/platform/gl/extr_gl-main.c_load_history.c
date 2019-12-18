#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {void* loc; } ;

/* Variables and functions */
 int PATH_MAX ; 
 void* currentpage ; 
 int /*<<< orphan*/  filename ; 
 TYPE_1__* future ; 
 int future_count ; 
 int fz_clampi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* history ; 
 int history_count ; 
 int /*<<< orphan*/  js_freestate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_getindex (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_getlength (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_hasproperty (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ js_isarray (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * js_newstate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* marks ; 
 int /*<<< orphan*/  nelem (TYPE_1__*) ; 
 int /*<<< orphan*/  read_history_file_as_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realpath (int /*<<< orphan*/ ,char*) ; 
 void* try_location (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_history(void)
{
	js_State *J;
	char absname[PATH_MAX];
	int i, n;

	if (!realpath(filename, absname))
		return;

	J = js_newstate(NULL, NULL, 0);

	read_history_file_as_json(J);

	if (js_hasproperty(J, -1, absname))
	{
		if (js_hasproperty(J, -1, "current"))
		{
			currentpage = try_location(J);
			js_pop(J, 1);
		}

		if (js_hasproperty(J, -1, "history"))
		{
			if (js_isarray(J, -1))
			{
				history_count = fz_clampi(js_getlength(J, -1), 0, nelem(history));
				for (i = 0; i < history_count; ++i)
				{
					js_getindex(J, -1, i);
					history[i].loc = try_location(J);
					js_pop(J, 1);
				}
			}
			js_pop(J, 1);
		}

		if (js_hasproperty(J, -1, "future"))
		{
			if (js_isarray(J, -1))
			{
				future_count = fz_clampi(js_getlength(J, -1), 0, nelem(future));
				for (i = 0; i < future_count; ++i)
				{
					js_getindex(J, -1, i);
					future[i].loc = try_location(J);
					js_pop(J, 1);
				}
			}
			js_pop(J, 1);
		}

		if (js_hasproperty(J, -1, "marks"))
		{
			if (js_isarray(J, -1))
			{
				n = fz_clampi(js_getlength(J, -1), 0, nelem(marks));
				for (i = 0; i < n; ++i)
				{
					js_getindex(J, -1, i);
					marks[i].loc = try_location(J);
					js_pop(J, 1);
				}
			}
			js_pop(J, 1);
		}
	}

	js_freestate(J);
}