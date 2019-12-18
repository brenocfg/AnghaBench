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
typedef  int /*<<< orphan*/  json_value ;

/* Variables and functions */
 char* jsongetstring (int /*<<< orphan*/  const*,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static inline
char * json_dupstring(const json_value *node, const char *key)
{
    const char *str = jsongetstring(node, key);
    return (str) ? strdup(str) : NULL;
}