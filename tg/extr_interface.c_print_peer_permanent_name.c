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
typedef  int /*<<< orphan*/  tgl_peer_id_t ;
struct in_ev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_permanent_peer_id (int /*<<< orphan*/ ) ; 

void print_peer_permanent_name (struct in_ev *ev, tgl_peer_id_t id) {
  mprintf (ev, "%s", print_permanent_peer_id (id));
}