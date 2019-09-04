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
typedef  int /*<<< orphan*/  object_header_t ;
typedef  int /*<<< orphan*/  http_request_t ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ drain_content (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_release_netconn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void HTTPREQ_CloseConnection(object_header_t *hdr)
{
    http_request_t *req = (http_request_t*)hdr;

    http_release_netconn(req, drain_content(req, FALSE) == ERROR_SUCCESS);
}