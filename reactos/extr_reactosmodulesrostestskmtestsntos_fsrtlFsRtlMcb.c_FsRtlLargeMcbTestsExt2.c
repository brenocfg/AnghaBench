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
typedef  int ULONG ;
typedef  long long LONGLONG ;
typedef  int /*<<< orphan*/  LARGE_MCB ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DumpAllRuns (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ FsRtlAddLargeMcbEntry (int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ FsRtlGetNextLargeMcbEntry (int /*<<< orphan*/ *,int,long long*,long long*,long long*) ; 
 int /*<<< orphan*/  FsRtlInitializeLargeMcb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FsRtlLookupLargeMcbEntry (int /*<<< orphan*/ *,int,long long*,long long*,long long*,long long*,int*) ; 
 int FsRtlNumberOfRunsInLargeMcb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsRtlTruncateLargeMcb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsRtlUninitializeLargeMcb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static VOID FsRtlLargeMcbTestsExt2()
{
    LARGE_MCB FirstMcb, SecondMcb;
    LONGLONG Lbn, SectorCountFromLbn, StartingLbn, SectorCountFromStartingLbn, Vbn, SectorCount;
    ULONG Index, NbRuns;
    BOOLEAN Result;

    FsRtlInitializeLargeMcb(&FirstMcb, PagedPool);
    FsRtlInitializeLargeMcb(&SecondMcb, PagedPool);

    FsRtlTruncateLargeMcb(&FirstMcb, 0);
    FsRtlTruncateLargeMcb(&SecondMcb, 0);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 1, &Lbn, &SectorCountFromLbn, NULL, NULL, NULL);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&FirstMcb, 1, 198657, 1);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    DumpAllRuns(&FirstMcb);

    NbRuns = FsRtlNumberOfRunsInLargeMcb(&FirstMcb);
    ok(NbRuns == 2, "Expected 2 runs, got: %lu\n", NbRuns);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 1, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 198657LL, "Expected Lbn 198657, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 1LL, "Expected SectorCountFromLbn 1, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 198657LL, "Expected StartingLbn 198657, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 1LL, "Expected SectorCountFromStartingLbn 1, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 1, "Expected Index 1, got: %d\n", Index);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 2, &Lbn, &SectorCountFromLbn, NULL, NULL, NULL);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&FirstMcb, 2, 199169, 11);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    DumpAllRuns(&FirstMcb);

    NbRuns = FsRtlNumberOfRunsInLargeMcb(&FirstMcb);
    ok(NbRuns == 3, "Expected 3 runs, got: %lu\n", NbRuns);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 2, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 199169LL, "Expected Lbn 199169, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 11LL, "Expected SectorCountFromLbn 11, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 199169LL, "Expected StartingLbn 199169, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 11LL, "Expected SectorCountFromStartingLbn 11, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 2, "Expected Index 2, got: %d\n", Index);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 0, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 0LL, "Expected Vbn 0, got: %I64d\n", Vbn);
    ok(Lbn == -1LL, "Expected Lbn -1, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 1, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 1LL, "Expected Vbn 1, got: %I64d\n", Vbn);
    ok(Lbn == 198657LL, "Expected Lbn 198657, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 2, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 2LL, "Expected Vbn 2, got: %I64d\n", Vbn);
    ok(Lbn == 199169LL, "Expected Lbn 199169, got: %I64d\n", Lbn);
    ok(SectorCount == 11LL, "Expected SectorCount 11, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 3, &Vbn, &Lbn, &SectorCount);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&SecondMcb, 197128, 197128, 1);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    Result = FsRtlLookupLargeMcbEntry(&SecondMcb, 197128, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 197128LL, "Expected Lbn 197128, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 1LL, "Expected SectorCountFromLbn 1, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 197128LL, "Expected StartingLbn 197128, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 1LL, "Expected SectorCountFromStartingLbn 1, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 1, "Expected Index 1, got: %d\n", Index);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 13, &Lbn, &SectorCountFromLbn, NULL, NULL, NULL);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&FirstMcb, 13, 199180, 4);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    DumpAllRuns(&FirstMcb);

    NbRuns = FsRtlNumberOfRunsInLargeMcb(&FirstMcb);
    ok(NbRuns == 3, "Expected 3 runs, got: %lu\n", NbRuns);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 13, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 199180LL, "Expected Lbn 199180, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 4LL, "Expected SectorCountFromLbn 4, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 199169LL, "Expected StartingLbn 199169, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 15LL, "Expected SectorCountFromStartingLbn 15, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 2, "Expected Index 2, got: %d\n", Index);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 0, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 0LL, "Expected Vbn 0, got: %I64d\n", Vbn);
    ok(Lbn == -1LL, "Expected Lbn -1, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 1, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 1LL, "Expected Vbn 1, got: %I64d\n", Vbn);
    ok(Lbn == 198657LL, "Expected Lbn 198657, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 2, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 2LL, "Expected Vbn 2, got: %I64d\n", Vbn);
    ok(Lbn == 199169LL, "Expected Lbn 199169, got: %I64d\n", Lbn);
    ok(SectorCount == 15LL, "Expected SectorCount 15, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 3, &Vbn, &Lbn, &SectorCount);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&SecondMcb, 197128, 197128, 1);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    Result = FsRtlLookupLargeMcbEntry(&SecondMcb, 197128, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 197128LL, "Expected Lbn 197128, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 1LL, "Expected SectorCountFromLbn 1, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 197128LL, "Expected StartingLbn 197128, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 1LL, "Expected SectorCountFromStartingLbn 1, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 1, "Expected Index 1, got: %d\n", Index);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 17, &Lbn, &SectorCountFromLbn, NULL, NULL, NULL);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&FirstMcb, 17, 1105, 16);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    DumpAllRuns(&FirstMcb);

    NbRuns = FsRtlNumberOfRunsInLargeMcb(&FirstMcb);
    ok(NbRuns == 4, "Expected 4 runs, got: %lu\n", NbRuns);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 17, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 1105LL, "Expected Lbn 1105, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 16LL, "Expected SectorCountFromLbn 16, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 1105LL, "Expected StartingLbn 1105, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 16LL, "Expected SectorCountFromStartingLbn 16, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 3, "Expected Index 3, got: %d\n", Index);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 0, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 0LL, "Expected Vbn 0, got: %I64d\n", Vbn);
    ok(Lbn == -1LL, "Expected Lbn -1, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 1, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 1LL, "Expected Vbn 1, got: %I64d\n", Vbn);
    ok(Lbn == 198657LL, "Expected Lbn 198657, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 2, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 2LL, "Expected Vbn 2, got: %I64d\n", Vbn);
    ok(Lbn == 199169LL, "Expected Lbn 199169, got: %I64d\n", Lbn);
    ok(SectorCount == 15LL, "Expected SectorCount 15, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 3, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 17LL, "Expected Vbn 17, got: %I64d\n", Vbn);
    ok(Lbn == 1105LL, "Expected Lbn 1105, got: %I64d\n", Lbn);
    ok(SectorCount == 16LL, "Expected SectorCount 16, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 4, &Vbn, &Lbn, &SectorCount);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&SecondMcb, 197128, 197128, 1);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    Result = FsRtlLookupLargeMcbEntry(&SecondMcb, 197128, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 197128LL, "Expected Lbn 197128, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 1LL, "Expected SectorCountFromLbn 1, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 197128LL, "Expected StartingLbn 197128, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 1LL, "Expected SectorCountFromStartingLbn 1, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 1, "Expected Index 1, got: %d\n", Index);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 33, &Lbn, &SectorCountFromLbn, NULL, NULL, NULL);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&FirstMcb, 33, 1185, 32);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    DumpAllRuns(&FirstMcb);

    NbRuns = FsRtlNumberOfRunsInLargeMcb(&FirstMcb);
    ok(NbRuns == 5, "Expected 5 runs, got: %lu\n", NbRuns);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 33, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 1185LL, "Expected Lbn 1185, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 32LL, "Expected SectorCountFromLbn 32, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 1185LL, "Expected StartingLbn 1185, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 32LL, "Expected SectorCountFromStartingLbn 32, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 4, "Expected Index 4, got: %d\n", Index);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 0, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 0LL, "Expected Vbn 0, got: %I64d\n", Vbn);
    ok(Lbn == -1LL, "Expected Lbn -1, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 1, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 1LL, "Expected Vbn 1, got: %I64d\n", Vbn);
    ok(Lbn == 198657LL, "Expected Lbn 198657, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 2, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 2LL, "Expected Vbn 2, got: %I64d\n", Vbn);
    ok(Lbn == 199169LL, "Expected Lbn 199169, got: %I64d\n", Lbn);
    ok(SectorCount == 15LL, "Expected SectorCount 15, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 3, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 17LL, "Expected Vbn 17, got: %I64d\n", Vbn);
    ok(Lbn == 1105LL, "Expected Lbn 1105, got: %I64d\n", Lbn);
    ok(SectorCount == 16LL, "Expected SectorCount 16, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 4, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 33LL, "Expected Vbn 33, got: %I64d\n", Vbn);
    ok(Lbn == 1185LL, "Expected Lbn 1185, got: %I64d\n", Lbn);
    ok(SectorCount == 32LL, "Expected SectorCount 32, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 5, &Vbn, &Lbn, &SectorCount);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&SecondMcb, 197128, 197128, 1);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    Result = FsRtlLookupLargeMcbEntry(&SecondMcb, 197128, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 197128LL, "Expected Lbn 197128, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 1LL, "Expected SectorCountFromLbn 1, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 197128LL, "Expected StartingLbn 197128, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 1LL, "Expected SectorCountFromStartingLbn 1, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 1, "Expected Index 1, got: %d\n", Index);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 65, &Lbn, &SectorCountFromLbn, NULL, NULL, NULL);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlAddLargeMcbEntry(&FirstMcb, 65, 1249, 44);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");

    DumpAllRuns(&FirstMcb);

    NbRuns = FsRtlNumberOfRunsInLargeMcb(&FirstMcb);
    ok(NbRuns == 6, "Expected 6 runs, got: %lu\n", NbRuns);

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 65, &Lbn, &SectorCountFromLbn, &StartingLbn, &SectorCountFromStartingLbn, &Index);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 1249LL, "Expected Lbn 1249, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 44LL, "Expected SectorCountFromLbn 44, got: %I64d\n", SectorCountFromLbn);
    ok(StartingLbn == 1249LL, "Expected StartingLbn 1249, got: %I64d\n", StartingLbn);
    ok(SectorCountFromStartingLbn == 44LL, "Expected SectorCountFromStartingLbn 44, got: %I64d\n", SectorCountFromStartingLbn);
    ok(Index == 5, "Expected Index 1, got: %d\n", Index);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 0, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 0LL, "Expected Vbn 0, got: %I64d\n", Vbn);
    ok(Lbn == -1LL, "Expected Lbn -1, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 1, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 1LL, "Expected Vbn 1, got: %I64d\n", Vbn);
    ok(Lbn == 198657LL, "Expected Lbn 198657, got: %I64d\n", Lbn);
    ok(SectorCount == 1LL, "Expected SectorCount 1, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 2, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 2LL, "Expected Vbn 2, got: %I64d\n", Vbn);
    ok(Lbn == 199169LL, "Expected Lbn 199169, got: %I64d\n", Lbn);
    ok(SectorCount == 15LL, "Expected SectorCount 15, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 3, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 17LL, "Expected Vbn 17, got: %I64d\n", Vbn);
    ok(Lbn == 1105LL, "Expected Lbn 1105, got: %I64d\n", Lbn);
    ok(SectorCount == 16LL, "Expected SectorCount 16, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 4, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 33LL, "Expected Vbn 33, got: %I64d\n", Vbn);
    ok(Lbn == 1185LL, "Expected Lbn 1185, got: %I64d\n", Lbn);
    ok(SectorCount == 32LL, "Expected SectorCount 32, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 5, &Vbn, &Lbn, &SectorCount);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Vbn == 65LL, "Expected Vbn 65, got: %I64d\n", Vbn);
    ok(Lbn == 1249LL, "Expected Lbn 1249, got: %I64d\n", Lbn);
    ok(SectorCount == 44LL, "Expected SectorCount 44, got: %I64d\n", SectorCount);

    Result = FsRtlGetNextLargeMcbEntry(&FirstMcb, 6, &Vbn, &Lbn, &SectorCount);
    ok(Result == FALSE, "Expected FALSE, got TRUE\n");

    Result = FsRtlLookupLargeMcbEntry(&FirstMcb, 1, &Lbn, &SectorCountFromLbn, NULL, NULL, NULL);
    ok(Result == TRUE, "Expected TRUE, got FALSE\n");
    ok(Lbn == 198657LL, "Expected Lbn 198657, got: %I64d\n", Lbn);
    ok(SectorCountFromLbn == 1LL, "Expected SectorCountFromLbn 108, got: %I64d\n", SectorCountFromLbn);

    FsRtlUninitializeLargeMcb(&SecondMcb);
    FsRtlUninitializeLargeMcb(&FirstMcb);
}