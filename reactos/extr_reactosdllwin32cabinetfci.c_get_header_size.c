#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int cab_ULONG ;
struct TYPE_6__ {int cbReserveCFHeader; scalar_t__ cbReserveCFData; scalar_t__ cbReserveCFFolder; } ;
struct TYPE_7__ {TYPE_1__* pccab; scalar_t__ fNextCab; int /*<<< orphan*/  szPrevDisk; int /*<<< orphan*/  szPrevCab; scalar_t__ fPrevCab; TYPE_2__ ccab; } ;
struct TYPE_5__ {int /*<<< orphan*/  szDisk; int /*<<< orphan*/  szCab; } ;
typedef  TYPE_3__ FCI_Int ;
typedef  int /*<<< orphan*/  CFHEADER ;

/* Variables and functions */
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cab_ULONG get_header_size( FCI_Int *fci )
{
    cab_ULONG ret = sizeof(CFHEADER) + fci->ccab.cbReserveCFHeader;

    if (fci->ccab.cbReserveCFHeader || fci->ccab.cbReserveCFFolder || fci->ccab.cbReserveCFData)
        ret += 4;

    if (fci->fPrevCab)
        ret += strlen( fci->szPrevCab ) + 1 + strlen( fci->szPrevDisk ) + 1;

    if (fci->fNextCab)
        ret += strlen( fci->pccab->szCab ) + 1 + strlen( fci->pccab->szDisk ) + 1;

    return ret;
}