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
typedef  int /*<<< orphan*/  int64_ ;
typedef  int /*<<< orphan*/  _TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char) ; 
 int /*<<< orphan*/  _puttc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ttoi64 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  print_uptime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int parse_print(const _TCHAR * str)
{
 int64_ tickcount;

 tickcount = _ttoi64(str);

 if(tickcount < 0)
  tickcount = - tickcount;
 else if(tickcount == 0)
  return 1;

 print_uptime(tickcount, 0, NULL, 0);
 _puttc(_T('\n'), stdout);

 return 0;
}