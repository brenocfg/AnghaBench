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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/ * _tfopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doSetValue ; 
 int /*<<< orphan*/  processRegLines (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL import_registry_file(LPTSTR filename)
{
    FILE* reg_file = _tfopen(filename, _T("r"));

    if (reg_file) {
        processRegLines(reg_file, doSetValue);
        return TRUE;
    }
    return FALSE;
}