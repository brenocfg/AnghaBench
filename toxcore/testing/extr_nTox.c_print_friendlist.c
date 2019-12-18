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
typedef  char uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int FRADDR_TOSTR_BUFSIZE ; 
 int TOX_ADDRESS_SIZE ; 
 scalar_t__ TOX_MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  fraddr_to_str (char*,char*) ; 
 int getfriendname_terminated (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int id_str_len ; 
 int /*<<< orphan*/  new_lines (char*) ; 
 char* ptrn_friend ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ tox_friend_get_public_key (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *) ; 

void print_friendlist(Tox *m)
{
    new_lines("[i] Friend List:");

    char name[TOX_MAX_NAME_LENGTH + 1];
    uint8_t fraddr_bin[TOX_ADDRESS_SIZE];
    char fraddr_str[FRADDR_TOSTR_BUFSIZE];

    /* account for the longest name and the longest "base" string and number (int) and id_str */
    char fstring[TOX_MAX_NAME_LENGTH + strlen(ptrn_friend) + 21 + id_str_len];

    uint32_t i = 0;

    while (getfriendname_terminated(m, i, name) != -1) {
        if (tox_friend_get_public_key(m, i, fraddr_bin, NULL))
            fraddr_to_str(fraddr_bin, fraddr_str);
        else
            sprintf(fraddr_str, "???");

        if (strlen(name) <= 0) {
            sprintf(fstring, ptrn_friend, i, "No name?", fraddr_str);
        } else {
            sprintf(fstring, ptrn_friend, i, (uint8_t *)name, fraddr_str);
        }

        i++;
        new_lines(fstring);
    }

    if (i == 0)
        new_lines("+ no friends! D:");
}