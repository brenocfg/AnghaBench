#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ tgl_peer_t ;
struct in_ev {int dummy; } ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_pack_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_pack_updates (unsigned int) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,char*) ; 

void json_peer_update (struct in_ev *ev, tgl_peer_t *P, unsigned flags) {
  #ifdef USE_JSON
    json_t *res = json_object ();
    assert (json_object_set (res, "event", json_string ("updates")) >= 0);
    assert (json_object_set (res, "peer", json_pack_peer (P->id)) >= 0);
    assert (json_object_set (res, "updates", json_pack_updates (flags)) >= 0);
    char *s = json_dumps (res, 0);
    mprintf (ev, "%s\n", s);
    json_decref (res);
    free (s);
  #endif
}