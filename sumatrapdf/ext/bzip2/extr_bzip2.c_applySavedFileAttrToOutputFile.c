#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  IntNative ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_IF_NOT_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fchmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fchown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fileMetaInfo ; 

__attribute__((used)) static 
void applySavedFileAttrToOutputFile ( IntNative fd )
{
#  if BZ_UNIX
   IntNative retVal;

   retVal = fchmod ( fd, fileMetaInfo.st_mode );
   ERROR_IF_NOT_ZERO ( retVal );

   (void) fchown ( fd, fileMetaInfo.st_uid, fileMetaInfo.st_gid );
   /* chown() will in many cases return with EPERM, which can
      be safely ignored.
   */
#  endif
}