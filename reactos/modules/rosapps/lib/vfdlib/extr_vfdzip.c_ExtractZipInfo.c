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
typedef  int /*<<< orphan*/  zip_hdr ;
struct TYPE_3__ {scalar_t__ header_signature; scalar_t__ compression_method; int general_flags; int /*<<< orphan*/  uncompressed_size; } ;
typedef  TYPE_1__ ZIP_HEADER ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_INVALID_DATA ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int GetLastError () ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,TYPE_1__*,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemMessage (int) ; 
 int /*<<< orphan*/  VFDTRACE (int /*<<< orphan*/ ,char*) ; 
 int ZIP_FLAG_ENCRYPTED ; 
 scalar_t__ ZIP_LOCAL_SIGNATURE ; 
 scalar_t__ ZIP_METHOD_DEFLATED ; 

DWORD ExtractZipInfo(
	HANDLE			hFile,
	ULONG			*pSize)
{
	ZIP_HEADER		zip_hdr;
	DWORD			result;
	DWORD			ret;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) != 0) {
		ret = GetLastError();

		VFDTRACE(0,
			("SetFilePointer() - %s\n",
			SystemMessage(ret)));

		return ret;
	}

	if (!ReadFile(hFile, &zip_hdr, sizeof(zip_hdr), &result, NULL)) {
		ret = GetLastError();

		VFDTRACE(0,
			("ReadFile() - %s\n",
			SystemMessage(ret)));

		return ret;
	}

	if (result != sizeof(zip_hdr)							||
		zip_hdr.header_signature != ZIP_LOCAL_SIGNATURE		||
		zip_hdr.compression_method != ZIP_METHOD_DEFLATED	||
		(zip_hdr.general_flags & ZIP_FLAG_ENCRYPTED)) {

		VFDTRACE(0,
			("[VFD] Invalid ZIP file\n"));

		return ERROR_INVALID_DATA;
	}

	//	correct (and supported) ZIP header detected

	*pSize = zip_hdr.uncompressed_size;

	return ERROR_SUCCESS;
}