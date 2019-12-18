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
struct vlc_http_conn {TYPE_1__* cbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct vlc_http_conn*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vlc_http_conn*) ; 

__attribute__((used)) static inline void vlc_http_conn_release(struct vlc_http_conn *conn)
{
    conn->cbs->release(conn);
}