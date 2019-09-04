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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Tox ;
struct TYPE_2__ {scalar_t__ accepted; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOX_PUBLIC_KEY_SIZE ; 
 int /*<<< orphan*/  do_refresh () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_lines (char*) ; 
 int num_requests ; 
 TYPE_1__* pending_requests ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void print_request(Tox *m, const uint8_t *public_key, const uint8_t *data, size_t length, void *userdata)
{
    new_lines("[i] received friend request with message:");
    new_lines((char *)data);
    char numchar[100];
    sprintf(numchar, "[i] accept request with /a %u", num_requests);
    new_lines(numchar);
    memcpy(pending_requests[num_requests].id, public_key, TOX_PUBLIC_KEY_SIZE);
    pending_requests[num_requests].accepted = 0;
    ++num_requests;
    do_refresh();
}