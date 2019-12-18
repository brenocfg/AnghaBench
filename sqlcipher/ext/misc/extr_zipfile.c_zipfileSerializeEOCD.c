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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  iOffset; int /*<<< orphan*/  nSize; int /*<<< orphan*/  nEntryTotal; int /*<<< orphan*/  nEntry; int /*<<< orphan*/  iFirstDisk; int /*<<< orphan*/  iDisk; } ;
typedef  TYPE_1__ ZipfileEOCD ;

/* Variables and functions */
 int /*<<< orphan*/  ZIPFILE_SIGNATURE_EOCD ; 
 int /*<<< orphan*/  zipfileWrite16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zipfileWrite32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zipfileSerializeEOCD(ZipfileEOCD *p, u8 *aBuf){
  u8 *a = aBuf;
  zipfileWrite32(a, ZIPFILE_SIGNATURE_EOCD);
  zipfileWrite16(a, p->iDisk);
  zipfileWrite16(a, p->iFirstDisk);
  zipfileWrite16(a, p->nEntry);
  zipfileWrite16(a, p->nEntryTotal);
  zipfileWrite32(a, p->nSize);
  zipfileWrite32(a, p->iOffset);
  zipfileWrite16(a, 0);        /* Size of trailing comment in bytes*/

  return a-aBuf;
}