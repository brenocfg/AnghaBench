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

/* Variables and functions */
 int /*<<< orphan*/  TLS ; 
 int /*<<< orphan*/  cur_a_dc ; 
 int tgl_authorized_dc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int is_authorized (void) {
  return tgl_authorized_dc (TLS, cur_a_dc);
}