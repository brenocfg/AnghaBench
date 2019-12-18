#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINTN ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_13__ {int /*<<< orphan*/  WaitForEvent; } ;
struct TYPE_12__ {TYPE_3__* ConIn; } ;
struct TYPE_9__ {int /*<<< orphan*/  UnicodeChar; int /*<<< orphan*/  ScanCode; } ;
struct TYPE_8__ {int KeyShiftState; } ;
struct TYPE_11__ {int /*<<< orphan*/  UnicodeChar; int /*<<< orphan*/  ScanCode; TYPE_2__ Key; TYPE_1__ KeyState; } ;
struct TYPE_10__ {int /*<<< orphan*/  ReadKeyStroke; int /*<<< orphan*/  ReadKeyStrokeEx; int /*<<< orphan*/  WaitForKey; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  TYPE_3__ EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL ;
typedef  TYPE_4__ EFI_KEY_DATA ;
typedef  TYPE_4__ EFI_INPUT_KEY ;
typedef  int /*<<< orphan*/  EFI_GUID ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_7__* BS ; 
 int /*<<< orphan*/  EFI_ALT_PRESSED ; 
 int /*<<< orphan*/  EFI_CONTROL_PRESSED ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int EFI_LEFT_ALT_PRESSED ; 
 int EFI_LEFT_CONTROL_PRESSED ; 
 int EFI_RIGHT_ALT_PRESSED ; 
 int EFI_RIGHT_CONTROL_PRESSED ; 
 int EFI_SHIFT_STATE_VALID ; 
 int /*<<< orphan*/  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID ; 
 int /*<<< orphan*/  KEYPRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibLocateProtocol (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_6__* ST ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  uefi_call_wrapper (int /*<<< orphan*/ ,int,...) ; 

EFI_STATUS console_key_read(UINT64 *key, BOOLEAN wait) {
        EFI_GUID EfiSimpleTextInputExProtocolGuid = EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID;
        static EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *TextInputEx;
        static BOOLEAN checked;
        UINTN index;
        EFI_INPUT_KEY k;
        EFI_STATUS err;

        if (!checked) {
                err = LibLocateProtocol(&EfiSimpleTextInputExProtocolGuid, (VOID **)&TextInputEx);
                if (EFI_ERROR(err))
                        TextInputEx = NULL;

                checked = TRUE;
        }

        /* wait until key is pressed */
        if (wait)
                uefi_call_wrapper(BS->WaitForEvent, 3, 1, &ST->ConIn->WaitForKey, &index);

        if (TextInputEx) {
                EFI_KEY_DATA keydata;
                UINT64 keypress;

                err = uefi_call_wrapper(TextInputEx->ReadKeyStrokeEx, 2, TextInputEx, &keydata);
                if (!EFI_ERROR(err)) {
                        UINT32 shift = 0;

                        /* do not distinguish between left and right keys */
                        if (keydata.KeyState.KeyShiftState & EFI_SHIFT_STATE_VALID) {
                                if (keydata.KeyState.KeyShiftState & (EFI_RIGHT_CONTROL_PRESSED|EFI_LEFT_CONTROL_PRESSED))
                                        shift |= EFI_CONTROL_PRESSED;
                                if (keydata.KeyState.KeyShiftState & (EFI_RIGHT_ALT_PRESSED|EFI_LEFT_ALT_PRESSED))
                                        shift |= EFI_ALT_PRESSED;
                        };

                        /* 32 bit modifier keys + 16 bit scan code + 16 bit unicode */
                        keypress = KEYPRESS(shift, keydata.Key.ScanCode, keydata.Key.UnicodeChar);
                        if (keypress > 0) {
                                *key = keypress;
                                return 0;
                        }
                }
        }

        /* fallback for firmware which does not support SimpleTextInputExProtocol
         *
         * This is also called in case ReadKeyStrokeEx did not return a key, because
         * some broken firmwares offer SimpleTextInputExProtocol, but never actually
         * handle any key. */
        err  = uefi_call_wrapper(ST->ConIn->ReadKeyStroke, 2, ST->ConIn, &k);
        if (EFI_ERROR(err))
                return err;

        *key = KEYPRESS(0, k.ScanCode, k.UnicodeChar);
        return 0;
}