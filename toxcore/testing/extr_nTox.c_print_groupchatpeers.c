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
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int STRING_LENGTH ; 
 int TOX_MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  new_lines (char*) ; 
 int /*<<< orphan*/  new_lines_mark (char*,int) ; 
 size_t sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  tox_group_get_names (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,size_t*,int) ; 
 int tox_group_number_peers (int /*<<< orphan*/ *,int) ; 

void print_groupchatpeers(Tox *m, int groupnumber)
{
    int num = tox_group_number_peers(m, groupnumber);

    if (num < 0)
        return;

    if (!num) {
        new_lines("[g]+ no peers left in group.");
        return;
    }

    uint8_t names[num][TOX_MAX_NAME_LENGTH];
    uint16_t lengths[num];
    tox_group_get_names(m, groupnumber, names, lengths, num);
    int i;
    char numstr[16];
    char header[] = "[g]+ ";
    size_t header_len = strlen(header);
    char msg[STRING_LENGTH];
    strcpy(msg, header);
    size_t len_total = header_len;

    for (i = 0; i < num; ++i) {
        size_t len_name = lengths[i];
        size_t len_num = sprintf(numstr, "%i: ", i);

        if (len_num + len_name + len_total + 3 >= STRING_LENGTH) {
            new_lines_mark(msg, 1);

            strcpy(msg, header);
            len_total = header_len;
        }

        strcpy(msg + len_total, numstr);
        len_total += len_num;
        memcpy(msg + len_total, (char *)names[i], len_name);
        len_total += len_name;

        if (i < num - 1) {
            strcpy(msg + len_total, "|");
            len_total++;
        }
    }

    new_lines_mark(msg, 1);
}