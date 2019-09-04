#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cmdf; } ;
typedef  TYPE_1__ OLECMD ;
typedef  int /*<<< orphan*/  HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int OLECMDF_ENABLED ; 
 int OLECMDF_SUPPORTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static HRESULT query_selall_status(HTMLDocument *This, OLECMD *cmd)
{
    TRACE("(%p)->(%p)\n", This, cmd);

    cmd->cmdf = OLECMDF_SUPPORTED|OLECMDF_ENABLED;
    return S_OK;
}