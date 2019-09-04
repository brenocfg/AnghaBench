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
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIALTERVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT ALTER_close( struct tagMSIVIEW *view )
{
    MSIALTERVIEW *av = (MSIALTERVIEW*)view;

    TRACE("%p\n", av );

    return ERROR_SUCCESS;
}