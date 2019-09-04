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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_FRIENDLY_NAME_PROP_ID ; 
 int /*<<< orphan*/  CERT_NAME_SIMPLE_DISPLAY_TYPE ; 
 int /*<<< orphan*/ * get_cert_name_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_cert_property_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_cert_display_name(PCCERT_CONTEXT cert)
{
    WCHAR *name = get_cert_property_as_string(cert, CERT_FRIENDLY_NAME_PROP_ID);

    if (!name)
        name = get_cert_name_string(cert, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0);
    return name;
}