/* See LICENSE file for copyright and license details. */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bspwmbar.h"
#include "util.h"

static char *format = " %d%%";

void brightness(draw_context_t *dc, module_option_t *opts) {
  static time_t prevtime;
  static uintmax_t _brightness, brightness, max_brightness;

  static int f_bright_found = -1;
  static int f_max_bright_found = -1;

  static char bpath[128], mpath[128];
  snprintf(bpath, 128, "/sys/class/backlight/%s/brightness",
           opts->backlight.display);
  snprintf(mpath, 128, "/sys/class/backlight/%s/max_brightness",
           opts->backlight.display);

  check_file(bpath, &f_bright_found);
  check_file(mpath, &f_max_bright_found);

  if (!f_bright_found)
    return;

  time_t curtime = time(NULL);
  if (curtime - prevtime < 1)
    goto DRAW_BRIGHTNESS;
  prevtime = curtime;

  if (pscanf(bpath, "%ju", &_brightness) == -1) {
    return;
  }

  if (!f_max_bright_found || pscanf(mpath, "%ju", &max_brightness) == -1) {
    max_brightness = 1;
  }

  brightness = 100 * _brightness / max_brightness;

DRAW_BRIGHTNESS:
  sprintf(buf, "%s %ld%s", opts->backlight.prefix, brightness,
          opts->backlight.suffix);
  draw_text(dc, buf);
}
