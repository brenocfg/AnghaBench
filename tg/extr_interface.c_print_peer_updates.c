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

/* Variables and functions */
 int TGL_UPDATE_ACCESS_HASH ; 
 int TGL_UPDATE_ADMIN ; 
 int TGL_UPDATE_BLOCKED ; 
 int TGL_UPDATE_CONTACT ; 
 int TGL_UPDATE_FLAGS ; 
 int TGL_UPDATE_MEMBERS ; 
 int TGL_UPDATE_NAME ; 
 int TGL_UPDATE_PHONE ; 
 int TGL_UPDATE_PHOTO ; 
 int TGL_UPDATE_REAL_NAME ; 
 int TGL_UPDATE_REQUESTED ; 
 int TGL_UPDATE_TITLE ; 
 int TGL_UPDATE_USERNAME ; 
 int TGL_UPDATE_WORKING ; 
 int /*<<< orphan*/  mprintf (struct in_ev*,char*) ; 

void print_peer_updates (struct in_ev *ev, int flags) {
  if (flags & TGL_UPDATE_PHONE) {
    mprintf (ev, " phone");
  }
  if (flags & TGL_UPDATE_CONTACT) {
    mprintf (ev, " contact");
  }
  if (flags & TGL_UPDATE_PHOTO) {
    mprintf (ev, " photo");
  }
  if (flags & TGL_UPDATE_BLOCKED) {
    mprintf (ev, " blocked");
  }
  if (flags & TGL_UPDATE_REAL_NAME) {
    mprintf (ev, " name");
  }
  if (flags & TGL_UPDATE_NAME) {
    mprintf (ev, " contact_name");
  }
  if (flags & TGL_UPDATE_REQUESTED) {
    mprintf (ev, " status");
  }
  if (flags & TGL_UPDATE_WORKING) {
    mprintf (ev, " status");
  }
  if (flags & TGL_UPDATE_FLAGS) {
    mprintf (ev, " flags");
  }
  if (flags & TGL_UPDATE_TITLE) {
    mprintf (ev, " title");
  }
  if (flags & TGL_UPDATE_ADMIN) {
    mprintf (ev, " admin");
  }
  if (flags & TGL_UPDATE_MEMBERS) {
    mprintf (ev, " members");
  }
  if (flags & TGL_UPDATE_ACCESS_HASH) {
    mprintf (ev, " access_hash");
  }
  if (flags & TGL_UPDATE_USERNAME) {
    mprintf (ev, " username");
  }
}