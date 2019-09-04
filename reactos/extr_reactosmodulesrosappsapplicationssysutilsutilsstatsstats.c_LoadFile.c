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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 scalar_t__ FileHandle ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
LoadFile(LPTSTR FileName)
{
  LONG FileSize;

  FileHandle = CreateFile (FileName, // Create this file
    GENERIC_READ,                    // Open for reading
    0,                               // No sharing
    NULL,                            // No security
    OPEN_EXISTING,                   // Open the file
    FILE_ATTRIBUTE_NORMAL,           // Normal file
    NULL);                           // No attribute template
  if (FileHandle == INVALID_HANDLE_VALUE)
    return FALSE;

  FileSize = GetFileSize (FileHandle, NULL);
  if (FileSize <= 0)
  {
    CloseHandle (FileHandle);
    return FALSE;
  }

  return TRUE;
}