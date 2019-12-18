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
struct sig_list {int sig; void* arg; int /*<<< orphan*/  func; struct sig_list* next; } ;
typedef  int /*<<< orphan*/  strm_sighandler_t ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 struct sig_list* malloc (int) ; 
 struct sig_list* sig_list ; 

__attribute__((used)) static int
add_sig(int sig, strm_sighandler_t func, void* arg)
{
  struct sig_list* node = malloc(sizeof(struct sig_list));

  if (node == NULL) return STRM_NG;
  node->next = sig_list;
  node->sig = sig;
  node->func = func;
  node->arg = arg;
  sig_list = node;
  return STRM_OK;
}