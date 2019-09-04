#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct find_s {int expected_loc; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  needle; } ;
typedef  int /*<<< orphan*/  ft ;
struct TYPE_4__ {int /*<<< orphan*/  cpMax; int /*<<< orphan*/  cpMin; } ;
struct TYPE_5__ {int /*<<< orphan*/  lpstrText; TYPE_1__ chrg; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ FINDTEXTA ;

/* Variables and functions */
 int /*<<< orphan*/  EM_FINDTEXT ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void check_EM_FINDTEXT(HWND hwnd, const char *name, struct find_s *f, int id) {
  int findloc;
  FINDTEXTA ft;
  memset(&ft, 0, sizeof(ft));
  ft.chrg.cpMin = f->start;
  ft.chrg.cpMax = f->end;
  ft.lpstrText = f->needle;
  findloc = SendMessageA(hwnd, EM_FINDTEXT, f->flags, (LPARAM)&ft);
  ok(findloc == f->expected_loc,
     "EM_FINDTEXT(%s,%d) '%s' in range(%d,%d), flags %08x, got start at %d, expected %d\n",
     name, id, f->needle, f->start, f->end, f->flags, findloc, f->expected_loc);
}