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
typedef  int /*<<< orphan*/ * PTSTR ;
typedef  int /*<<< orphan*/  PDWORD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ SetupCopyOEMInfW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wDestinationInfFileName ; 
 int /*<<< orphan*/  wOEMSourceMediaLocation ; 
 int /*<<< orphan*/  wSourceInfFileName ; 
 int /*<<< orphan*/  walloc (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 

__attribute__((used)) static __inline BOOL SetupCopyOEMInfU(const char* SourceInfFileName, const char* OEMSourceMediaLocation, DWORD OEMSourceMediaType,
									  DWORD CopyStyle, char* DestinationInfFileName, DWORD DestinationInfFileNameSize,
									  PDWORD RequiredSize, PTSTR DestinationInfFileNameComponent)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(SourceInfFileName);
	wconvert(OEMSourceMediaLocation);
	// coverity[returned_null]
	walloc(DestinationInfFileName, DestinationInfFileNameSize);

	// DestinationInfFileNameComponent is not supported
	if (DestinationInfFileNameComponent != NULL) goto out;

	ret = SetupCopyOEMInfW(wSourceInfFileName, wOEMSourceMediaLocation, OEMSourceMediaType, CopyStyle,
		wDestinationInfFileName, DestinationInfFileNameSize, RequiredSize, NULL);
	err = GetLastError();
	if ((ret != FALSE) && ((ret = wchar_to_utf8_no_alloc(wDestinationInfFileName, DestinationInfFileName, DestinationInfFileNameSize)) == 0)) {
		err = GetLastError();
	}
out:
	wfree(SourceInfFileName);
	wfree(OEMSourceMediaLocation);
	wfree(DestinationInfFileName);
	SetLastError(err);
	return ret;
}