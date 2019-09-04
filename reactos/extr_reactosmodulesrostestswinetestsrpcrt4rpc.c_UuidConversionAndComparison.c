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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UUID ;
typedef  scalar_t__ RPC_STATUS ;
typedef  char* LPWSTR ;
typedef  char* LPSTR ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ RPC_S_INVALID_STRING_UUID ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  RpcStringFreeA (unsigned char**) ; 
 int /*<<< orphan*/  RpcStringFreeW (char**) ; 
 int UuidEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ UuidFromStringA (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ UuidFromStringW (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ UuidToStringA (int /*<<< orphan*/ *,unsigned char**) ; 
 scalar_t__ UuidToStringW (int /*<<< orphan*/ *,char**) ; 
 int** Uuid_Comparison_Grid ; 
 int /*<<< orphan*/ * Uuid_Table ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void UuidConversionAndComparison(void) {
    CHAR strx[100], x;
    LPSTR str = strx;
    WCHAR wstrx[100], wx;
    LPWSTR wstr = wstrx;

    UUID Uuid1, Uuid2, *PUuid1, *PUuid2;
    RPC_STATUS rslt;

    int i1,i2;

    /* Uuid Equality */
    for (i1 = 0; i1 < 11; i1++)
        for (i2 = 0; i2 < 11; i2++) {
	    if (i1 < 10) {
	        Uuid1 = Uuid_Table[i1]; 
		PUuid1 = &Uuid1;
            } else {
	        PUuid1 = NULL;
	    }        
	    if (i2 < 10) {
	        Uuid2 = Uuid_Table[i2];
		PUuid2 = &Uuid2;
            } else {
	        PUuid2 = NULL;
	    }
	    ok( (UuidEqual(PUuid1, PUuid2, &rslt) == Uuid_Comparison_Grid[i1][i2]), "UUID Equality\n" );
        }

    /* Uuid to String to Uuid (char) */
    for (i1 = 0; i1 < 10; i1++) {
        Uuid1 = Uuid_Table[i1];
	ok( (UuidToStringA(&Uuid1, (unsigned char**)&str) == RPC_S_OK), "Simple UUID->String copy\n" );
	ok( (UuidFromStringA((unsigned char*)str, &Uuid2) == RPC_S_OK), "Simple String->UUID copy from generated UUID String\n" );
	ok( UuidEqual(&Uuid1, &Uuid2, &rslt), "Uuid -> String -> Uuid transform\n" );
	/* invalid uuid tests  -- size of valid UUID string=36 */
	for (i2 = 0; i2 < 36; i2++) {
	    x = str[i2];
	    str[i2] = 'g'; /* whatever, but "g" is a good boundary condition */
	    ok( (UuidFromStringA((unsigned char*)str, &Uuid1) == RPC_S_INVALID_STRING_UUID), "Invalid UUID String\n" );
	    str[i2] = x; /* change it back so remaining tests are interesting. */
	}
	RpcStringFreeA((unsigned char **)&str);
    }

    /* Uuid to String to Uuid (wchar) */
    for (i1 = 0; i1 < 10; i1++) {
        Uuid1 = Uuid_Table[i1];
        rslt=UuidToStringW(&Uuid1, &wstr);
        ok( (rslt == RPC_S_OK), "Simple UUID->WString copy\n" );
        ok( (UuidFromStringW(wstr, &Uuid2) == RPC_S_OK), "Simple WString->UUID copy from generated UUID String\n" );
        ok( UuidEqual(&Uuid1, &Uuid2, &rslt), "Uuid -> WString -> Uuid transform\n" );
	/* invalid uuid tests  -- size of valid UUID string=36 */
	for (i2 = 0; i2 < 36; i2++) {
	    wx = wstr[i2];
	    wstr[i2] = 'g'; /* whatever, but "g" is a good boundary condition */
	    ok( (UuidFromStringW(wstr, &Uuid1) == RPC_S_INVALID_STRING_UUID), "Invalid UUID WString\n" );
	    wstr[i2] = wx; /* change it back so remaining tests are interesting. */
	}
	RpcStringFreeW(&wstr);
    }
}