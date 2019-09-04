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
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ Get7ZipPath () ; 
 int /*<<< orphan*/  PF_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIMApplyImage ; 
 int /*<<< orphan*/  WIMCloseHandle ; 
 int /*<<< orphan*/  WIMCreateFile ; 
 int /*<<< orphan*/  WIMExtractImagePath ; 
 int /*<<< orphan*/  WIMGetImageInformation ; 
 int /*<<< orphan*/  WIMLoadImage ; 
 int /*<<< orphan*/  WIMRegisterMessageCallback ; 
 int /*<<< orphan*/  WIMSetTemporaryPath ; 
 int /*<<< orphan*/  WIMUnregisterMessageCallback ; 
 int WIM_HAS_7Z_EXTRACT ; 
 int WIM_HAS_API_APPLY ; 
 int WIM_HAS_API_EXTRACT ; 
 int WIM_HAS_EXTRACT (int) ; 
 int /*<<< orphan*/  Wimgapi ; 
 scalar_t__ pfWIMApplyImage ; 
 scalar_t__ pfWIMCloseHandle ; 
 scalar_t__ pfWIMCreateFile ; 
 scalar_t__ pfWIMExtractImagePath ; 
 scalar_t__ pfWIMLoadImage ; 
 scalar_t__ pfWIMRegisterMessageCallback ; 
 scalar_t__ pfWIMSetTemporaryPath ; 
 scalar_t__ pfWIMUnregisterMessageCallback ; 
 int /*<<< orphan*/  uprintf (char*,char*,...) ; 
 int wim_flags ; 

uint8_t WimExtractCheck(void)
{
	PF_INIT(WIMCreateFile, Wimgapi);
	PF_INIT(WIMSetTemporaryPath, Wimgapi);
	PF_INIT(WIMLoadImage, Wimgapi);
	PF_INIT(WIMApplyImage, Wimgapi);
	PF_INIT(WIMExtractImagePath, Wimgapi);
	PF_INIT(WIMGetImageInformation, Wimgapi);
	PF_INIT(WIMRegisterMessageCallback, Wimgapi);
	PF_INIT(WIMUnregisterMessageCallback, Wimgapi);
	PF_INIT(WIMCloseHandle, Wimgapi);

	if (pfWIMCreateFile && pfWIMSetTemporaryPath && pfWIMLoadImage && pfWIMExtractImagePath && pfWIMCloseHandle)
		wim_flags |= WIM_HAS_API_EXTRACT;
	if (Get7ZipPath())
		wim_flags |= WIM_HAS_7Z_EXTRACT;
	if ((wim_flags & WIM_HAS_API_EXTRACT) && pfWIMApplyImage && pfWIMRegisterMessageCallback && pfWIMUnregisterMessageCallback)
		wim_flags |= WIM_HAS_API_APPLY;

	uprintf("WIM extraction method(s) supported: %s%s%s", (wim_flags & WIM_HAS_7Z_EXTRACT)?"7-Zip":
		((wim_flags & WIM_HAS_API_EXTRACT)?"":"NONE"),
		(WIM_HAS_EXTRACT(wim_flags) == (WIM_HAS_API_EXTRACT|WIM_HAS_7Z_EXTRACT))?", ":
		"", (wim_flags & WIM_HAS_API_EXTRACT)?"wimgapi.dll":"");
	uprintf("WIM apply method supported: %s", (wim_flags & WIM_HAS_API_APPLY)?"wimgapi.dll":"NONE");
	return wim_flags;
}