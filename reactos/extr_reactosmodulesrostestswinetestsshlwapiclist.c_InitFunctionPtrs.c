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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SHLWAPI_hshlwapi ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 void* pSHLWAPI_166 ; 
 void* pSHLWAPI_17 ; 
 void* pSHLWAPI_18 ; 
 void* pSHLWAPI_184 ; 
 void* pSHLWAPI_19 ; 
 void* pSHLWAPI_20 ; 
 void* pSHLWAPI_21 ; 
 void* pSHLWAPI_212 ; 
 void* pSHLWAPI_213 ; 
 void* pSHLWAPI_214 ; 
 void* pSHLWAPI_22 ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL InitFunctionPtrs(void)
{
  SHLWAPI_hshlwapi = GetModuleHandleA("shlwapi.dll");

  /* SHCreateStreamOnFileEx was introduced in shlwapi v6.0 */
  if(!GetProcAddress(SHLWAPI_hshlwapi, "SHCreateStreamOnFileEx")){
      win_skip("Too old shlwapi version\n");
      return FALSE;
  }

  pSHLWAPI_17 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)17);
  ok(pSHLWAPI_17 != 0, "No Ordinal 17\n");
  pSHLWAPI_18 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)18);
  ok(pSHLWAPI_18 != 0, "No Ordinal 18\n");
  pSHLWAPI_19 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)19);
  ok(pSHLWAPI_19 != 0, "No Ordinal 19\n");
  pSHLWAPI_20 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)20);
  ok(pSHLWAPI_20 != 0, "No Ordinal 20\n");
  pSHLWAPI_21 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)21);
  ok(pSHLWAPI_21 != 0, "No Ordinal 21\n");
  pSHLWAPI_22 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)22);
  ok(pSHLWAPI_22 != 0, "No Ordinal 22\n");
  pSHLWAPI_166 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)166);
  ok(pSHLWAPI_166 != 0, "No Ordinal 166\n");
  pSHLWAPI_184 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)184);
  ok(pSHLWAPI_184 != 0, "No Ordinal 184\n");
  pSHLWAPI_212 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)212);
  ok(pSHLWAPI_212 != 0, "No Ordinal 212\n");
  pSHLWAPI_213 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)213);
  ok(pSHLWAPI_213 != 0, "No Ordinal 213\n");
  pSHLWAPI_214 = (void *)GetProcAddress( SHLWAPI_hshlwapi, (LPSTR)214);
  ok(pSHLWAPI_214 != 0, "No Ordinal 214\n");

  return TRUE;
}