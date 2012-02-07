#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <sys/stat.h>
#include <clutter/clutter.h>
#include <clutter/x11/clutter-x11.h>
#include <judaemon/conf.h>
#include <judaemon/module.h>
#include <judaemon/component.h>
#include "judaemon.h"
#include "module.h"

JdModule *
jd_module_load(const gchar *filename)
{
	JdModule *module;

	DEBUG("Load module: %s\n", filename);

	module = (JdModule *)g_slice_new0(JdModule);

	module->gmodule = g_module_open(filename, G_MODULE_BIND_LAZY);
	if (module->gmodule == NULL) {
		g_slice_free(JdModule, module);
		DEBUG("Failed to load: %s\n", filename);
		return NULL;
	}

	if (!g_module_symbol(module->gmodule, "module_class", (gpointer *)&module->module_class) ||
		!module->module_class) {
		g_module_close(module->gmodule);
		g_slice_free(JdModule, module);
		return NULL;
	}

	return module;
}

JdModule *
jd_module_find_from_file(const gchar *module_name)
{
	JdModule *module;
	const char *filename;
	char *fullpath;
	GDir *dir;

	DEBUG("Finding Module from path: %s\n", PACKAGE_LIB_DIR "/judaemon");

	dir = g_dir_open(PACKAGE_LIB_DIR "/judaemon", 0, NULL);
	if (dir == NULL)
		return NULL;

	/* Search */
	while((filename = g_dir_read_name(dir)) != NULL) {
		if (g_str_has_suffix(filename, ".so")) {
			/* Load Module */
			fullpath = g_build_filename(PACKAGE_LIB_DIR "/judaemon", filename, NULL);
			module = jd_module_load(fullpath);
			if (!module) {
				g_free(fullpath);
				continue;
			}

			/* Check module name */
			if (strcmp(module->module_class->name, module_name) == 0) {
				DEBUG("Found Module \"%s\"\n", filename);
				g_dir_close(dir);
				g_free(fullpath);
				return module;
			}

			g_free(fullpath);
		}
	}

	g_dir_close(dir);

	DEBUG("No found Module!\n");

	return NULL;
}

JdModule *
jd_module_find(JuDaemon *judaemon, const gchar *module_name)
{
	JdModule *module;
	gint i;

	DEBUG("Finding Module from list\n");

	/* Find from modules list */
	for (i = 0; judaemon->modules->len; ++i) {
		module = (JdModule *)g_ptr_array_index(judaemon->modules, i);
		if (strcmp(module->module_class->name, module_name) == 0)
			return module;
	}

	/* Search external modules */
	module = jd_module_find_from_file(module_name);	
	if (!module)
		return NULL;

	/* Add to modules list */
	g_ptr_array_add(judaemon->modules, module);

	return module;
}

void
jd_module_constructor(JdComponent *comp, JsonNode *node)
{
	comp->module->module_class->constructor(comp, node);
}
