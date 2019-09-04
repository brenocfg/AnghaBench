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
typedef  int WORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int CDFRAMES_PERSEC ; 
 int /*<<< orphan*/  MCI_MAKE_MSF (int,int,int) ; 
 int MCI_MSF_FRAME (int /*<<< orphan*/ ) ; 
 int MCI_MSF_MINUTE (int /*<<< orphan*/ ) ; 
 int MCI_MSF_SECOND (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD MSF_Add(DWORD d1, DWORD d2)
{
    WORD c, m, s, f;
    f = MCI_MSF_FRAME(d1)  + MCI_MSF_FRAME(d2);
    c = f / CDFRAMES_PERSEC;
    f = f % CDFRAMES_PERSEC;
    s = MCI_MSF_SECOND(d1) + MCI_MSF_SECOND(d2) + c;
    c = s / 60;
    s = s % 60;
    m = MCI_MSF_MINUTE(d1) + MCI_MSF_MINUTE(d2) + c; /* may be > 60 */
    return MCI_MAKE_MSF(m,s,f);
}