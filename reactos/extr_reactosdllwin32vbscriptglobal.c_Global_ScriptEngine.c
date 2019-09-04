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
typedef  int /*<<< orphan*/  vbdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbscriptW ; 

__attribute__((used)) static HRESULT Global_ScriptEngine(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    TRACE("%s\n", debugstr_variant(arg));

    assert(args_cnt == 0);

    return return_string(res, vbscriptW);
}