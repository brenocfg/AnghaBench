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
struct TYPE_3__ {int nLength; int /*<<< orphan*/ * lpSecurityDescriptor; void* bInheritHandle; } ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileU (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetSID () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_215 ; 
 int /*<<< orphan*/  MSG_216 ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PrintInfoDebug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* ReadFile (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 scalar_t__ SetSecurityDescriptorOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 void* WriteFile (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

BOOL FileIO(BOOL save, char* path, char** buffer, DWORD* size)
{
	SECURITY_ATTRIBUTES s_attr, *sa = NULL;
	SECURITY_DESCRIPTOR s_desc;
	PSID sid = NULL;
	HANDLE handle;
	BOOL r;
	BOOL ret = FALSE;

	// Change the owner from admin to regular user
	sid = GetSID();
	if ( (sid != NULL)
	  && InitializeSecurityDescriptor(&s_desc, SECURITY_DESCRIPTOR_REVISION)
	  && SetSecurityDescriptorOwner(&s_desc, sid, FALSE) ) {
		s_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
		s_attr.bInheritHandle = FALSE;
		s_attr.lpSecurityDescriptor = &s_desc;
		sa = &s_attr;
	} else {
		uprintf("Could not set security descriptor: %s\n", WindowsErrorString());
	}

	if (!save) {
		*buffer = NULL;
	}
	handle = CreateFileU(path, save?GENERIC_WRITE:GENERIC_READ, FILE_SHARE_READ,
		sa, save?CREATE_ALWAYS:OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		uprintf("Could not %s file '%s'\n", save?"create":"open", path);
		goto out;
	}

	if (save) {
		r = WriteFile(handle, *buffer, *size, size, NULL);
	} else {
		*size = GetFileSize(handle, NULL);
		*buffer = (char*)malloc(*size);
		if (*buffer == NULL) {
			uprintf("Could not allocate buffer for reading file\n");
			goto out;
		}
		r = ReadFile(handle, *buffer, *size, size, NULL);
	}

	if (!r) {
		uprintf("I/O Error: %s\n", WindowsErrorString());
		goto out;
	}

	PrintInfoDebug(0, save?MSG_216:MSG_215, path);
	ret = TRUE;

out:
	CloseHandle(handle);
	if (!ret) {
		// Only leave a buffer allocated if successful
		*size = 0;
		if (!save) {
			safe_free(*buffer);
		}
	}
	return ret;
}