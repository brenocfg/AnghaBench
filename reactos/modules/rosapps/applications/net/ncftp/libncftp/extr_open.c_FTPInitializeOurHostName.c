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
struct TYPE_3__ {scalar_t__ htried; int /*<<< orphan*/  ourHostName; int /*<<< orphan*/  hresult; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__* FTPLIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  GetOurHostName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
FTPInitializeOurHostName(const FTPLIPtr lip)
{
	if (lip == NULL)
		return;
	if (strcmp(lip->magic, kLibraryMagic))
		return;

	if (lip->htried == 0) {
		(void) memset(lip->ourHostName, 0, sizeof(lip->ourHostName));
		lip->hresult = GetOurHostName(lip->ourHostName, sizeof(lip->ourHostName));
	}
	lip->htried++;
}