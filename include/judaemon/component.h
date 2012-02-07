#ifndef JD_COMPONENT_H
#define JD_COMPONENT_H

#include <clutter/clutter.h>
#include <judaemon/module.h>

struct _JdComponent { 
	gpointer parent;
	JdModule *module;
	gpointer priv;
};
typedef struct _JdComponent JdComponent;

#endif
