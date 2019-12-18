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
struct TYPE_3__ {char* szPathName; } ;
typedef  TYPE_1__ OFSTRUCT ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetFileAttributesA (char*) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  LZClose (scalar_t__) ; 
 scalar_t__ LZOpenFileA (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_DELETE ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 

__attribute__((used)) static void delete_file(char *fname)
{
  INT file;
  OFSTRUCT ofs;
  DWORD retval;

  file = LZOpenFileA(fname, &ofs, OF_DELETE);
  ok(file >= 0, "LZOpenFileA failed to delete '%s'\n", fname);
  LZClose(file);
  retval = GetFileAttributesA(fname);
  ok(retval == INVALID_FILE_ATTRIBUTES, "GetFileAttributesA succeeded on deleted file ('%s')\n", ofs.szPathName);
}