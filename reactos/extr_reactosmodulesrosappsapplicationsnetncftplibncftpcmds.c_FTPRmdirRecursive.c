#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* const buf; void* errNo; int /*<<< orphan*/  bufSize; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int FTPChdir (TYPE_1__* const,char const* const) ; 
 int /*<<< orphan*/  FTPGetCWD (TYPE_1__* const,char const* const,int /*<<< orphan*/ ) ; 
 int FTPRmdir (TYPE_1__* const,char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FTPRmdirRecursiveL2 (TYPE_1__* const) ; 
 void* kErrCannotGoToPrevDir ; 
 int /*<<< orphan*/  kGlobNo ; 
 int kNoErr ; 
 int /*<<< orphan*/  kRecursiveNo ; 

__attribute__((used)) static int
FTPRmdirRecursive(const FTPCIPtr cip, const char *const dir)
{
	int result, result2;

	/* Preserve old working directory. */
	(void) FTPGetCWD(cip, cip->buf, cip->bufSize);

	result = FTPChdir(cip, dir);
	if (result != kNoErr) {
		return (result);
	}

	result = FTPRmdirRecursiveL2(cip);

	if (FTPChdir(cip, cip->buf) != kNoErr) {
		/* Could not cd back to the original user directory -- bad. */
		if (result != kNoErr) {
			result = kErrCannotGoToPrevDir;
			cip->errNo = kErrCannotGoToPrevDir;
		}
		return (result);
	}

	/* Now rmdir the last node, the root of the tree
	 * we just went through.
	 */
	result2 = FTPRmdir(cip, dir, kRecursiveNo, kGlobNo);
	if ((result2 != kNoErr) && (result == kNoErr))
		result = result2;

	return (result);
}