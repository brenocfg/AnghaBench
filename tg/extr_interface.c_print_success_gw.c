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
struct tgl_state {int dummy; } ;
struct in_ev {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 struct tgl_state* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct in_ev*) ; 
 int /*<<< orphan*/  print_fail (struct in_ev*) ; 
 int /*<<< orphan*/  print_success (struct in_ev*) ; 

void print_success_gw (struct tgl_state *TLSR, void *extra, int success) {
  assert (TLS == TLSR);
  struct in_ev *ev = extra;
  if (ev && !--ev->refcnt) {
    free (ev);
    return;
  }
  if (!success) { print_fail (ev); return; }
  else { print_success (ev); return; }
}