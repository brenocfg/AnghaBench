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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  NSCMD_COPY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_ns_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT exec_copy(HTMLDocument *This, DWORD nCmdexecopt, VARIANT *pvaIn, VARIANT *pvaOut)
{
    TRACE("(%p)->(%d %s %p)\n", This, nCmdexecopt, debugstr_variant(pvaIn), pvaOut);

    do_ns_command(This, NSCMD_COPY, NULL);
    return S_OK;
}