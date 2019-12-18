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
struct TYPE_4__ {char type; int /*<<< orphan*/  mdtm; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__* FileInfoPtr ;
typedef  int /*<<< orphan*/  FileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  kModTimeUnknown ; 
 int /*<<< orphan*/  kSizeUnknown ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
InitFileInfo(FileInfoPtr fip)
{
	(void) memset(fip, 0, sizeof(FileInfo));
	fip->type = '-';
	fip->size = kSizeUnknown;
	fip->mdtm = kModTimeUnknown;
}