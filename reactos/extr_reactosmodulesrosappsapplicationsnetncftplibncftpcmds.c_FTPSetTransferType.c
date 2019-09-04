#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int curTransferType; int errNo; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*,int) ; 
 int FTPCmd (TYPE_1__* const,char*,int) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrBadTransferType ; 
 void* kErrTYPEFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
#define  kTypeAscii 130 
#define  kTypeBinary 129 
#define  kTypeEbcdic 128 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
FTPSetTransferType(const FTPCIPtr cip, int type)
{
	int result;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if (cip->curTransferType != type) {
		switch (type) {
			case kTypeAscii:
			case kTypeBinary:
			case kTypeEbcdic:
				break;
			case 'i':
			case 'b':
			case 'B':
				type = kTypeBinary;
				break;
			case 'e':
				type = kTypeEbcdic;
				break;
			case 'a':
				type = kTypeAscii;
				break;
			default:
				/* Yeah, we don't support Tenex.  Who cares? */
				Error(cip, kDontPerror, "Bad transfer type [%c].\n", type);
				cip->errNo = kErrBadTransferType;
				return (kErrBadTransferType);
		}
		result = FTPCmd(cip, "TYPE %c", type);
		if (result != 2) {
			result = kErrTYPEFailed;
			cip->errNo = kErrTYPEFailed;
			return (result);
		}
		cip->curTransferType = type;
	}
	return (kNoErr);
}