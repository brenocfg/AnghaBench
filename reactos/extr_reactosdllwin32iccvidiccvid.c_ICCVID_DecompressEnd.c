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
struct TYPE_3__ {int /*<<< orphan*/ * cvinfo; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ ICCVID_Info ;

/* Variables and functions */
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  free_cvinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT ICCVID_DecompressEnd( ICCVID_Info *info )
{
    if( info->cvinfo )
    {
        free_cvinfo( info->cvinfo );
        info->cvinfo = NULL;
    }
    return ICERR_OK;
}