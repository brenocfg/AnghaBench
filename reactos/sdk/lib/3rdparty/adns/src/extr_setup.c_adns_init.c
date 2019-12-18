#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* adns_state ;
typedef  int /*<<< orphan*/  adns_initflags ;
struct TYPE_13__ {scalar_t__ configerrno; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  GetWindowsDirectory (char*,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SECURE_PATH_LEN ; 
 int /*<<< orphan*/  adns__consistency (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_entex ; 
 int /*<<< orphan*/  ccf_options (TYPE_1__*,char*,int,char const*) ; 
 int /*<<< orphan*/  ccf_search (TYPE_1__*,char*,int,char*) ; 
 int /*<<< orphan*/  init_abort (TYPE_1__*) ; 
 int init_begin (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int init_finish (TYPE_1__*) ; 
 char* instrum_getenv (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  readconfig (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  readconfigenv (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  readconfigenvtext (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

int adns_init(adns_state *ads_r, adns_initflags flags, FILE *diagfile) {
  adns_state ads;
  const char *res_options, *adns_res_options;
  int r;
#ifdef ADNS_JGAA_WIN32
  #define SECURE_PATH_LEN (MAX_PATH - 64)
  char PathBuf[MAX_PATH];
#endif

  r= init_begin(&ads, flags, diagfile ? diagfile : stderr);
  if (r) return r;

  res_options= instrum_getenv(ads,"RES_OPTIONS");
  adns_res_options= instrum_getenv(ads,"ADNS_RES_OPTIONS");
  ccf_options(ads,"RES_OPTIONS",-1,res_options);
  ccf_options(ads,"ADNS_RES_OPTIONS",-1,adns_res_options);

#ifdef ADNS_JGAA_WIN32
  GetWindowsDirectory(PathBuf, SECURE_PATH_LEN);
  strcat(PathBuf,"\\resolv.conf");
  readconfig(ads,PathBuf,1);
  GetWindowsDirectory(PathBuf, SECURE_PATH_LEN);
  strcat(PathBuf,"\\resolv-adns.conf");
  readconfig(ads,PathBuf,0);
  GetWindowsDirectory(PathBuf, SECURE_PATH_LEN);
  strcat(PathBuf,"\\System32\\Drivers\\etc\\resolv.conf");
  readconfig(ads,PathBuf,1);
  GetWindowsDirectory(PathBuf, SECURE_PATH_LEN);
  strcat(PathBuf,"\\System32\\Drivers\\etc\\resolv-adns.conf");
  readconfig(ads,PathBuf,0);
#else
  readconfig(ads,"/etc/resolv.conf",1);
  readconfig(ads,"/etc/resolv-adns.conf",0);
#endif

  readconfigenv(ads,"RES_CONF");
  readconfigenv(ads,"ADNS_RES_CONF");

  readconfigenvtext(ads,"RES_CONF_TEXT");
  readconfigenvtext(ads,"ADNS_RES_CONF_TEXT");

  ccf_options(ads,"RES_OPTIONS",-1,res_options);
  ccf_options(ads,"ADNS_RES_OPTIONS",-1,adns_res_options);

  ccf_search(ads,"LOCALDOMAIN",-1,instrum_getenv(ads,"LOCALDOMAIN"));
  ccf_search(ads,"ADNS_LOCALDOMAIN",-1,instrum_getenv(ads,"ADNS_LOCALDOMAIN"));

  if (ads->configerrno && ads->configerrno != EINVAL) {
    r= ads->configerrno;
    init_abort(ads);
    return r;
  }

  r= init_finish(ads);
  if (r) return r;

  adns__consistency(ads,0,cc_entex);
  *ads_r= ads;
  return 0;
}