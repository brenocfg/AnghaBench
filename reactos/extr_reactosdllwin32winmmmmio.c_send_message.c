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
struct IOProcList {scalar_t__ is_unicode; int /*<<< orphan*/  (* pIOProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ LPMMIOINFO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  MMSYSERR_ERROR ; 
 int /*<<< orphan*/  MMSYSERR_INVALPARAM ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT	send_message(struct IOProcList* ioProc, LPMMIOINFO mmioinfo,
                             DWORD wMsg, LPARAM lParam1,
                             LPARAM lParam2, BOOL is_unicode)
{
    LRESULT 		result = MMSYSERR_ERROR;
    LPARAM		lp1 = lParam1, lp2 = lParam2;

    if (!ioProc) {
	ERR("ioProc NULL\n");
	return MMSYSERR_INVALPARAM;
    }

    if (ioProc->is_unicode != is_unicode) {
        /* map (lParam1, lParam2) into (lp1, lp2) 32 A<=>W */
        FIXME("NIY 32 A<=>W mapping\n");
    }
    result = (ioProc->pIOProc)((LPSTR)mmioinfo, wMsg, lp1, lp2);

#if 0
    if (ioProc->is_unicode != is_unicode) {
	    /* unmap (lParam1, lParam2) into (lp1, lp2) 32 A<=>W */
	}
#endif

    return result;
}