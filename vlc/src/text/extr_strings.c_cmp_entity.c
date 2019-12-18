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
struct xml_entity_s {int /*<<< orphan*/  psz_entity; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_entity (const void *key, const void *elem)
{
    const struct xml_entity_s *ent = elem;
    const char *name = key;

    return strncmp (name, ent->psz_entity, strlen (ent->psz_entity));
}