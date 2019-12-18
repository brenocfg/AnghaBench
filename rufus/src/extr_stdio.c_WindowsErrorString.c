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
typedef  int /*<<< orphan*/  err_string ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ FACILITY_ITF ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 size_t FormatMessageU (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *) ; 
 size_t GetLastError () ; 
 int /*<<< orphan*/ * GetVdsError (size_t) ; 
 int /*<<< orphan*/  HRESULT_CODE (size_t) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SCODE_FACILITY (size_t) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SetLastError (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,size_t,...) ; 
 scalar_t__ strlen (char*) ; 

const char *WindowsErrorString(void)
{
	static char err_string[256] = { 0 };

	DWORD size, presize;
	DWORD error_code, format_error;

	error_code = GetLastError();
	// Check for VDS error codes
	if ((SCODE_FACILITY(error_code) == FACILITY_ITF) && (GetVdsError(error_code) != NULL)) {
		static_sprintf(err_string, "[0x%08lX] %s", error_code, GetVdsError(error_code));
		return err_string;
	}

	static_sprintf(err_string, "[0x%08lX] ", error_code);
	presize = (DWORD)strlen(err_string);

	size = FormatMessageU(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, HRESULT_CODE(error_code),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), &err_string[presize],
		sizeof(err_string)-(DWORD)strlen(err_string), NULL);
	if (size == 0) {
		format_error = GetLastError();
		if ((format_error) && (format_error != 0x13D))		// 0x13D, decode error, is returned for unknown codes
			static_sprintf(err_string, "Windows error code 0x%08lX (FormatMessage error code 0x%08lX)",
				error_code, format_error);
		else
			static_sprintf(err_string, "Unknown error 0x%08lX", error_code);
	} else {
		// Microsoft may suffix CRLF to error messages, which we need to remove...
		assert(presize > 2);
		size += presize - 2;
		// Cannot underflow if the above assert passed since our first char is neither of the following
		while ((err_string[size] == 0x0D) || (err_string[size] == 0x0A) || (err_string[size] == 0x20))
			err_string[size--] = 0;
	}

	SetLastError(error_code);	// Make sure we don't change the errorcode on exit
	return err_string;
}