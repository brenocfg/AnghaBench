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
struct in_ev {int dummy; } ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ enable_json ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,...) ; 

void print_success (struct in_ev *ev) {
  if (ev || enable_json) {
    mprint_start (ev);
    if (!enable_json) {
      mprintf (ev, "SUCCESS\n");
    } else {
      #ifdef USE_JSON
        json_t *res = json_object ();
        assert (json_object_set (res, "result", json_string ("SUCCESS")) >= 0);
        char *s = json_dumps (res, 0);
        mprintf (ev, "%s\n", s);
        json_decref (res);
        free (s);
      #endif
    }
    mprint_end (ev);
  }
}