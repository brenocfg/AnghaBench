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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  szPathName; } ;
typedef  TYPE_1__ OFSTRUCT ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  LZClose (scalar_t__) ; 
 scalar_t__ LZOpenFileW (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_DELETE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void delete_fileW(WCHAR *fnameW)
{
  INT file;
  OFSTRUCT ofs;
  DWORD retval;

  file = LZOpenFileW(fnameW, &ofs, OF_DELETE);
  ok(file >= 0, "LZOpenFileW failed on delete\n");
  LZClose(file);
  retval = GetFileAttributesW(fnameW);
  ok(retval == INVALID_FILE_ATTRIBUTES, "GetFileAttributesW succeeded on deleted file ('%s')\n", ofs.szPathName);
}