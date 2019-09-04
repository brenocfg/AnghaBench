#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dwMagic; } ;
struct TYPE_5__ {int dwSize; int /*<<< orphan*/  szDescription; int /*<<< orphan*/  szName; void* dwVersionICM; void* dwVersion; scalar_t__ dwFlags; int /*<<< orphan*/  fccHandler; int /*<<< orphan*/  fccType; } ;
typedef  int LRESULT ;
typedef  TYPE_1__ ICINFO ;
typedef  TYPE_2__ ICCVID_Info ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICCVID_MAGIC ; 
 int /*<<< orphan*/  ICCVID_hModule ; 
 int /*<<< orphan*/  ICTYPE_VIDEO ; 
 void* ICVERSION ; 
 int /*<<< orphan*/  IDS_DESCRIPTION ; 
 int /*<<< orphan*/  IDS_NAME ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT ICCVID_GetInfo( ICCVID_Info *info, ICINFO *icinfo, DWORD dwSize )
{
    if (!icinfo) return sizeof(ICINFO);
    if (dwSize < sizeof(ICINFO)) return 0;

    icinfo->dwSize = sizeof(ICINFO);
    icinfo->fccType = ICTYPE_VIDEO;
    icinfo->fccHandler = info ? info->dwMagic : ICCVID_MAGIC;
    icinfo->dwFlags = 0;
    icinfo->dwVersion = ICVERSION;
    icinfo->dwVersionICM = ICVERSION;

    LoadStringW(ICCVID_hModule, IDS_NAME, icinfo->szName, ARRAY_SIZE(icinfo->szName));
    LoadStringW(ICCVID_hModule, IDS_DESCRIPTION, icinfo->szDescription, ARRAY_SIZE(icinfo->szDescription));
    /* msvfw32 will fill icinfo->szDriver for us */

    return sizeof(ICINFO);
}