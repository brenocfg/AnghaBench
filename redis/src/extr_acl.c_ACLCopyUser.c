#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__** allowed_subcommands; int /*<<< orphan*/  flags; int /*<<< orphan*/  allowed_commands; void* patterns; void* passwords; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  ACLAddAllowedSubcommand (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  ACLResetSubcommands (TYPE_1__*) ; 
 int USER_COMMAND_BITS_COUNT ; 
 void* listDup (void*) ; 
 int /*<<< orphan*/  listRelease (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ACLCopyUser(user *dst, user *src) {
    listRelease(dst->passwords);
    listRelease(dst->patterns);
    dst->passwords = listDup(src->passwords);
    dst->patterns = listDup(src->patterns);
    memcpy(dst->allowed_commands,src->allowed_commands,
           sizeof(dst->allowed_commands));
    dst->flags = src->flags;
    ACLResetSubcommands(dst);
    /* Copy the allowed subcommands array of array of SDS strings. */
    if (src->allowed_subcommands) {
        for (int j = 0; j < USER_COMMAND_BITS_COUNT; j++) {
            if (src->allowed_subcommands[j]) {
                for (int i = 0; src->allowed_subcommands[j][i]; i++)
                {
                    ACLAddAllowedSubcommand(dst, j,
                        src->allowed_subcommands[j][i]);
                }
            }
        }
    }
}