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
struct TYPE_3__ {scalar_t__ post_data; int /*<<< orphan*/  headers; scalar_t__ post_stream; } ;
typedef  TYPE_1__ request_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIInputStream_Release (scalar_t__) ; 

__attribute__((used)) static void release_request_data(request_data_t *request_data)
{
    if(request_data->post_stream)
        nsIInputStream_Release(request_data->post_stream);
    heap_free(request_data->headers);
    if(request_data->post_data)
        GlobalFree(request_data->post_data);
}