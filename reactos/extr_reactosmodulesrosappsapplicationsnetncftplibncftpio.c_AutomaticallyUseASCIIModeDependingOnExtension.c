#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * asciiFilenameExtensions; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 scalar_t__ FilenameExtensionIndicatesASCII (char const* const,int /*<<< orphan*/ *) ; 
 int kTypeAscii ; 
 int kTypeBinary ; 

__attribute__((used)) static void
AutomaticallyUseASCIIModeDependingOnExtension(const FTPCIPtr cip, const char *const pathName, int *const xtype)
{
	if ((*xtype == kTypeBinary) && (cip->asciiFilenameExtensions != NULL)) {
		if (FilenameExtensionIndicatesASCII(pathName, cip->asciiFilenameExtensions)) {
			/* Matched -- send this file in ASCII mode
			 * instead of binary since it's extension
			 * appears to be that of a text file.
			 */
			*xtype = kTypeAscii;
		}
	}
}