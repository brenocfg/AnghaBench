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
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int WIM_HAS_7Z_EXTRACT ; 
 int WIM_HAS_API_EXTRACT ; 
 int /*<<< orphan*/  WIM_HAS_EXTRACT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WimExtractCheck () ; 
 scalar_t__ WimExtractFile_7z (char const*,int,char const*,char const*) ; 
 scalar_t__ WimExtractFile_API (char const*,int,char const*,char const*) ; 
 int wim_flags ; 

BOOL WimExtractFile(const char* image, int index, const char* src, const char* dst)
{
	if ((wim_flags == 0) && (!WIM_HAS_EXTRACT(WimExtractCheck())))
		return FALSE;
	if ((image == NULL) || (src == NULL) || (dst == NULL))
		return FALSE;

	// Prefer 7-Zip as, unsurprisingly, it's faster than the Microsoft way,
	// but allow fallback if 7-Zip doesn't succeed
	return ( ((wim_flags & WIM_HAS_7Z_EXTRACT) && WimExtractFile_7z(image, index, src, dst))
		  || ((wim_flags & WIM_HAS_API_EXTRACT) && WimExtractFile_API(image, index, src, dst)) );
}