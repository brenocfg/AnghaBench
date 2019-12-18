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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _wcsnicmp (int*,int const*,scalar_t__) ; 
 scalar_t__ wcslen (int const*) ; 
 scalar_t__ wcsspn (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wspace ; 

__attribute__((used)) static wchar_t* get_token_data_line(const wchar_t* wtoken, wchar_t* wline)
{
	size_t i, r;
	BOOLEAN quoteth = FALSE;
	BOOLEAN xml = FALSE;

	if ((wtoken == NULL) || (wline == NULL) || (wline[0] == 0))
		return NULL;

	i = 0;

	// Skip leading spaces and opening '<'
	i += wcsspn(&wline[i], wspace);
	if (wline[i] == L'<')
		i++;
	i += wcsspn(&wline[i], wspace);

	// Our token should begin a line
	if (_wcsnicmp(&wline[i], wtoken, wcslen(wtoken)) != 0)
		return NULL;

	// Token was found, move past token
	i += wcslen(wtoken);

	// Skip spaces
	i += wcsspn(&wline[i], wspace);

	// Check for '=' or '>' sign
	if (wline[i] == L'>')
		xml = TRUE;
	else if (wline[i] != L'=')
		return NULL;
	i++;

	// Skip spaces
	i += wcsspn(&wline[i], wspace);

	// eliminate leading quote, if it exists
	if (wline[i] == L'"') {
		quoteth = TRUE;
		i++;
	}

	// Keep the starting pos of our data
	r = i;

	// locate end of string or quote
	while ( (wline[i] != 0) && (((wline[i] != L'"') && (wline[i] != L'<')) || ((wline[i] == L'"') && (!quoteth)) || ((wline[i] == L'<') && (!xml))) )
		i++;
	wline[i--] = 0;

	// Eliminate trailing EOL characters
	while ((i>=r) && ((wline[i] == L'\r') || (wline[i] == L'\n')))
		wline[i--] = 0;

	return (wline[r] == 0)?NULL:&wline[r];
}