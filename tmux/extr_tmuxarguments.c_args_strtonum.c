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
typedef  int /*<<< orphan*/  u_char ;
struct args_value {int /*<<< orphan*/  value; } ;
struct args_entry {int /*<<< orphan*/  values; } ;
struct args {int dummy; } ;

/* Variables and functions */
 struct args_value* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct args_entry* args_find (struct args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args_values ; 
 long long strtonum (int /*<<< orphan*/ ,long long,long long,char const**) ; 
 char* xstrdup (char const*) ; 

long long
args_strtonum(struct args *args, u_char ch, long long minval, long long maxval,
    char **cause)
{
	const char		*errstr;
	long long 	 	 ll;
	struct args_entry	*entry;
	struct args_value	*value;

	if ((entry = args_find(args, ch)) == NULL) {
		*cause = xstrdup("missing");
		return (0);
	}
	value = TAILQ_LAST(&entry->values, args_values);

	ll = strtonum(value->value, minval, maxval, &errstr);
	if (errstr != NULL) {
		*cause = xstrdup(errstr);
		return (0);
	}

	*cause = NULL;
	return (ll);
}