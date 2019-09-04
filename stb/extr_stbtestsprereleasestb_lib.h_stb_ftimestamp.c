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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  time_t ;
struct stb__stat {int /*<<< orphan*/  st_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  _wstat (int /*<<< orphan*/  const*,struct stb__stat*) ; 
 int /*<<< orphan*/  stat (char*,struct stb__stat*) ; 
 scalar_t__ stb__from_utf8 (char*) ; 
 scalar_t__ stb__windows (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

time_t stb_ftimestamp(char *filename)
{
   struct stb__stat buf;
   if (stb__windows(
             _wstat((const wchar_t *)stb__from_utf8(filename), &buf),
               stat(filename,&buf)
          ) == 0)
   {
      return buf.st_mtime;
   } else {
      return 0;
   }
}