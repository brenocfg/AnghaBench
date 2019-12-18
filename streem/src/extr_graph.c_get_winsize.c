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
struct winsize {int ws_col; int ws_row; } ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int ioctl (int,int /*<<< orphan*/ ,struct winsize*) ; 

__attribute__((used)) static int
get_winsize(int* row, int* col)
{
  struct winsize w;
  int n;

  n = ioctl(1, TIOCGWINSZ, &w);
  if (n < 0 || w.ws_col == 0) {
    return STRM_NG;
  }
  *row = w.ws_row;
  *col = w.ws_col;
  return STRM_OK;
}