#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ cbData; int /*<<< orphan*/ * pbData; } ;
struct TYPE_8__ {void* cbData; void* pbData; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ DATA_BLOB ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 TYPE_4__ cipher ; 
 TYPE_4__ cipher_entropy ; 
 TYPE_4__ cipher_no_desc ; 
 int /*<<< orphan*/ * desc ; 
 scalar_t__ key ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCryptProtectData (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ protected ; 
 scalar_t__ secret ; 
 scalar_t__ secret2 ; 
 void* strlen (scalar_t__) ; 

__attribute__((used)) static void test_cryptprotectdata(void)
{
    LONG r;
    DATA_BLOB plain;
    DATA_BLOB entropy;

    plain.pbData=(void*)secret;
    plain.cbData=strlen(secret)+1;

    entropy.pbData=(void*)key;
    entropy.cbData=strlen(key)+1;

    SetLastError(0xDEADBEEF);
    protected = pCryptProtectData(NULL,desc,NULL,NULL,NULL,0,&cipher);
    ok(!protected, "Encrypting without plain data source.\n");
    r = GetLastError();
    ok(r == ERROR_INVALID_PARAMETER, "Wrong (%u) GetLastError seen\n",r);

    SetLastError(0xDEADBEEF);
    protected = pCryptProtectData(&plain,desc,NULL,NULL,NULL,0,NULL);
    ok(!protected, "Encrypting without cipher destination.\n");
    r = GetLastError();
    ok(r == ERROR_INVALID_PARAMETER, "Wrong (%u) GetLastError seen\n",r);

    cipher.pbData=NULL;
    cipher.cbData=0;

    /* without entropy */
    SetLastError(0xDEADBEEF);
    protected = pCryptProtectData(&plain,desc,NULL,NULL,NULL,0,&cipher);
    ok(protected ||
     broken(!protected), /* Win9x/NT4 */
     "Encrypting without entropy.\n");
    if (protected)
    {
        r = GetLastError();
        ok(r == ERROR_SUCCESS ||
           r == ERROR_IO_PENDING, /* win2k */
           "Expected ERROR_SUCCESS or ERROR_IO_PENDING, got %d\n",r);
    }

    cipher_entropy.pbData=NULL;
    cipher_entropy.cbData=0;

    /* with entropy */
    SetLastError(0xDEADBEEF);
    protected = pCryptProtectData(&plain,desc,&entropy,NULL,NULL,0,&cipher_entropy);
    ok(protected ||
     broken(!protected), /* Win9x/NT4 */
     "Encrypting with entropy.\n");

    cipher_no_desc.pbData=NULL;
    cipher_no_desc.cbData=0;

    /* with entropy but no description */
    plain.pbData=(void*)secret2;
    plain.cbData=strlen(secret2)+1;
    SetLastError(0xDEADBEEF);
    protected = pCryptProtectData(&plain,NULL,&entropy,NULL,NULL,0,&cipher_no_desc);
    if (!protected)
    {
        /* fails in win2k */
        ok(GetLastError() == ERROR_INVALID_PARAMETER,
           "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    }
}