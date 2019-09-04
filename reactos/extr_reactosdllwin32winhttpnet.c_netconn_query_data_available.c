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
struct TYPE_3__ {int /*<<< orphan*/  peek_len; scalar_t__ secure; } ;
typedef  TYPE_1__ netconn_t ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */

ULONG netconn_query_data_available( netconn_t *conn )
{
    return conn->secure ? conn->peek_len : 0;
}