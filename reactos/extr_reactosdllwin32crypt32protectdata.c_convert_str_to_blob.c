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
struct TYPE_3__ {int /*<<< orphan*/ * pbData; scalar_t__ cbData; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  TYPE_1__ DATA_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BYTE *convert_str_to_blob(LPCSTR str, DATA_BLOB *blob)
{
    if (!str || !blob) return NULL;

    blob->cbData=strlen(str)+1;
    if (!(blob->pbData=CryptMemAlloc(blob->cbData)))
    {
        blob->cbData=0;
    }
    else {
        strcpy((LPSTR)blob->pbData, str);
    }

    return blob->pbData;
}