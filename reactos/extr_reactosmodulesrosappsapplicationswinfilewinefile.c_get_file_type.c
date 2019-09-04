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
typedef  enum FILE_TYPE { ____Placeholder_FILE_TYPE } FILE_TYPE ;
typedef  scalar_t__ LPCWSTR ;

/* Variables and functions */
 int FT_DOCUMENT ; 
 int FT_EXECUTABLE ; 
 int FT_OTHER ; 
 scalar_t__ is_exe_file (scalar_t__) ; 
 scalar_t__ is_registered_type (scalar_t__) ; 
 scalar_t__ sEmpty ; 
 scalar_t__ strrchrW (scalar_t__,char) ; 

__attribute__((used)) static enum FILE_TYPE get_file_type(LPCWSTR filename)
{
	LPCWSTR ext = strrchrW(filename, '.');
	if (!ext)
		ext = sEmpty;

	if (is_exe_file(ext))
		return FT_EXECUTABLE;
	else if (is_registered_type(ext))
		return FT_DOCUMENT;
	else
		return FT_OTHER;
}