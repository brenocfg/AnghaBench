#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ getline_ctx ;
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  adns__debug (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  adns__diag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char const*,char*) ; 
 int /*<<< orphan*/  gl_file ; 
 int /*<<< orphan*/  readconfiggeneric (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  saveerr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void readconfig(adns_state ads, const char *filename, int warnmissing) {
  getline_ctx gl_ctx;

  gl_ctx.file= fopen(filename,"r");
  if (!gl_ctx.file) {
    if (errno == ENOENT) {
      if (warnmissing)
	adns__debug(ads,-1,0,"configuration file `%s' does not exist",filename);
      return;
    }
    saveerr(ads,errno);
    adns__diag(ads,-1,0,"cannot open configuration file `%s': %s",
	       filename,strerror(errno));
    return;
  }

  readconfiggeneric(ads,filename,gl_file,gl_ctx);

  fclose(gl_ctx.file);
}