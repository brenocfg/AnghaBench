#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  dwPageSize; } ;
typedef  TYPE_1__ SYSTEM_INFO ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileMappingA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 int /*<<< orphan*/  FILE_MAP_ALL_ACCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 scalar_t__ MapViewOfFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PAGE_READWRITE ; 
 int SEC_RESERVE ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VirtualAlloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int VirtualTest()
{
   DWORD dwErr;
   SYSTEM_INFO si;
   HANDLE hMap;
   PBYTE pBufferStart;
   PCHAR pszFileName = "test.txt";
   ULONG dwMaxSize = strlen(pszFileName);

   DBG("Calling CreateFileMappingA\n");
   hMap = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL,
      PAGE_READWRITE | SEC_RESERVE, 0, dwMaxSize, pszFileName);
   if (!hMap)
   {
      DBG("CreateFileMappingA failed\n");
      return 1;
   }

   dwErr = GetLastError();
   DBG("Calling MapViewOfFile\n");
   pBufferStart = (BYTE *)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
   if (!pBufferStart)
   {
      DBG("MapViewOfFile failed\n");
      return 1;
   }

   GetSystemInfo(&si);

   if (dwErr == ERROR_ALREADY_EXISTS)
   {
      DBG("MapViewOfFile returned ERROR_ALREADY_EXISTS\n");
      DBG("This really shouldn't happen, but it's not fatal.\n");
      UnmapViewOfFile(pBufferStart);
      CloseHandle(hMap);
      return 1;
   }
   else
   {
      DBG("Calling VirtualAlloc\n");
      if (!VirtualAlloc(pBufferStart, si.dwPageSize, MEM_COMMIT, PAGE_READWRITE))
      {
         DBG("VirtualAlloc failed\n");
         UnmapViewOfFile(pBufferStart);
         CloseHandle(hMap);
         return 1;
      }
   }

   DBG("Hurray!\n");

   UnmapViewOfFile(pBufferStart);
   CloseHandle(hMap);

   return 0;
}