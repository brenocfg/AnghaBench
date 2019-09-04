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
typedef  void* PCERT_EXTENSION ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int CRYPT_FORMAT_STR_MULTI_LINE ; 
 int CRYPT_FORMAT_STR_NO_HEX ; 
 int /*<<< orphan*/ * crypt_format_extension (void*,int) ; 
 int /*<<< orphan*/ * field_format_extension_hex_with_ascii (void*) ; 

__attribute__((used)) static WCHAR *field_format_detailed_extension(PCCERT_CONTEXT cert, void *param)
{
    PCERT_EXTENSION ext = param;
    LPWSTR str = crypt_format_extension(ext,
     CRYPT_FORMAT_STR_MULTI_LINE | CRYPT_FORMAT_STR_NO_HEX);

    if (!str)
        str = field_format_extension_hex_with_ascii(ext);
    return str;
}