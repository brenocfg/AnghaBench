#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct find_s {int expected_loc; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ needle; } ;
typedef  int /*<<< orphan*/  ftw ;
typedef  int /*<<< orphan*/  fta ;
struct TYPE_5__ {int /*<<< orphan*/  cpMax; int /*<<< orphan*/  cpMin; } ;
struct TYPE_6__ {scalar_t__ lpstrText; TYPE_1__ chrg; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ FINDTEXTW ;
typedef  TYPE_2__ FINDTEXTA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EM_FINDTEXT ; 
 int /*<<< orphan*/  EM_FINDTEXTW ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atowstr (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void check_EM_FINDTEXT(HWND hwnd, const char *name, struct find_s *f, int id, BOOL unicode)
{
  int findloc;

  if(unicode){
      FINDTEXTW ftw;
      memset(&ftw, 0, sizeof(ftw));
      ftw.chrg.cpMin = f->start;
      ftw.chrg.cpMax = f->end;
      ftw.lpstrText = atowstr(f->needle);

      findloc = SendMessageA(hwnd, EM_FINDTEXT, f->flags, (LPARAM)&ftw);
      ok(findloc == f->expected_loc,
         "EM_FINDTEXT(%s,%d,%u) '%s' in range(%d,%d), flags %08x, got start at %d, expected %d\n",
         name, id, unicode, f->needle, f->start, f->end, f->flags, findloc, f->expected_loc);

      findloc = SendMessageA(hwnd, EM_FINDTEXTW, f->flags, (LPARAM)&ftw);
      ok(findloc == f->expected_loc,
         "EM_FINDTEXTW(%s,%d,%u) '%s' in range(%d,%d), flags %08x, got start at %d, expected %d\n",
         name, id, unicode, f->needle, f->start, f->end, f->flags, findloc, f->expected_loc);

      HeapFree(GetProcessHeap(), 0, (void*)ftw.lpstrText);
  }else{
      FINDTEXTA fta;
      memset(&fta, 0, sizeof(fta));
      fta.chrg.cpMin = f->start;
      fta.chrg.cpMax = f->end;
      fta.lpstrText = f->needle;

      findloc = SendMessageA(hwnd, EM_FINDTEXT, f->flags, (LPARAM)&fta);
      ok(findloc == f->expected_loc,
         "EM_FINDTEXT(%s,%d,%u) '%s' in range(%d,%d), flags %08x, got start at %d, expected %d\n",
         name, id, unicode, f->needle, f->start, f->end, f->flags, findloc, f->expected_loc);
  }
}