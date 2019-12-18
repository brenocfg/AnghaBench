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
struct sig_list {int sig; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int,int /*<<< orphan*/ ) ;struct sig_list* next; } ;

/* Variables and functions */
 struct sig_list* sig_list ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handler(int sig)
{
  struct sig_list* list;

  for (list=sig_list; list; list=list->next) {
    if (list->sig == sig) {
      (*list->func)(sig, list->arg);
    }
  }
}