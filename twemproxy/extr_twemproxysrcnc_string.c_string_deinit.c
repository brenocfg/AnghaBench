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
struct string {scalar_t__ len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  nc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_init (struct string*) ; 

void
string_deinit(struct string *str)
{
    ASSERT((str->len == 0 && str->data == NULL) ||
           (str->len != 0 && str->data != NULL));

    if (str->data != NULL) {
        nc_free(str->data);
        string_init(str);
    }
}