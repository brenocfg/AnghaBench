#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buf; int errNo; int /*<<< orphan*/  bufSize; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrMallocFailed ; 
 int kNoErr ; 

__attribute__((used)) static int
FTPAllocateHost(const FTPCIPtr cip)
{
	char *buf;

	/* Requires the cip->bufSize field set,
	 * and the cip->buf cleared if the
	 * buffer is not allocated.
	 */
	if (cip->buf == NULL) {
		buf = (char *) calloc((size_t) 1, cip->bufSize);
		if (buf == NULL) {
			Error(cip, kDontPerror, "Malloc failed.\n");
			cip->errNo = kErrMallocFailed;
			return (kErrMallocFailed);
		}
		cip->buf = buf;
	}
	return (kNoErr);
}