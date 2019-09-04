#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_8__ {char* pbData; scalar_t__ cbData; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ DATA_BLOB ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 TYPE_1__ cipher ; 
 TYPE_1__ cipher_entropy ; 
 TYPE_1__ cipher_no_desc ; 
 int /*<<< orphan*/  desc ; 
 scalar_t__ key ; 
 int /*<<< orphan*/  lstrcmpW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCryptUnprotectData (TYPE_1__*,char**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  protected ; 
 scalar_t__ secret ; 
 scalar_t__ secret2 ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static void test_cryptunprotectdata(void)
{
    LONG r;
    DATA_BLOB plain;
    DATA_BLOB entropy;
    BOOL okay;
    WCHAR * data_desc;

    entropy.pbData=(void*)key;
    entropy.cbData=strlen(key)+1;

    /* fails in win2k */
    if (!protected)
    {
        skip("CryptProtectData failed to run\n");
        return;
    }

    plain.pbData=NULL;
    plain.cbData=0;

    SetLastError(0xDEADBEEF);
    okay = pCryptUnprotectData(&cipher,NULL,NULL,NULL,NULL,0,NULL);
    ok(!okay,"Decrypting without destination\n");
    r = GetLastError();
    ok(r == ERROR_INVALID_PARAMETER, "Wrong (%u) GetLastError seen\n",r);

    SetLastError(0xDEADBEEF);
    okay = pCryptUnprotectData(NULL,NULL,NULL,NULL,NULL,0,&plain);
    ok(!okay,"Decrypting without source\n");
    r = GetLastError();
    ok(r == ERROR_INVALID_PARAMETER, "Wrong (%u) GetLastError seen\n",r);

    plain.pbData=NULL;
    plain.cbData=0;

    SetLastError(0xDEADBEEF);
    okay = pCryptUnprotectData(&cipher_entropy,NULL,NULL,NULL,NULL,0,&plain);
    ok(!okay,"Decrypting without needed entropy\n");
    r = GetLastError();
    ok(r == ERROR_INVALID_DATA, "Wrong (%u) GetLastError seen\n", r);

    plain.pbData=NULL;
    plain.cbData=0;
    data_desc=NULL;

    /* without entropy */
    SetLastError(0xDEADBEEF);
    okay = pCryptUnprotectData(&cipher,&data_desc,NULL,NULL,NULL,0,&plain);
    ok(okay,"Decrypting without entropy\n");

    ok(plain.pbData!=NULL,"Plain DATA_BLOB missing data\n");
    ok(plain.cbData==strlen(secret)+1,"Plain DATA_BLOB wrong length\n");
    ok(!strcmp((const char*)plain.pbData,secret),"Plain does not match secret\n");
    ok(data_desc!=NULL,"Description not allocated\n");
    ok(!lstrcmpW(data_desc,desc),"Description does not match\n");

    LocalFree(plain.pbData);
    LocalFree(data_desc);

    plain.pbData=NULL;
    plain.cbData=0;
    data_desc=NULL;

    /* with wrong entropy */
    SetLastError(0xDEADBEEF);
    okay = pCryptUnprotectData(&cipher_entropy,&data_desc,&cipher_entropy,NULL,NULL,0,&plain);
    ok(!okay,"Decrypting with wrong entropy\n");
    r = GetLastError();
    ok(r == ERROR_INVALID_DATA, "Wrong (%u) GetLastError seen\n",r);

    /* with entropy */
    SetLastError(0xDEADBEEF);
    okay = pCryptUnprotectData(&cipher_entropy,&data_desc,&entropy,NULL,NULL,0,&plain);
    ok(okay,"Decrypting with entropy\n");

    ok(plain.pbData!=NULL,"Plain DATA_BLOB missing data\n");
    ok(plain.cbData==strlen(secret)+1,"Plain DATA_BLOB wrong length\n");
    ok(!strcmp((const char*)plain.pbData,secret),"Plain does not match secret\n");
    ok(data_desc!=NULL,"Description not allocated\n");
    ok(!lstrcmpW(data_desc,desc),"Description does not match\n");

    LocalFree(plain.pbData);
    LocalFree(data_desc);

    plain.pbData=NULL;
    plain.cbData=0;
    data_desc=NULL;

    /* with entropy but no description */
    SetLastError(0xDEADBEEF);
    okay = pCryptUnprotectData(&cipher_no_desc,&data_desc,&entropy,NULL,NULL,0,&plain);
    ok(okay,"Decrypting with entropy and no description\n");

    ok(plain.pbData!=NULL,"Plain DATA_BLOB missing data\n");
    ok(plain.cbData==strlen(secret2)+1,"Plain DATA_BLOB wrong length\n");
    ok(!strcmp((const char*)plain.pbData,secret2),"Plain does not match secret\n");
    ok(data_desc!=NULL,"Description not allocated\n");
    ok(data_desc[0]=='\0',"Description not empty\n");

    LocalFree(data_desc);
    LocalFree(plain.pbData);

    plain.pbData=NULL;
    plain.cbData=0;
}