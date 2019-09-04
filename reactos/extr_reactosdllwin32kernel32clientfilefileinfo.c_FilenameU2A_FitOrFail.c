#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_4__ {scalar_t__ Length; scalar_t__ MaximumLength; scalar_t__ Buffer; } ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  scalar_t__ LPSTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ ANSI_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAX_PATH ; 
 scalar_t__ RtlUnicodeStringToAnsiSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlUnicodeStringToAnsiString (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlUnicodeStringToOemSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlUnicodeStringToOemString (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bIsFileApiAnsi ; 

DWORD
FilenameU2A_FitOrFail(
   LPSTR  DestA,
   INT destLen, /* buffer size in TCHARS incl. nullchar */
   PUNICODE_STRING SourceU
   )
{
   DWORD ret;

   /* destLen should never exceed MAX_PATH */
   if (destLen > MAX_PATH) destLen = MAX_PATH;

   ret = bIsFileApiAnsi? RtlUnicodeStringToAnsiSize(SourceU) : RtlUnicodeStringToOemSize(SourceU);
   /* ret incl. nullchar */

   if (DestA && (INT)ret <= destLen)
   {
      ANSI_STRING str;

      str.Buffer = DestA;
      str.MaximumLength = (USHORT)destLen;


      if (bIsFileApiAnsi)
         RtlUnicodeStringToAnsiString(&str, SourceU, FALSE );
      else
         RtlUnicodeStringToOemString(&str, SourceU, FALSE );

      ret = str.Length;  /* SUCCESS: length without terminating 0 */
   }

   return ret;
}