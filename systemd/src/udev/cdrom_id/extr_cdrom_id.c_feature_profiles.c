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

/* Variables and functions */
 int cd_bd ; 
 int cd_bd_r ; 
 int cd_bd_re ; 
 int cd_cd_r ; 
 int cd_cd_rom ; 
 int cd_cd_rw ; 
 int cd_dvd_plus_r ; 
 int cd_dvd_plus_r_dl ; 
 int cd_dvd_plus_rw ; 
 int cd_dvd_plus_rw_dl ; 
 int cd_dvd_ram ; 
 int cd_dvd_rom ; 
 int cd_dvd_rw ; 
 int cd_hddvd ; 
 int cd_hddvd_r ; 
 int cd_hddvd_rw ; 
 int cd_mo ; 
 int /*<<< orphan*/  log_debug (char*,int) ; 

__attribute__((used)) static int feature_profiles(const unsigned char *profiles, size_t size) {
        unsigned i;

        for (i = 0; i+4 <= size; i += 4) {
                int profile;

                profile = profiles[i] << 8 | profiles[i+1];
                switch (profile) {
                case 0x03:
                case 0x04:
                case 0x05:
                        log_debug("profile 0x%02x mo", profile);
                        cd_mo = 1;
                        break;
                case 0x08:
                        log_debug("profile 0x%02x cd_rom", profile);
                        cd_cd_rom = 1;
                        break;
                case 0x09:
                        log_debug("profile 0x%02x cd_r", profile);
                        cd_cd_r = 1;
                        break;
                case 0x0A:
                        log_debug("profile 0x%02x cd_rw", profile);
                        cd_cd_rw = 1;
                        break;
                case 0x10:
                        log_debug("profile 0x%02x dvd_rom", profile);
                        cd_dvd_rom = 1;
                        break;
                case 0x12:
                        log_debug("profile 0x%02x dvd_ram", profile);
                        cd_dvd_ram = 1;
                        break;
                case 0x13:
                case 0x14:
                        log_debug("profile 0x%02x dvd_rw", profile);
                        cd_dvd_rw = 1;
                        break;
                case 0x1B:
                        log_debug("profile 0x%02x dvd_plus_r", profile);
                        cd_dvd_plus_r = 1;
                        break;
                case 0x1A:
                        log_debug("profile 0x%02x dvd_plus_rw", profile);
                        cd_dvd_plus_rw = 1;
                        break;
                case 0x2A:
                        log_debug("profile 0x%02x dvd_plus_rw_dl", profile);
                        cd_dvd_plus_rw_dl = 1;
                        break;
                case 0x2B:
                        log_debug("profile 0x%02x dvd_plus_r_dl", profile);
                        cd_dvd_plus_r_dl = 1;
                        break;
                case 0x40:
                        cd_bd = 1;
                        log_debug("profile 0x%02x bd", profile);
                        break;
                case 0x41:
                case 0x42:
                        cd_bd_r = 1;
                        log_debug("profile 0x%02x bd_r", profile);
                        break;
                case 0x43:
                        cd_bd_re = 1;
                        log_debug("profile 0x%02x bd_re", profile);
                        break;
                case 0x50:
                        cd_hddvd = 1;
                        log_debug("profile 0x%02x hddvd", profile);
                        break;
                case 0x51:
                        cd_hddvd_r = 1;
                        log_debug("profile 0x%02x hddvd_r", profile);
                        break;
                case 0x52:
                        cd_hddvd_rw = 1;
                        log_debug("profile 0x%02x hddvd_rw", profile);
                        break;
                default:
                        log_debug("profile 0x%02x <ignored>", profile);
                        break;
                }
        }
        return 0;
}