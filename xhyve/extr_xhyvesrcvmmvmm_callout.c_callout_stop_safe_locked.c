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
struct callout {int flags; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int CALLOUT_ACTIVE ; 
 int CALLOUT_COMPLETED ; 
 int CALLOUT_PENDING ; 
 int CALLOUT_WAITING ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ callout_active (struct callout*) ; 
 int /*<<< orphan*/  callout_cnd ; 
 int /*<<< orphan*/  callout_completed (struct callout*) ; 
 int /*<<< orphan*/  callout_mtx ; 
 scalar_t__ callout_pending (struct callout*) ; 
 int /*<<< orphan*/  callout_remove (struct callout*) ; 
 scalar_t__ callout_thread ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_self () ; 
 int work ; 

__attribute__((used)) static int callout_stop_safe_locked(struct callout *c, int drain) {
  int result = 0;
  
  if ((drain) && (pthread_self() != callout_thread) && (callout_pending(c) ||
    (callout_active(c) && !callout_completed(c))))
  {
    if (c->flags & CALLOUT_WAITING) {
      abort();
    }
    
    /* wait for callout */
    c->flags |= CALLOUT_WAITING;
    work = true;

    pthread_cond_signal(&callout_cnd);
  
    while (!(c->flags & CALLOUT_COMPLETED)) {
      pthread_cond_wait(&c->wait, &callout_mtx);
    }

    c->flags &= ~CALLOUT_WAITING;
    result = 1;
  }
  
  callout_remove(c);
  
  /* clear flags */
  c->flags &= ~(CALLOUT_ACTIVE | CALLOUT_PENDING | CALLOUT_COMPLETED |
    CALLOUT_WAITING);
  
  return (result);
}