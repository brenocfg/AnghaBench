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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pCompareStringEx ; 
 void* pCompareStringOrdinal ; 
 void* pEnumLanguageGroupLocalesA ; 
 void* pEnumSystemGeoID ; 
 void* pEnumSystemLanguageGroupsA ; 
 void* pEnumSystemLocalesEx ; 
 void* pEnumUILanguagesA ; 
 void* pFoldStringA ; 
 void* pFoldStringW ; 
 void* pGetDateFormatEx ; 
 void* pGetGeoInfoA ; 
 void* pGetGeoInfoW ; 
 void* pGetLocaleInfoEx ; 
 void* pGetNumberFormatEx ; 
 void* pGetSystemPreferredUILanguages ; 
 void* pGetThreadPreferredUILanguages ; 
 void* pGetTimeFormatEx ; 
 void* pGetUserPreferredUILanguages ; 
 void* pIdnToAscii ; 
 void* pIdnToNameprepUnicode ; 
 void* pIdnToUnicode ; 
 void* pIsValidLanguageGroup ; 
 void* pIsValidLocaleName ; 
 void* pLCIDToLocaleName ; 
 void* pLCMapStringEx ; 
 void* pLocaleNameToLCID ; 
 void* pRtlUpcaseUnicodeChar ; 

__attribute__((used)) static void InitFunctionPointers(void)
{
  HMODULE mod = GetModuleHandleA("kernel32");

#define X(f) p##f = (void*)GetProcAddress(mod, #f)
  X(GetTimeFormatEx);
  X(GetDateFormatEx);
  X(EnumSystemLanguageGroupsA);
  X(EnumLanguageGroupLocalesA);
  X(LocaleNameToLCID);
  X(LCIDToLocaleName);
  X(LCMapStringEx);
  X(FoldStringA);
  X(FoldStringW);
  X(IsValidLanguageGroup);
  X(EnumUILanguagesA);
  X(EnumSystemLocalesEx);
  X(IdnToNameprepUnicode);
  X(IdnToAscii);
  X(IdnToUnicode);
  X(GetLocaleInfoEx);
  X(IsValidLocaleName);
  X(CompareStringOrdinal);
  X(CompareStringEx);
  X(GetGeoInfoA);
  X(GetGeoInfoW);
  X(EnumSystemGeoID);
  X(GetSystemPreferredUILanguages);
  X(GetThreadPreferredUILanguages);
  X(GetUserPreferredUILanguages);
  X(GetNumberFormatEx);

  mod = GetModuleHandleA("ntdll");
  X(RtlUpcaseUnicodeChar);
#undef X
}