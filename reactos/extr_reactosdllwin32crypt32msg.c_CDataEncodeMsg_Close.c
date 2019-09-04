#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bare_content; } ;
typedef  TYPE_1__* HCRYPTMSG ;
typedef  TYPE_1__ CDataEncodeMsg ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 scalar_t__ empty_data_content ; 

__attribute__((used)) static void CDataEncodeMsg_Close(HCRYPTMSG hCryptMsg)
{
    CDataEncodeMsg *msg = hCryptMsg;

    if (msg->bare_content != empty_data_content)
        LocalFree(msg->bare_content);
}