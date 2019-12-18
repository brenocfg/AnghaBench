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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  __int64 ;
struct TYPE_3__ {int hasError; int /*<<< orphan*/  isQuiet; } ;
struct TYPE_4__ {TYPE_1__ file; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  THFile ;
typedef  TYPE_2__ THDiskFile ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ LLONG_MAX ; 
 scalar_t__ LONG_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  THArgCheck (int,int,char*) ; 
 int /*<<< orphan*/  THError (char*,size_t) ; 
 scalar_t__ _fseeki64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void THDiskFile_seek(THFile *self, size_t position)
{
  THDiskFile *dfself = (THDiskFile*)(self);

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");

#if defined(_WIN64)
  THArgCheck(position <= (size_t)INT64_MAX, 2, "position must be smaller than INT64_MAX");
  if(_fseeki64(dfself->handle, (__int64)position, SEEK_SET) < 0)
#elif defined(_WIN32)
  THArgCheck(position <= (size_t)LONG_MAX, 2, "position must be smaller than LONG_MAX");
  if(fseek(dfself->handle, (long)position, SEEK_SET) < 0)
#else
  THArgCheck(position <= (size_t)LLONG_MAX, 2, "position must be smaller than LLONG_MAX");
  if(fseeko(dfself->handle, (off_t)position, SEEK_SET) < 0)
#endif
  {
    dfself->file.hasError = 1;
    if(!dfself->file.isQuiet)
      THError("unable to seek to position %zu", position);
  }
}