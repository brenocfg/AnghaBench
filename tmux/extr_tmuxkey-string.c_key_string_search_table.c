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
typedef  size_t u_int ;
typedef  size_t key_code ;
struct TYPE_3__ {size_t key; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 size_t KEYC_NUSER ; 
 size_t KEYC_UNKNOWN ; 
 size_t KEYC_USER ; 
 TYPE_1__* key_string_table ; 
 size_t nitems (TYPE_1__*) ; 
 int sscanf (char const*,char*,size_t*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static key_code
key_string_search_table(const char *string)
{
	u_int	i, user;

	for (i = 0; i < nitems(key_string_table); i++) {
		if (strcasecmp(string, key_string_table[i].string) == 0)
			return (key_string_table[i].key);
	}

	if (sscanf(string, "User%u", &user) == 1 && user < KEYC_NUSER)
		return (KEYC_USER + user);

	return (KEYC_UNKNOWN);
}