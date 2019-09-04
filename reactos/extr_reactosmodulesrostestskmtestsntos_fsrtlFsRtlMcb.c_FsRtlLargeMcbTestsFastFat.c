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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  LARGE_MCB ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FsRtlInitializeLargeMcb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsRtlLookupLargeMcbEntry (int /*<<< orphan*/ *,long long,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsRtlLookupLastLargeMcbEntryAndIndex (int /*<<< orphan*/ *,int*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  FsRtlUninitializeLargeMcb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  ok_bool_false (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_eq_longlong (int,int) ; 
 int /*<<< orphan*/  ok_eq_ulong (scalar_t__,scalar_t__) ; 

__attribute__((used)) static VOID FsRtlLargeMcbTestsFastFat()
{
    LARGE_MCB FirstMcb;
    LONGLONG Lbn, Vbn, SectorCount;
    ULONG Index;
    BOOLEAN Result;

    FsRtlInitializeLargeMcb(&FirstMcb, PagedPool);

    Lbn = -1;
    SectorCount = -1;
    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 8388607LL, &Lbn, &SectorCount, NULL, NULL, NULL);
    ok_bool_false(Result, "FsRtlLookupLargeMcbEntry returned");
    ok_eq_longlong(Lbn, -1);
    ok_eq_longlong(SectorCount, -1);

    Vbn = -1;
    Lbn = -1;
    Index = (ULONG) -1;
    Result = FsRtlLookupLastLargeMcbEntryAndIndex(&FirstMcb, &Vbn, &Lbn, &Index);
    ok_bool_false(Result, "FsRtlLookupLastLargeMcbEntryAndIndex returned");
    ok_eq_longlong(Vbn, -1);
    ok_eq_longlong(Lbn, -1);
    ok_eq_ulong(Index, (ULONG) -1);

    FsRtlUninitializeLargeMcb(&FirstMcb);
}