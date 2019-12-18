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
typedef  int /*<<< orphan*/  zed_strings_t ;
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_STRING_ARRAY ; 
 int MAXBUF ; 
 int _zed_event_add_array_err (int /*<<< orphan*/ ,char const*) ; 
 int _zed_event_add_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*,char*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_string_array (int /*<<< orphan*/ *,char***,size_t*) ; 
 int snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
_zed_event_add_string_array(uint64_t eid, zed_strings_t *zsp,
    const char *prefix, nvpair_t *nvp)
{
	char buf[MAXBUF];
	int buflen = sizeof (buf);
	const char *name;
	char **strp;
	uint_t nelem;
	uint_t i;
	char *p;
	int n;

	assert((nvp != NULL) && (nvpair_type(nvp) == DATA_TYPE_STRING_ARRAY));

	name = nvpair_name(nvp);
	(void) nvpair_value_string_array(nvp, &strp, &nelem);
	for (i = 0, p = buf; (i < nelem) && (buflen > 0); i++) {
		n = snprintf(p, buflen, "%s ", strp[i] ? strp[i] : "<NULL>");
		if ((n < 0) || (n >= buflen))
			return (_zed_event_add_array_err(eid, name));
		p += n;
		buflen -= n;
	}
	if (nelem > 0)
		*--p = '\0';

	return (_zed_event_add_var(eid, zsp, prefix, name, "%s", buf));
}