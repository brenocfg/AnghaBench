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
struct TYPE_2__ {scalar_t__ size; scalar_t__ content; } ;
typedef  TYPE_1__ HttpRequest ;

/* Variables and functions */
 size_t MIN (scalar_t__,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 

__attribute__((used)) static size_t
send_request (void *ptr, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size *nmemb;
    size_t copy_size;
    HttpRequest *req = userp;

    if (req->size == 0)
        return 0;

    copy_size = MIN(req->size, realsize);
    memcpy (ptr, req->content, copy_size);
    req->size -= copy_size;
    req->content = req->content + copy_size;

    return copy_size;
}