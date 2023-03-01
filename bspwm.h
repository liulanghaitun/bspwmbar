/* See LICENSE file for copyright and license details. */

#ifndef BSPWMBAR_BSPWM_H_
#define BSPWMBAR_BSPWM_H_
#include "util.h"
/* bspwm commands */
#define SUBSCRIBE_REPORT "subscribe\0report"

typedef enum {
	BSPWM_DESKTOP_FREE     = 0,
	BSPWM_DESKTOP_FOCUSED  = 1 << 1,
	BSPWM_DESKTOP_OCCUPIED = 1 << 2,
	BSPWM_DESKTOP_URGENT   = 1 << 3,
} bspwm_desktop_state_t;

typedef struct _bspwm_desktop_t bspwm_desktop_t;
typedef struct _bspwm_monitor_t bspwm_monitor_t;

typedef struct {
	list_head monitors;
} bspwm_t;

struct _bspwm_desktop_t {
	char *name;
	bspwm_desktop_state_t state;

	list_head head;
};

struct _bspwm_monitor_t {
	char *name;
	bool is_active;

	/* cache of number of desktops */
	list_head desktops;

	list_head head;
};

bspwm_desktop_state_t
bspwm_desktop_state(bspwm_desktop_t *);

bspwm_t* get_bspwm_t();
void sendMessage(char* buffer,size_t length);

#endif // BSPWM_BAR_BSPWM_H_
