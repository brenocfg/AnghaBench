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
struct sig_list {int sig; struct sig_list* next; } ;
typedef  int /*<<< orphan*/  strm_sighandler_t ;
typedef  scalar_t__ sighandler_t ;

/* Variables and functions */
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  handler ; 
 struct sig_list* sig_list ; 
 scalar_t__ signal (int,int /*<<< orphan*/ ) ; 

int
strm_unsignal(int sig, strm_sighandler_t func)
{
  sighandler_t r = signal(sig, SIG_IGN);
  struct sig_list* list;
  struct sig_list* tmp = NULL;

  if (r == SIG_ERR) return STRM_NG;
  for (list=sig_list; list; list=list->next) {
    if (list->sig == sig) {
      if (tmp == NULL) {        /* head */
        sig_list = list->next;
      }
      else {
        tmp->next = list->next;
        tmp = list;
      }
    }
  }
  signal(sig, handler);
  return STRM_OK;
}