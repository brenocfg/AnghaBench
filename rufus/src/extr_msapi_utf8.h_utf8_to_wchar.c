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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  sfree (int /*<<< orphan*/ *) ; 
 int utf8_to_wchar_no_alloc (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline wchar_t* utf8_to_wchar(const char* str)
{
	int size = 0;
	wchar_t* wstr = NULL;

	if (str == NULL)
		return NULL;

	// Convert the empty string too
	if (str[0] == 0)
		return calloc(1, sizeof(wchar_t));

	// Find out the size we need to allocate for our converted string
	size = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	if (size <= 1)	// An empty string would be size 1
		return NULL;

	if ((wstr = (wchar_t*)calloc(size, sizeof(wchar_t))) == NULL)
		return NULL;

	if (utf8_to_wchar_no_alloc(str, wstr, size) != size) {
		sfree(wstr);
		return NULL;
	}
	return wstr;
}