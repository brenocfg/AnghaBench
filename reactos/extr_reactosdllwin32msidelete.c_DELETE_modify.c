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
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIMODIFY ;
typedef  int /*<<< orphan*/  MSIDELETEVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT DELETE_modify( struct tagMSIVIEW *view, MSIMODIFY eModifyMode,
                           MSIRECORD *rec, UINT row )
{
    MSIDELETEVIEW *dv = (MSIDELETEVIEW*)view;

    TRACE("%p %d %p\n", dv, eModifyMode, rec );

    return ERROR_FUNCTION_FAILED;
}