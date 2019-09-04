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
typedef  int /*<<< orphan*/  WINE_MCIMIDI ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mciGetDriverData (int) ; 
 int /*<<< orphan*/  mciSetDriverData (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	DWORD	MIDI_drvClose(DWORD dwDevID)
{
    WINE_MCIMIDI*  wmm = (WINE_MCIMIDI*)mciGetDriverData(dwDevID);

    if (wmm) {
	HeapFree(GetProcessHeap(), 0, wmm);
	mciSetDriverData(dwDevID, 0);
	return 1;
    }
    return (dwDevID == 0xFFFFFFFF) ? 1 : 0;
}