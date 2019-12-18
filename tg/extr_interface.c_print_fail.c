#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in_ev {int dummy; } ;
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_2__ {char* error; int /*<<< orphan*/  error_code; } ;

/* Variables and functions */
 TYPE_1__* TLS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  enable_json ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 scalar_t__ json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 int /*<<< orphan*/  mprint_end (struct in_ev*) ; 
 int /*<<< orphan*/  mprint_start (struct in_ev*) ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*,char*,...) ; 

void print_fail (struct in_ev *ev) {
  mprint_start (ev);
  if (!enable_json) {
    mprintf (ev, "FAIL: %d: %s\n", TLS->error_code, TLS->error);
  } else {
  #ifdef USE_JSON
    json_t *res = json_object ();
    assert (json_object_set (res, "result", json_string ("FAIL")) >= 0);
    assert (json_object_set (res, "error_code", json_integer (TLS->error_code)) >= 0);
    assert (json_object_set (res, "error", json_string (TLS->error)) >= 0);
    char *s = json_dumps (res, 0);
    mprintf (ev, "%s\n", s);
    json_decref (res);
    free (s);
  #endif
  }
  mprint_end (ev);
}