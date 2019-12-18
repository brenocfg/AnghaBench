#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; scalar_t__ name_length; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ MAX_NAME_LENGTH ; 
 scalar_t__ friend_not_valid (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 

int setfriendname(Messenger *m, int32_t friendnumber, const uint8_t *name, uint16_t length)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    if (length > MAX_NAME_LENGTH || length == 0)
        return -1;

    m->friendlist[friendnumber].name_length = length;
    memcpy(m->friendlist[friendnumber].name, name, length);
    return 0;
}