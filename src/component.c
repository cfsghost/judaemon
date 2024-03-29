#include <stdlib.h>
#include <glib.h>
#include <json-glib/json-glib.h>
#include <sys/stat.h>
#include <judaemon/conf.h>
#include <judaemon/component.h>
#include "judaemon.h"
#include "component.h"
#include "module.h"

JdComponent *
jd_component_new(JuDaemon *judaemon, const gchar *module_name)
{
	JdComponent *comp;

	DEBUG("Create a component - \"%s\"\n", module_name);
	comp = (JdComponent *)g_slice_new0(JdComponent);
	comp->module = jd_module_find(judaemon, module_name);

	/* Intial variables */
	comp->display = judaemon->display;

	return comp;
}

void
jd_component_init(JuDaemon *judaemon, JdComponent *comp, JsonNode *node)
{
	jd_module_constructor(comp, node);

	/* X event handler */
	if (comp->module->module_class->xevent_handler)
		clutter_x11_add_filter(jd_module_xevent_handler, comp);
}
