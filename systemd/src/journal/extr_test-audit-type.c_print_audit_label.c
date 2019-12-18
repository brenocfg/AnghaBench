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

/* Variables and functions */
 char* audit_type_name_alloca (int) ; 
 char* audit_type_to_string (int) ; 
 int /*<<< orphan*/  printf (char*,int,char*,char const*) ; 

__attribute__((used)) static void print_audit_label(int i) {
        const char *name;

        name = audit_type_name_alloca(i);
        /* This is a separate function only because of alloca */
        printf("%i → %s → %s\n", i, audit_type_to_string(i), name);
}