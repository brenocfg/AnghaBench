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
struct tgl_state {int dummy; } ;

/* Variables and functions */
 struct tgl_state* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lua_our_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  py_our_id (int /*<<< orphan*/ ) ; 

void our_id_gw (struct tgl_state *TLSR, tgl_peer_id_t id) {
  assert (TLSR == TLS);
  #ifdef USE_LUA
    lua_our_id (id);
  #endif
  #ifdef USE_PYTHON
    py_our_id (id);
  #endif
}