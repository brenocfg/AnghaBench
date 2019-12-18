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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int TOX_ADDRESS_SIZE ; 
 int /*<<< orphan*/  fraddr_to_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tox_self_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void get_id(Tox *m, char *data)
{
    sprintf(data, "[i] ID: ");
    int offset = strlen(data);
    uint8_t address[TOX_ADDRESS_SIZE];
    tox_self_get_address(m, address);
    fraddr_to_str(address, data + offset);
}