#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* errhint; int /*<<< orphan*/ * versionstr; } ;
typedef  TYPE_1__ VersionResult ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_VERSION_STR_LEN ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_VERSION_JSON_FIELD ; 
 int /*<<< orphan*/  char_in_valid_version_digits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstring_to_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isalpha (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_field_text ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * text_to_cstring (int /*<<< orphan*/ ) ; 

bool
ts_validate_server_version(const char *json, VersionResult *result)
{
	int i;
	Datum version = DirectFunctionCall2(json_object_field_text,
										CStringGetTextDatum(json),
										PointerGetDatum(cstring_to_text(TS_VERSION_JSON_FIELD)));

	memset(result, 0, sizeof(VersionResult));

	result->versionstr = text_to_cstring(DatumGetTextPP(version));

	if (result->versionstr == NULL)
	{
		result->errhint = "no version string in response";
		return false;
	}

	if (strlen(result->versionstr) > MAX_VERSION_STR_LEN)
	{
		result->errhint = "version string is too long";
		return false;
	}

	for (i = 0; i < strlen(result->versionstr); i++)
	{
		if (!isalpha(result->versionstr[i]) && !isdigit(result->versionstr[i]) &&
			!char_in_valid_version_digits(result->versionstr[i]))
		{
			result->errhint = "version string has invalid characters";
			return false;
		}
	}

	return true;
}