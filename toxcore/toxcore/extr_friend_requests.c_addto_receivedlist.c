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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t received_requests_index; int /*<<< orphan*/ * received_requests; } ;
typedef  TYPE_1__ Friend_Requests ;

/* Variables and functions */
 size_t MAX_RECEIVED_STORED ; 
 int /*<<< orphan*/  id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void addto_receivedlist(Friend_Requests *fr, const uint8_t *real_pk)
{
    if (fr->received_requests_index >= MAX_RECEIVED_STORED)
        fr->received_requests_index = 0;

    id_copy(fr->received_requests[fr->received_requests_index], real_pk);
    ++fr->received_requests_index;
}