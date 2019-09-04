#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int wxflag; char* lookahead; int /*<<< orphan*/  exflag; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ioinfo ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EF_CRIT_INIT ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetStdHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WX_APPEND ; 
 int WX_DONTINHERIT ; 
 int WX_OPEN ; 
 int WX_PIPE ; 
 int WX_TEXT ; 
 int WX_TTY ; 
 TYPE_1__** __pioinfo ; 

__attribute__((used)) static void msvcrt_set_fd(ioinfo *fdinfo, HANDLE hand, int flag)
{
  fdinfo->handle = hand;
  fdinfo->wxflag = WX_OPEN | (flag & (WX_DONTINHERIT | WX_APPEND | WX_TEXT | WX_PIPE | WX_TTY));
  fdinfo->lookahead[0] = '\n';
  fdinfo->lookahead[1] = '\n';
  fdinfo->lookahead[2] = '\n';
  fdinfo->exflag &= EF_CRIT_INIT;

  switch (fdinfo-__pioinfo[0])
  {
  case 0: SetStdHandle(STD_INPUT_HANDLE,  hand); break;
  case 1: SetStdHandle(STD_OUTPUT_HANDLE, hand); break;
  case 2: SetStdHandle(STD_ERROR_HANDLE,  hand); break;
  }
}