#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ content_read; int /*<<< orphan*/  data_stream; } ;
struct TYPE_5__ {int /*<<< orphan*/  read_gzip; TYPE_1__ netconn_stream; scalar_t__ read_size; scalar_t__ read_pos; int /*<<< orphan*/ * data_stream; } ;
typedef  TYPE_2__ http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  destroy_data_stream (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_data_stream(http_request_t *req)
{
    destroy_data_stream(req->data_stream);
    req->data_stream = &req->netconn_stream.data_stream;
    req->read_pos = req->read_size = req->netconn_stream.content_read = 0;
    req->read_gzip = FALSE;
}