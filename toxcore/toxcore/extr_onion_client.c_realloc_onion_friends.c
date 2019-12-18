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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * friends_list; } ;
typedef  int /*<<< orphan*/  Onion_Friend ;
typedef  TYPE_1__ Onion_Client ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int realloc_onion_friends(Onion_Client *onion_c, uint32_t num)
{
    if (num == 0) {
        free(onion_c->friends_list);
        onion_c->friends_list = NULL;
        return 0;
    }

    Onion_Friend *newonion_friends = realloc(onion_c->friends_list, num * sizeof(Onion_Friend));

    if (newonion_friends == NULL)
        return -1;

    onion_c->friends_list = newonion_friends;
    return 0;
}