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
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IMimeMessage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMimeMessage_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMimeMessage_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMimeMessage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MimeMessage_create (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT load_mime_message(IStream *stream, IMimeMessage **ret)
{
    IMimeMessage *mime_message;
    HRESULT hres;

    hres = MimeMessage_create(NULL, (void**)&mime_message);
    if(FAILED(hres))
        return hres;

    IMimeMessage_InitNew(mime_message);

    hres = IMimeMessage_Load(mime_message, stream);
    if(FAILED(hres)) {
        IMimeMessage_Release(mime_message);
        return hres;
    }

    *ret = mime_message;
    return S_OK;
}