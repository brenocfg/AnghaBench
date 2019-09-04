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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
struct TYPE_2__ {scalar_t__ file; scalar_t__ friendnum; } ;
typedef  scalar_t__ TOX_CONNECTION ;

/* Variables and functions */
 unsigned int NUM_FILE_SENDERS ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 TYPE_1__* file_senders ; 
 int /*<<< orphan*/  printf (char*) ; 

void print_online(Tox *tox, uint32_t friendnumber, TOX_CONNECTION status, void *userdata)
{
    if (status)
        printf("\nOther went online.\n");
    else {
        printf("\nOther went offline.\n");
        unsigned int i;

        for (i = 0; i < NUM_FILE_SENDERS; ++i)
            if (file_senders[i].file != 0 && file_senders[i].friendnum == friendnumber) {
                fclose(file_senders[i].file);
                file_senders[i].file = 0;
            }
    }
}