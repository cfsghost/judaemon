#ifndef JD_COMPONENT_H
#define JD_COMPONENT_H

#include <X11/Xlib.h>
#include <judaemon/module.h>

struct _JdComponent { 
	gpointer parent;
	JdModule *module;
	gpointer priv;

	Display *display;
};
typedef struct _JdComponent JdComponent;

#endif
