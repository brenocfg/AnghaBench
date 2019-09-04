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
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PI2C_CALLBACKS ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_HALF () ; 
 scalar_t__ HIGH ; 
 int /*<<< orphan*/  INFO_ (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ LOW ; 
 scalar_t__ READ_SCL () ; 
 scalar_t__ READ_SDA () ; 
 int /*<<< orphan*/  VIDEOPRT ; 
 int /*<<< orphan*/  WRITE_SCL (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_SDA (scalar_t__) ; 

__attribute__((used)) static BOOL
I2CWrite(PVOID HwDeviceExtension, PI2C_CALLBACKS i2c, UCHAR Data)
{
   UCHAR Bit;
   BOOL Ack;

   /* transmit data */
   for (Bit = (1 << 7); Bit != 0; Bit >>= 1)
     {
        WRITE_SCL(LOW);
        WRITE_SDA((Data & Bit) ? HIGH : LOW);
        DELAY_HALF();
        WRITE_SCL(HIGH);
        DELAY_HALF();
     }

   /* get ack */
   WRITE_SCL(LOW);
   WRITE_SDA(HIGH);
   DELAY_HALF();
   WRITE_SCL(HIGH);
   do
     {
        DELAY_HALF();
     }
   while (READ_SCL() != HIGH);
   Ack = (READ_SDA() == LOW);
   DELAY_HALF();

   INFO_(VIDEOPRT, "I2CWrite: %s\n", Ack ? "Ack" : "Nak");
   return Ack;
}