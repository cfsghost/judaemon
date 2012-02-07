#ifndef JD_MODULE_CLASS_H
#define JD_MODULE_CLASS_H

#include <glib.h>
#include <gmodule.h>
#include <judaemon/conf.h>

typedef struct _JdWidget JdWidget;
struct _JdModuleClass {
	gchar *name;
	gchar *version;
	gchar *description;
	void (*constructor)(JdWidget *, JsonNode *);
};
typedef struct _JdModuleClass JdModuleClass;

struct _JdModule {
	GModule *gmodule;
	JdModuleClass *module_class;
};
typedef struct _JdModule JdModule;

#endif
