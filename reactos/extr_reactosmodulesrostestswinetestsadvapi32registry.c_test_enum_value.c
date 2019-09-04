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
typedef  int /*<<< orphan*/  xxxW ;
typedef  int /*<<< orphan*/  testW ;
typedef  int /*<<< orphan*/  foobarW ;
typedef  float WCHAR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int GetVersion () ; 
 int REG_BINARY ; 
 int REG_EXPAND_SZ ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegCreateKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int RegEnumValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int RegEnumValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 int RegSetValueExW (int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  memcmp (float*,float const*,int) ; 
 int /*<<< orphan*/  memcpy (float*,float const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pRegGetValueA ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_enum_value(void)
{
    DWORD res;
    HKEY test_key;
    char value[20], data[20];
    WCHAR valueW[20], dataW[20];
    DWORD val_count, data_count, type;
    static const WCHAR foobarW[] = {'f','o','o','b','a','r',0};
    static const WCHAR testW[] = {'T','e','s','t',0};
    static const WCHAR xxxW[] = {'x','x','x','x','x','x','x','x',0};

    /* create the working key for new 'Test' value */
    res = RegCreateKeyA( hkey_main, "TestKey", &test_key );
    ok( res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res);

    /* check NULL data with zero length */
    res = RegSetValueExA( test_key, "Test", 0, REG_SZ, NULL, 0 );
    if (GetVersion() & 0x80000000)
        ok( res == ERROR_INVALID_PARAMETER, "RegSetValueExA returned %d\n", res );
    else
        ok( !res, "RegSetValueExA returned %d\n", res );
    res = RegSetValueExA( test_key, "Test", 0, REG_EXPAND_SZ, NULL, 0 );
    ok( ERROR_SUCCESS == res || ERROR_INVALID_PARAMETER == res, "RegSetValueExA returned %d\n", res );
    res = RegSetValueExA( test_key, "Test", 0, REG_BINARY, NULL, 0 );
    ok( ERROR_SUCCESS == res || ERROR_INVALID_PARAMETER == res, "RegSetValueExA returned %d\n", res );

    /* test reading the value and data without setting them */
    val_count = 20;
    data_count = 20;
    type = 1234;
    strcpy( value, "xxxxxxxxxx" );
    strcpy( data, "xxxxxxxxxx" );
    res = RegEnumValueA( test_key, 0, value, &val_count, NULL, &type, (LPBYTE)data, &data_count );
    ok( res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res );
    ok( val_count == 4, "val_count set to %d instead of 4\n", val_count );
    ok( data_count == 0, "data_count set to %d instead of 0\n", data_count );
    ok( type == REG_BINARY, "type %d is not REG_BINARY\n", type );
    ok( !strcmp( value, "Test" ), "value is '%s' instead of Test\n", value );
    ok( !strcmp( data, "xxxxxxxxxx" ), "data is '%s' instead of xxxxxxxxxx\n", data );

    val_count = 20;
    data_count = 20;
    type = 1234;
    memcpy( valueW, xxxW, sizeof(xxxW) );
    memcpy( dataW, xxxW, sizeof(xxxW) );
    res = RegEnumValueW( test_key, 0, valueW, &val_count, NULL, &type, (BYTE*)dataW, &data_count );
    ok( res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res );
    ok( val_count == 4, "val_count set to %d instead of 4\n", val_count );
    ok( data_count == 0, "data_count set to %d instead of 0\n", data_count );
    ok( type == REG_BINARY, "type %d is not REG_BINARY\n", type );
    ok( !memcmp( valueW, testW, sizeof(testW) ), "value is not 'Test'\n" );
    ok( !memcmp( dataW, xxxW, sizeof(xxxW) ), "data is not 'xxxxxxxxxx'\n" );

    res = RegSetValueExA( test_key, "Test", 0, REG_SZ, (const BYTE *)"foobar", 7 );
    ok( res == 0, "RegSetValueExA failed error %d\n", res );

    /* overflow both name and data */
    val_count = 2;
    data_count = 2;
    type = 1234;
    strcpy( value, "xxxxxxxxxx" );
    strcpy( data, "xxxxxxxxxx" );
    res = RegEnumValueA( test_key, 0, value, &val_count, NULL, &type, (LPBYTE)data, &data_count );
    ok( res == ERROR_MORE_DATA, "expected ERROR_MORE_DATA, got %d\n", res );
    ok( val_count == 2, "val_count set to %d\n", val_count );
    ok( data_count == 7 || broken( data_count == 8 ), "data_count set to %d instead of 7\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !strcmp( value, "xxxxxxxxxx" ), "value set to '%s'\n", value );
    ok( !strcmp( data, "xxxxxxxxxx" ), "data set to '%s'\n", data );

    /* overflow name */
    val_count = 3;
    data_count = 20;
    type = 1234;
    strcpy( value, "xxxxxxxxxx" );
    strcpy( data, "xxxxxxxxxx" );
    res = RegEnumValueA( test_key, 0, value, &val_count, NULL, &type, (LPBYTE)data, &data_count );
    ok( res == ERROR_MORE_DATA, "expected ERROR_MORE_DATA, got %d\n", res );
    ok( val_count == 3, "val_count set to %d\n", val_count );
    ok( data_count == 7 || broken( data_count == 8 ), "data_count set to %d instead of 7\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    /* v5.1.2600.0 (XP Home and Professional) does not touch value or data in this case */
    ok( !strcmp( value, "Te" ) || !strcmp( value, "xxxxxxxxxx" ), 
        "value set to '%s' instead of 'Te' or 'xxxxxxxxxx'\n", value );
    ok( !strcmp( data, "foobar" ) || !strcmp( data, "xxxxxxx" ) || broken( !strcmp( data, "xxxxxxxx" ) && data_count == 8 ),
        "data set to '%s' instead of 'foobar' or 'xxxxxxx'\n", data );

    /* overflow empty name */
    val_count = 0;
    data_count = 20;
    type = 1234;
    strcpy( value, "xxxxxxxxxx" );
    strcpy( data, "xxxxxxxxxx" );
    res = RegEnumValueA( test_key, 0, value, &val_count, NULL, &type, (LPBYTE)data, &data_count );
    ok( res == ERROR_MORE_DATA, "expected ERROR_MORE_DATA, got %d\n", res );
    ok( val_count == 0, "val_count set to %d\n", val_count );
    ok( data_count == 7 || broken( data_count == 8 ), "data_count set to %d instead of 7\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !strcmp( value, "xxxxxxxxxx" ), "value set to '%s'\n", value );
    /* v5.1.2600.0 (XP Home and Professional) does not touch data in this case */
    ok( !strcmp( data, "foobar" ) || !strcmp( data, "xxxxxxx" ) || broken( !strcmp( data, "xxxxxxxx" ) && data_count == 8 ),
        "data set to '%s' instead of 'foobar' or 'xxxxxxx'\n", data );

    /* overflow data */
    val_count = 20;
    data_count = 2;
    type = 1234;
    strcpy( value, "xxxxxxxxxx" );
    strcpy( data, "xxxxxxxxxx" );
    res = RegEnumValueA( test_key, 0, value, &val_count, NULL, &type, (LPBYTE)data, &data_count );
    ok( res == ERROR_MORE_DATA, "expected ERROR_MORE_DATA, got %d\n", res );
    ok( val_count == 20, "val_count set to %d\n", val_count );
    ok( data_count == 7, "data_count set to %d instead of 7\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !strcmp( value, "xxxxxxxxxx" ), "value set to '%s'\n", value );
    ok( !strcmp( data, "xxxxxxxxxx" ), "data set to '%s'\n", data );

    /* no overflow */
    val_count = 20;
    data_count = 20;
    type = 1234;
    strcpy( value, "xxxxxxxxxx" );
    strcpy( data, "xxxxxxxxxx" );
    res = RegEnumValueA( test_key, 0, value, &val_count, NULL, &type, (LPBYTE)data, &data_count );
    ok( res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res );
    ok( val_count == 4, "val_count set to %d instead of 4\n", val_count );
    ok( data_count == 7, "data_count set to %d instead of 7\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !strcmp( value, "Test" ), "value is '%s' instead of Test\n", value );
    ok( !strcmp( data, "foobar" ), "data is '%s' instead of foobar\n", data );

    if (pRegGetValueA) /* avoid a crash on Windows 2000 */
    {
        /* no value and no val_count parameter */
        data_count = 20;
        type = 1234;
        strcpy( data, "xxxxxxxxxx" );
        res = RegEnumValueA( test_key, 0, NULL, NULL, NULL, &type, (BYTE*)data, &data_count );
        ok( res == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", res );

        /* no value parameter */
        val_count = 20;
        data_count = 20;
        type = 1234;
        strcpy( data, "xxxxxxxxxx" );
        res = RegEnumValueA( test_key, 0, NULL, &val_count, NULL, &type, (BYTE*)data, &data_count );
        ok( res == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", res );

        /* no val_count parameter */
        data_count = 20;
        type = 1234;
        strcpy( value, "xxxxxxxxxx" );
        strcpy( data, "xxxxxxxxxx" );
        res = RegEnumValueA( test_key, 0, value, NULL, NULL, &type, (BYTE*)data, &data_count );
        ok( res == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", res );
    }

    /* Unicode tests */

    SetLastError(0xdeadbeef);
    res = RegSetValueExW( test_key, testW, 0, REG_SZ, (const BYTE *)foobarW, 7*sizeof(WCHAR) );
    if (res==0 && GetLastError()==ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("RegSetValueExW is not implemented\n");
        goto cleanup;
    }
    ok( res == 0, "RegSetValueExW failed error %d\n", res );

    /* overflow both name and data */
    val_count = 2;
    data_count = 2;
    type = 1234;
    memcpy( valueW, xxxW, sizeof(xxxW) );
    memcpy( dataW, xxxW, sizeof(xxxW) );
    res = RegEnumValueW( test_key, 0, valueW, &val_count, NULL, &type, (BYTE*)dataW, &data_count );
    ok( res == ERROR_MORE_DATA, "expected ERROR_MORE_DATA, got %d\n", res );
    ok( val_count == 2, "val_count set to %d\n", val_count );
    ok( data_count == 7*sizeof(WCHAR), "data_count set to %d instead of 7*sizeof(WCHAR)\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !memcmp( valueW, xxxW, sizeof(xxxW) ), "value modified\n" );
    ok( !memcmp( dataW, xxxW, sizeof(xxxW) ), "data modified\n" );

    /* overflow name */
    val_count = 3;
    data_count = 20;
    type = 1234;
    memcpy( valueW, xxxW, sizeof(xxxW) );
    memcpy( dataW, xxxW, sizeof(xxxW) );
    res = RegEnumValueW( test_key, 0, valueW, &val_count, NULL, &type, (BYTE*)dataW, &data_count );
    ok( res == ERROR_MORE_DATA, "expected ERROR_MORE_DATA, got %d\n", res );
    ok( val_count == 3, "val_count set to %d\n", val_count );
    ok( data_count == 7*sizeof(WCHAR), "data_count set to %d instead of 7*sizeof(WCHAR)\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !memcmp( valueW, xxxW, sizeof(xxxW) ), "value modified\n" );
    ok( !memcmp( dataW, xxxW, sizeof(xxxW) ), "data modified\n" );

    /* overflow data */
    val_count = 20;
    data_count = 2;
    type = 1234;
    memcpy( valueW, xxxW, sizeof(xxxW) );
    memcpy( dataW, xxxW, sizeof(xxxW) );
    res = RegEnumValueW( test_key, 0, valueW, &val_count, NULL, &type, (BYTE*)dataW, &data_count );
    ok( res == ERROR_MORE_DATA, "expected ERROR_MORE_DATA, got %d\n", res );
    ok( val_count == 4, "val_count set to %d instead of 4\n", val_count );
    ok( data_count == 7*sizeof(WCHAR), "data_count set to %d instead of 7*sizeof(WCHAR)\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !memcmp( valueW, testW, sizeof(testW) ), "value is not 'Test'\n" );
    ok( !memcmp( dataW, xxxW, sizeof(xxxW) ), "data modified\n" );

    /* no overflow */
    val_count = 20;
    data_count = 20;
    type = 1234;
    memcpy( valueW, xxxW, sizeof(xxxW) );
    memcpy( dataW, xxxW, sizeof(xxxW) );
    res = RegEnumValueW( test_key, 0, valueW, &val_count, NULL, &type, (BYTE*)dataW, &data_count );
    ok( res == ERROR_SUCCESS, "expected ERROR_SUCCESS, got %d\n", res );
    ok( val_count == 4, "val_count set to %d instead of 4\n", val_count );
    ok( data_count == 7*sizeof(WCHAR), "data_count set to %d instead of 7*sizeof(WCHAR)\n", data_count );
    ok( type == REG_SZ, "type %d is not REG_SZ\n", type );
    ok( !memcmp( valueW, testW, sizeof(testW) ), "value is not 'Test'\n" );
    ok( !memcmp( dataW, foobarW, sizeof(foobarW) ), "data is not 'foobar'\n" );

    if (pRegGetValueA) /* avoid a crash on Windows 2000 */
    {
        /* no valueW and no val_count parameter */
        data_count = 20;
        type = 1234;
        memcpy( dataW, xxxW, sizeof(xxxW) );
        res = RegEnumValueW( test_key, 0, NULL, NULL, NULL, &type, (BYTE*)dataW, &data_count );
        ok( res == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", res );

        /* no valueW parameter */
        val_count = 20;
        data_count = 20;
        type = 1234;
        memcpy( dataW, xxxW, sizeof(xxxW) );
        res = RegEnumValueW( test_key, 0, NULL, &val_count, NULL, &type, (BYTE*)dataW, &data_count );
        ok( res == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", res );

        /* no val_count parameter */
        data_count = 20;
        type = 1234;
        memcpy( valueW, xxxW, sizeof(xxxW) );
        memcpy( dataW, xxxW, sizeof(xxxW) );
        res = RegEnumValueW( test_key, 0, valueW, NULL, NULL, &type, (BYTE*)dataW, &data_count );
        ok( res == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", res );
    }

cleanup:
    RegDeleteKeyA(test_key, "");
    RegCloseKey(test_key);
}