#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
struct TYPE_6__ {int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__* PCJAPANESE_ERA ;
typedef  TYPE_2__* LPSYSTEMTIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

__attribute__((used)) static BOOL JapaneseEra_ToSystemTime(PCJAPANESE_ERA pEra, LPSYSTEMTIME pst)
{
    ASSERT(pEra != NULL);
    ASSERT(pst != NULL);

    ZeroMemory(pst, sizeof(*pst));
    pst->wYear = pEra->wYear;
    pst->wMonth = pEra->wMonth;
    pst->wDay = pEra->wDay;
    return TRUE;
}