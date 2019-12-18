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
typedef  int NTSTATUS ;

/* Variables and functions */
#define  STATUS_ACCESS_DENIED 144 
#define  STATUS_BUFFER_OVERFLOW 143 
#define  STATUS_BUFFER_TOO_SMALL 142 
#define  STATUS_INFO_LENGTH_MISMATCH 141 
#define  STATUS_INSUFFICIENT_RESOURCES 140 
#define  STATUS_INVALID_HANDLE 139 
#define  STATUS_INVALID_PARAMETER 138 
#define  STATUS_NOT_IMPLEMENTED 137 
#define  STATUS_NOT_SUPPORTED 136 
#define  STATUS_NO_MEMORY 135 
#define  STATUS_OBJECT_NAME_INVALID 134 
#define  STATUS_OBJECT_NAME_NOT_FOUND 133 
#define  STATUS_OBJECT_PATH_INVALID 132 
#define  STATUS_OBJECT_TYPE_MISMATCH 131 
#define  STATUS_SHARING_VIOLATION 130 
#define  STATUS_SUCCESS 129 
#define  STATUS_UNSUCCESSFUL 128 
 int /*<<< orphan*/  static_sprintf (char*,char*,int) ; 

char* NtStatusError(NTSTATUS Status) {
	static char unknown[32];

	switch (Status) {
	case STATUS_SUCCESS:
		return "Operation Successful";
	case STATUS_UNSUCCESSFUL:
		return "Operation Failed";
	case STATUS_BUFFER_OVERFLOW:
		return "Buffer Overflow";
	case STATUS_NOT_IMPLEMENTED:
		return "Not Implemented";
	case STATUS_INFO_LENGTH_MISMATCH:
		return "Info Length Mismatch";
	case STATUS_INVALID_HANDLE:
		return "Invalid Handle.";
	case STATUS_INVALID_PARAMETER:
		return "Invalid Parameter";
	case STATUS_NO_MEMORY:
		return "Not Enough Quota";
	case STATUS_ACCESS_DENIED:
		return "Access Denied";
	case STATUS_BUFFER_TOO_SMALL:
		return "Buffer Too Small";
	case STATUS_OBJECT_TYPE_MISMATCH:
		return "Wrong Type";
	case STATUS_OBJECT_NAME_INVALID:
		return "Object Name Invalid";
	case STATUS_OBJECT_NAME_NOT_FOUND:
		return "Object Name not found";
	case STATUS_OBJECT_PATH_INVALID:
		return "Object Path Invalid";
	case STATUS_SHARING_VIOLATION:
		return "Sharing Violation";
	case STATUS_INSUFFICIENT_RESOURCES:
		return "Insufficient resources";
	case STATUS_NOT_SUPPORTED:
		return "Operation is not supported";
	default:
		static_sprintf(unknown, "Unknown error 0x%08lx", Status);
		return unknown;
	}
}