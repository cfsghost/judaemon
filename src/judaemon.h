#ifndef JUDAEMON_H
#define JUDAEMON_H

#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif

typedef struct _JuDaemon JuDaemon;
struct _JuDaemon {
	/* XRandr Extension */
	gint rr_major_version;
	gint rr_minor_version;
	gint xrandr_event_base;
	gint xrandr_error_base;

	GPtrArray *modules;
	GPtrArray *components;
};

#endif
