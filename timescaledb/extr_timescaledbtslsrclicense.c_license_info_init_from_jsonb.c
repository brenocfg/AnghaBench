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
struct TYPE_3__ {int enterprise_features_enabled; int /*<<< orphan*/  end_time; int /*<<< orphan*/  start_time; int /*<<< orphan*/  kind; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ LicenseInfo ;
typedef  int /*<<< orphan*/  Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  json_get_end_time (int /*<<< orphan*/ *) ; 
 char* json_get_id (int /*<<< orphan*/ *) ; 
 char* json_get_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_get_start_time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
license_info_init_from_jsonb(Jsonb *json_license, LicenseInfo *out)
{
	char *id_str = json_get_id(json_license);

	if (id_str == NULL)
		elog(ERROR, "missing id in license key");
	StrNCpy(out->id, id_str, sizeof(out->id));
	StrNCpy(out->kind, json_get_kind(json_license), sizeof(out->kind));
	out->start_time = json_get_start_time(json_license);
	out->end_time = json_get_end_time(json_license);
	out->enterprise_features_enabled = true;
}