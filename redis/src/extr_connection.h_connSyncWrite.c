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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {TYPE_1__* type; } ;
typedef  TYPE_2__ connection ;
struct TYPE_5__ {int /*<<< orphan*/  (* sync_write ) (TYPE_2__*,char*,int /*<<< orphan*/ ,long long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int /*<<< orphan*/ ,long long) ; 

__attribute__((used)) static inline ssize_t connSyncWrite(connection *conn, char *ptr, ssize_t size, long long timeout) {
    return conn->type->sync_write(conn, ptr, size, timeout);
}