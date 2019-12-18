#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  THFile ;

/* Variables and functions */
 int /*<<< orphan*/  THDiskFile_name (int /*<<< orphan*/ *) ; 
 scalar_t__ THFile_isOpened (int /*<<< orphan*/ *) ; 
 scalar_t__ THFile_isReadable (int /*<<< orphan*/ *) ; 
 scalar_t__ THFile_isWritable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaT_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char,char) ; 

__attribute__((used)) static int torch_DiskFile___tostring__(lua_State *L)
{
  THFile *self = luaT_checkudata(L, 1, "torch.DiskFile");
  lua_pushfstring(L, "torch.DiskFile on <%s> [status: %s -- mode %c%c]",
                  THDiskFile_name(self),
                  (THFile_isOpened(self) ? "open" : "closed"),
                  (THFile_isReadable(self) ? 'r' : ' '),
                  (THFile_isWritable(self) ? 'w' : ' '));

  return 1;
}