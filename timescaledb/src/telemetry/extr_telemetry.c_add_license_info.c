#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* add_tsl_license_info_telemetry ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  JsonbParseState ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_LICENSE_EDITION ; 
 int /*<<< orphan*/  REQ_LICENSE_EDITION_APACHE ; 
 scalar_t__ TS_CURRENT_LICENSE_IS_APACHE_ONLY () ; 
 int /*<<< orphan*/  WJB_BEGIN_OBJECT ; 
 int /*<<< orphan*/  WJB_END_OBJECT ; 
 int /*<<< orphan*/  pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ts_cm_functions ; 
 int /*<<< orphan*/  ts_jsonb_add_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_license_info(JsonbParseState *state)
{
	pushJsonbValue(&state, WJB_BEGIN_OBJECT, NULL);

	if (TS_CURRENT_LICENSE_IS_APACHE_ONLY())
		ts_jsonb_add_str(state, REQ_LICENSE_EDITION, REQ_LICENSE_EDITION_APACHE);
	else
		ts_cm_functions->add_tsl_license_info_telemetry(state);

	pushJsonbValue(&state, WJB_END_OBJECT, NULL);
}