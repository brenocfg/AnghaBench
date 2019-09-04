#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
struct TYPE_23__ {scalar_t__ QuadPart; } ;
struct TYPE_22__ {scalar_t__ QuadPart; } ;
struct TYPE_27__ {scalar_t__ ProcessId; int /*<<< orphan*/  ThreadCount; int /*<<< orphan*/  HandleCount; int /*<<< orphan*/  BasePriority; int /*<<< orphan*/  NonPagedPoolUsagePages; int /*<<< orphan*/  PagedPoolUsagePages; int /*<<< orphan*/  VirtualMemorySizeBytes; void* PageFaultCountDelta; scalar_t__ PageFaultCount; void* WorkingSetSizeDelta; scalar_t__ WorkingSetSizeBytes; int /*<<< orphan*/  PeakWorkingSetSizeBytes; TYPE_3__ CPUTime; scalar_t__ CPUUsage; TYPE_2__ CreateTime; scalar_t__* ImageName; } ;
struct TYPE_25__ {scalar_t__ QuadPart; } ;
struct TYPE_24__ {scalar_t__ QuadPart; } ;
struct TYPE_21__ {int Length; scalar_t__ Buffer; } ;
struct TYPE_26__ {int /*<<< orphan*/  NumberOfThreads; int /*<<< orphan*/  HandleCount; int /*<<< orphan*/  BasePriority; int /*<<< orphan*/  QuotaNonPagedPoolUsage; int /*<<< orphan*/  QuotaPagedPoolUsage; int /*<<< orphan*/  VirtualSize; scalar_t__ PageFaultCount; scalar_t__ WorkingSetSize; int /*<<< orphan*/  PeakWorkingSetSize; TYPE_5__ KernelTime; TYPE_4__ UserTime; TYPE_2__ CreateTime; int /*<<< orphan*/  UniqueProcessId; TYPE_1__ ImageName; } ;
struct TYPE_20__ {int NumberOfProcessors; } ;
typedef  int /*<<< orphan*/  SYSTEM_TIMEOFDAY_INFORMATION ;
typedef  int /*<<< orphan*/  SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION ;
typedef  TYPE_6__* PSYSTEM_PROCESS_INFORMATION ;
typedef  TYPE_7__* PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION ;
typedef  TYPE_7__* PPERFDATA ;
typedef  int /*<<< orphan*/  PERFDATA ;
typedef  scalar_t__ LPBYTE ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ HandleToUlong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ NtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_7__*,int,int*) ; 
 int ProcessCount ; 
 int ProcessCountOld ; 
 int /*<<< orphan*/  PsaCaptureProcessesAndThreads (TYPE_6__**) ; 
 int /*<<< orphan*/  PsaFreeCapture (scalar_t__) ; 
 TYPE_6__* PsaWalkFirstProcess (TYPE_6__*) ; 
 TYPE_6__* PsaWalkNextProcess (TYPE_6__*) ; 
 TYPE_13__ SystemBasicInfo ; 
 int /*<<< orphan*/  SystemProcessorPerformanceInformation ; 
 scalar_t__ first ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 void* labs (scalar_t__) ; 
 int /*<<< orphan*/  lpIdleProcess ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* pPerfData ; 
 TYPE_7__* pPerfDataOld ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcsncpy (scalar_t__*,scalar_t__,int) ; 

void PerfDataRefresh()
{
	LONG							status;
	ULONG							ulSize;
	LPBYTE							pBuffer;
	ULONG							Idx, Idx2;
	PSYSTEM_PROCESS_INFORMATION		pSPI;
	PPERFDATA						pPDOld;
#ifdef EXTRA_INFO
	HANDLE							hProcess;
	HANDLE							hProcessToken;
	TCHAR							szTemp[MAX_PATH];
	DWORD							dwSize;
#endif
#ifdef TIMES
	LARGE_INTEGER 						liCurrentKernelTime;
	LARGE_INTEGER						liCurrentIdleTime;
	LARGE_INTEGER						liCurrentTime;
#endif
	PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION		SysProcessorTimeInfo;
	SYSTEM_TIMEOFDAY_INFORMATION				SysTimeInfo;

#ifdef TIMES
	// Get new system time
	status = NtQuerySystemInformation(SystemTimeInformation, &SysTimeInfo, sizeof(SysTimeInfo), 0);
	if (status != NO_ERROR)
		return;
#endif
	// Get processor information
	SysProcessorTimeInfo = (PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION)malloc(sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * SystemBasicInfo.NumberOfProcessors);
	status = NtQuerySystemInformation(SystemProcessorPerformanceInformation, SysProcessorTimeInfo, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * SystemBasicInfo.NumberOfProcessors, &ulSize);


	// Get process information
	PsaCaptureProcessesAndThreads((PSYSTEM_PROCESS_INFORMATION *)&pBuffer);

#ifdef TIMES
	liCurrentKernelTime.QuadPart = 0;
	liCurrentIdleTime.QuadPart = 0;
	for (Idx=0; Idx<SystemBasicInfo.NumberOfProcessors; Idx++) {
		liCurrentKernelTime.QuadPart += SysProcessorTimeInfo[Idx].KernelTime.QuadPart;
		liCurrentKernelTime.QuadPart += SysProcessorTimeInfo[Idx].DpcTime.QuadPart;
		liCurrentKernelTime.QuadPart += SysProcessorTimeInfo[Idx].InterruptTime.QuadPart;
		liCurrentIdleTime.QuadPart += SysProcessorTimeInfo[Idx].IdleTime.QuadPart;
	}

	// If it's a first call - skip idle time calcs
	if (liOldIdleTime.QuadPart != 0) {
		// CurrentValue = NewValue - OldValue
		liCurrentTime.QuadPart = liCurrentIdleTime.QuadPart - liOldIdleTime.QuadPart;
		dbIdleTime = Li2Double(liCurrentTime);
		liCurrentTime.QuadPart = liCurrentKernelTime.QuadPart - liOldKernelTime.QuadPart;
		dbKernelTime = Li2Double(liCurrentTime);
		liCurrentTime.QuadPart = SysTimeInfo.CurrentTime.QuadPart - liOldSystemTime.QuadPart;
	    	dbSystemTime = Li2Double(liCurrentTime);

		// CurrentCpuIdle = IdleTime / SystemTime
		dbIdleTime = dbIdleTime / dbSystemTime;
		dbKernelTime = dbKernelTime / dbSystemTime;

		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
		dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SystemBasicInfo.NumberOfProcessors;// + 0.5;
		dbKernelTime = 100.0 - dbKernelTime * 100.0 / (double)SystemBasicInfo.NumberOfProcessors;// + 0.5;
	}

	// Store new CPU's idle and system time
	liOldIdleTime = liCurrentIdleTime;
	liOldSystemTime = SysTimeInfo.CurrentTime;
	liOldKernelTime = liCurrentKernelTime;
#endif

	// Determine the process count
	// We loop through the data we got from PsaCaptureProcessesAndThreads
	// and count how many structures there are (until PsaWalkNextProcess
        // returns NULL)
	ProcessCountOld = ProcessCount;
	ProcessCount = 0;
        pSPI = PsaWalkFirstProcess((PSYSTEM_PROCESS_INFORMATION)pBuffer);
	while (pSPI) {
		ProcessCount++;
		pSPI = PsaWalkNextProcess(pSPI);
	}

	// Now alloc a new PERFDATA array and fill in the data
	if (pPerfDataOld) {
		free(pPerfDataOld);
	}
	pPerfDataOld = pPerfData;
	pPerfData = (PPERFDATA)malloc(sizeof(PERFDATA) * ProcessCount);
        pSPI = PsaWalkFirstProcess((PSYSTEM_PROCESS_INFORMATION)pBuffer);
	for (Idx=0; Idx<ProcessCount; Idx++) {
		// Get the old perf data for this process (if any)
		// so that we can establish delta values
		pPDOld = NULL;
		for (Idx2=0; Idx2<ProcessCountOld; Idx2++) {
			if (pPerfDataOld[Idx2].ProcessId == HandleToUlong(pSPI->UniqueProcessId) &&
			    /* check also for the creation time, a new process may have an id of an old one */
			    pPerfDataOld[Idx2].CreateTime.QuadPart == pSPI->CreateTime.QuadPart) {
				pPDOld = &pPerfDataOld[Idx2];
				break;
			}
		}

		// Clear out process perf data structure
		memset(&pPerfData[Idx], 0, sizeof(PERFDATA));

		if (pSPI->ImageName.Buffer) {
			wcsncpy(pPerfData[Idx].ImageName, pSPI->ImageName.Buffer, pSPI->ImageName.Length / sizeof(WCHAR));
                        pPerfData[Idx].ImageName[pSPI->ImageName.Length / sizeof(WCHAR)] = 0;
		}
		else
		{
#ifdef _UNICODE
			wcscpy(pPerfData[Idx].ImageName, lpIdleProcess);
#else
			MultiByteToWideChar(CP_ACP, 0, lpIdleProcess, strlen(lpIdleProcess), pPerfData[Idx].ImageName, MAX_PATH);
#endif
		}

		pPerfData[Idx].ProcessId = HandleToUlong(pSPI->UniqueProcessId);
		pPerfData[Idx].CreateTime = pSPI->CreateTime;

		if (pPDOld)	{
#ifdef TIMES
			double	CurTime = Li2Double(pSPI->KernelTime) + Li2Double(pSPI->UserTime);
			double	OldTime = Li2Double(pPDOld->KernelTime) + Li2Double(pPDOld->UserTime);
			double	CpuTime = (CurTime - OldTime) / dbSystemTime;
			CpuTime = CpuTime * 100.0 / (double)SystemBasicInfo.NumberOfProcessors; // + 0.5;

			pPerfData[Idx].CPUUsage = (ULONG)CpuTime;
#else
			pPerfData[Idx].CPUUsage = 0;
#endif
		}

		pPerfData[Idx].CPUTime.QuadPart = pSPI->UserTime.QuadPart + pSPI->KernelTime.QuadPart;
		pPerfData[Idx].WorkingSetSizeBytes = pSPI->WorkingSetSize;
		pPerfData[Idx].PeakWorkingSetSizeBytes = pSPI->PeakWorkingSetSize;
		if (pPDOld)
			pPerfData[Idx].WorkingSetSizeDelta = labs((LONG)pSPI->WorkingSetSize - (LONG)pPDOld->WorkingSetSizeBytes);
		else
			pPerfData[Idx].WorkingSetSizeDelta = 0;
		pPerfData[Idx].PageFaultCount = pSPI->PageFaultCount;
		if (pPDOld)
			pPerfData[Idx].PageFaultCountDelta = labs((LONG)pSPI->PageFaultCount - (LONG)pPDOld->PageFaultCount);
		else
			pPerfData[Idx].PageFaultCountDelta = 0;
		pPerfData[Idx].VirtualMemorySizeBytes = pSPI->VirtualSize;
		pPerfData[Idx].PagedPoolUsagePages = pSPI->QuotaPagedPoolUsage;
		pPerfData[Idx].NonPagedPoolUsagePages = pSPI->QuotaNonPagedPoolUsage;
		pPerfData[Idx].BasePriority = pSPI->BasePriority;
		pPerfData[Idx].HandleCount = pSPI->HandleCount;
		pPerfData[Idx].ThreadCount = pSPI->NumberOfThreads;
		//pPerfData[Idx].SessionId = pSPI->SessionId;

#ifdef EXTRA_INFO
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, (DWORD)pSPI->UniqueProcessId);
		if (hProcess) {
			if (OpenProcessToken(hProcess, TOKEN_QUERY|TOKEN_DUPLICATE|TOKEN_IMPERSONATE, &hProcessToken)) {
				ImpersonateLoggedOnUser(hProcessToken);
				memset(szTemp, 0, sizeof(TCHAR[MAX_PATH]));
				dwSize = MAX_PATH;
				GetUserName(szTemp, &dwSize);
#ifndef UNICODE
				MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTemp, -1, pPerfData[Idx].UserName, MAX_PATH);
#endif
				RevertToSelf();
				CloseHandle(hProcessToken);
			}
			CloseHandle(hProcess);
		}
#endif
#ifdef TIMES
		pPerfData[Idx].UserTime.QuadPart = pSPI->UserTime.QuadPart;
		pPerfData[Idx].KernelTime.QuadPart = pSPI->KernelTime.QuadPart;
#endif
		pSPI = PsaWalkNextProcess(pSPI);
	}
	PsaFreeCapture(pBuffer);

	free(SysProcessorTimeInfo);
	if (ProcessCount != ProcessCountOld)
		first = 0;
}