#ifndef JUDAEMON_H
#define JUDAEMON_H

#ifdef _DEBUG
#define DEBUG(format, args...) g_print("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif

#include <X11/Xlib.h>

typedef struct _JuDaemon JuDaemon;
struct _JuDaemon {
	Display *display;

	/* XRandr Extension */
	gint rr_major_version;
	gint rr_minor_version;
	gint xrandr_event_base;
	gint xrandr_error_base;

	GPtrArray *modules;
	GPtrArray *components;
};

#endif
