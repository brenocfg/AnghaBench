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
 char* append_namespace (char*,struct namespace*,char const*) ; 
 int /*<<< orphan*/  is_global_namespace (struct namespace*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ use_abi_namespace ; 
 char* xmalloc (unsigned int) ; 

char *format_namespace(struct namespace *namespace, const char *prefix, const char *separator, const char *suffix)
{
    unsigned len = strlen(prefix) + strlen(suffix);
    unsigned sep_len = strlen(separator);
    struct namespace *iter;
    char *ret, *ptr;

    if(use_abi_namespace && !is_global_namespace(namespace))
        len += 3 /* strlen("ABI") */ + sep_len;

    for(iter = namespace; !is_global_namespace(iter); iter = iter->parent)
        len += strlen(iter->name) + sep_len;

    ret = xmalloc(len+1);
    strcpy(ret, prefix);
    ptr = append_namespace(ret + strlen(ret), namespace, separator);
    strcpy(ptr, suffix);

    return ret;
}