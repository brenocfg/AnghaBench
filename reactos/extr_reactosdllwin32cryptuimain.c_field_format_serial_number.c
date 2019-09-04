#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {TYPE_2__* pCertInfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_6__ {TYPE_1__ SerialNumber; } ;
typedef  TYPE_3__* PCCERT_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/ * format_hex_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *field_format_serial_number(PCCERT_CONTEXT cert)
{
    return format_hex_string(cert->pCertInfo->SerialNumber.pbData,
     cert->pCertInfo->SerialNumber.cbData);
}