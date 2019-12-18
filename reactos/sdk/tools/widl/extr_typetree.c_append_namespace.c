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
struct namespace {char* name; struct namespace* parent; } ;

/* Variables and functions */
 scalar_t__ is_global_namespace (struct namespace*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  use_abi_namespace ; 

__attribute__((used)) static char *append_namespace(char *ptr, struct namespace *namespace, const char *separator)
{
    if(is_global_namespace(namespace)) {
        if(!use_abi_namespace)
            return ptr;
        strcpy(ptr, "ABI");
        strcat(ptr, separator);
        return ptr + strlen(ptr);
    }

    ptr = append_namespace(ptr, namespace->parent, separator);
    strcpy(ptr, namespace->name);
    strcat(ptr, separator);
    return ptr + strlen(ptr);
}