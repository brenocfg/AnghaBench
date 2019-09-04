#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hasError; int /*<<< orphan*/  isQuiet; int /*<<< orphan*/  isWritable; } ;
struct TYPE_4__ {TYPE_1__ file; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  THFile ;
typedef  TYPE_2__ THDiskFile ;

/* Variables and functions */
 int /*<<< orphan*/  THArgCheck (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  THError (char*,size_t,size_t) ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t THDiskFile_writeString(THFile *self, const char *str, size_t size)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  size_t nwrite;

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isWritable, 1, "attempt to write in a read-only file");

  nwrite = fwrite(str, 1, size, dfself->handle);
  if(nwrite != size)
  {
    dfself->file.hasError = 1;
    if(!dfself->file.isQuiet)
      THError("write error: wrote %zu blocks instead of %zu", nwrite, size);
  }

  return nwrite;
}