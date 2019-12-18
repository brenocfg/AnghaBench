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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  __time64_t ;
typedef  int /*<<< orphan*/  __time32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_BAD_COMMAND ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSVCRT_INVALID_PMT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gmtime_worker (struct tm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
_gmtime32_s(
   struct tm* ptm,
   const __time32_t* ptime)
{
    __time64_t time = *ptime;
    if (!ptm)
    {
        MSVCRT_INVALID_PMT("ptm == NULL", ERROR_BAD_COMMAND);
        return ERROR_BAD_COMMAND;
    }

    if (!ptime)
    {
        MSVCRT_INVALID_PMT("ptime == NULL", ERROR_BAD_COMMAND);
        return ERROR_BAD_COMMAND;
    }

    _gmtime_worker(ptm, time, 0);

    return ERROR_SUCCESS;
}