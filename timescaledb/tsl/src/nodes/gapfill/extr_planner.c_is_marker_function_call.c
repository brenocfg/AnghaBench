#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  funcid; } ;
typedef  TYPE_1__ FuncExpr ;

/* Variables and functions */
 int /*<<< orphan*/  GAPFILL_INTERPOLATE_FUNCTION ; 
 int /*<<< orphan*/  GAPFILL_LOCF_FUNCTION ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char* get_func_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
is_marker_function_call(FuncExpr *call)
{
	char *func_name = get_func_name(call->funcid);
	return strncmp(func_name, GAPFILL_LOCF_FUNCTION, NAMEDATALEN) == 0 ||
		   strncmp(func_name, GAPFILL_INTERPOLATE_FUNCTION, NAMEDATALEN) == 0;
}