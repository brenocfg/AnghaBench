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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int* CONTENTS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STREAM_NUMBER_CONTENTS ; 
 int STREAM_NUMBER_NOT_SET ; 

__attribute__((used)) static HRESULT open_pres_stream( IStorage *stg, int stream_number, IStream **stm )
{
    WCHAR pres[] = {2,'O','l','e','P','r','e','s',
                    '0' + (stream_number / 100) % 10,
                    '0' + (stream_number / 10) % 10,
                    '0' + stream_number % 10, 0};
    const WCHAR *name = pres;

    if (stream_number == STREAM_NUMBER_NOT_SET) return E_FAIL;
    if (stream_number == STREAM_NUMBER_CONTENTS) name = CONTENTS;

    return IStorage_OpenStream( stg, name, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, stm );
}