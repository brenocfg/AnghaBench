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
typedef  int /*<<< orphan*/  uint64_ ;
typedef  scalar_t__ _TCHAR ;

/* Variables and functions */
 scalar_t__ GetTickCount () ; 
 scalar_t__ _T (char) ; 
 scalar_t__* _fgetts (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _puttc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int parse_print (scalar_t__*) ; 
 int /*<<< orphan*/  print_uptime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

int _tmain(int argc, _TCHAR * argv[])
{
 int r;

 if(argc <= 1)
 {
  print_uptime((uint64_)GetTickCount(), 0, NULL, 0);
  _puttc(_T('\n'), stdout);
 }
 else if(argc == 2 && argv[1][0] == _T('-') && argv[1][1] == 0)
 {
  while(!feof(stdin))
  {
   _TCHAR buf[23];
   _TCHAR * str;

   str = _fgetts(buf, 22, stdin);

   if(str == NULL)
    return 0;

   if((r = parse_print(str)) != 0)
    return r;
  }
 }
 else
 {
  int i;

  for(i = 1; i < argc; ++ i)
   if((r = parse_print(argv[i])) != 0)
    return r;
 }

 return 0;
}