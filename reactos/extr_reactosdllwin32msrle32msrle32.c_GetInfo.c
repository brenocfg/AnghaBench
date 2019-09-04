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
struct TYPE_6__ {int /*<<< orphan*/  fccHandler; } ;
struct TYPE_5__ {int dwSize; int dwFlags; int /*<<< orphan*/  szDescription; int /*<<< orphan*/  szName; void* dwVersionICM; void* dwVersion; int /*<<< orphan*/  fccHandler; int /*<<< orphan*/  fccType; } ;
typedef  int LRESULT ;
typedef  TYPE_1__ ICINFO ;
typedef  int DWORD ;
typedef  TYPE_2__ CodecInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOURCC_MRLE ; 
 int /*<<< orphan*/  ICTYPE_VIDEO ; 
 void* ICVERSION ; 
 int /*<<< orphan*/  IDS_DESCRIPTION ; 
 int /*<<< orphan*/  IDS_NAME ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSRLE32_hModule ; 
 int VIDCF_CRUNCH ; 
 int VIDCF_FASTTEMPORALC ; 
 int VIDCF_QUALITY ; 
 int VIDCF_TEMPORAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT GetInfo(const CodecInfo *pi, ICINFO *icinfo, DWORD dwSize)
{
  /* pre-condition */
  assert(pi != NULL);

  /* check parameters */
  if (icinfo == NULL)
    return sizeof(ICINFO);
  if (dwSize < sizeof(ICINFO))
    return 0;

  icinfo->dwSize       = sizeof(ICINFO);
  icinfo->fccType      = ICTYPE_VIDEO;
  icinfo->fccHandler   = (pi != NULL ? pi->fccHandler : FOURCC_MRLE);
  icinfo->dwFlags      = VIDCF_QUALITY | VIDCF_TEMPORAL | VIDCF_CRUNCH | VIDCF_FASTTEMPORALC;
  icinfo->dwVersion    = ICVERSION;
  icinfo->dwVersionICM = ICVERSION;

  LoadStringW(MSRLE32_hModule, IDS_NAME, icinfo->szName, ARRAY_SIZE(icinfo->szName));
  LoadStringW(MSRLE32_hModule, IDS_DESCRIPTION, icinfo->szDescription, ARRAY_SIZE(icinfo->szDescription));

  return sizeof(ICINFO);
}