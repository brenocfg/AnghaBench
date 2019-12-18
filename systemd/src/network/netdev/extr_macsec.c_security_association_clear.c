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
struct TYPE_3__ {int /*<<< orphan*/  key_file; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;
typedef  TYPE_1__ SecurityAssociation ;

/* Variables and functions */
 int /*<<< orphan*/  explicit_bzero_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void security_association_clear(SecurityAssociation *sa) {
        if (!sa)
                return;

        explicit_bzero_safe(sa->key, sa->key_len);
        free(sa->key);
        free(sa->key_file);
}