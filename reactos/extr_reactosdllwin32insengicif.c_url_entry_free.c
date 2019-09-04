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
struct url_info {struct url_info* url; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct url_info*) ; 

__attribute__((used)) static void url_entry_free(struct url_info *url)
{
    heap_free(url->url);
    heap_free(url);
}