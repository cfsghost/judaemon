#include <stdlib.h>
#include <glib.h>
#include <gmodule.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <sys/stat.h>
#include <clutter/clutter.h>
#include <clutter/x11/clutter-x11.h>
#include <judaemon/conf.h>
#include <judaemon/component.h>
#include "judaemon.h"
#include "component.h"
#include "conf.h"

void
jd_load_main_config(JuDaemon *judaemon, gchar *path)
{
	JdComponent *comp;
	JdConf *conf;
	JsonNode *group_node;
	GList *members = NULL;
	GList *listnode = NULL;
	gchar *comp_name;

	DEBUG("Load Settings\n");
	conf = jd_conf_new();

	/* Load config file */
	if (jd_conf_load_from_file(conf, path)) {
		DEBUG("Read general settings\n");
		group_node = jd_conf_get_member(conf, NULL, "general", NULL);
		if (!group_node) {
			DEBUG("No general setting was defined in config\n");
			/* TODO: Build up default general settings here */
		} else {
			/* TODO: Load general settings here */
		}

		DEBUG("Read all settings of components\n");


		group_node = jd_conf_get_member(conf, NULL, "components", NULL);
		if (!group_node) {
			DEBUG("No component was defined in config\n");
//			shelf = jd_build_default_shelf(judaemon);
//			g_ptr_array_add(judaemon->shelves, shelf);
		} else {
			/* Read all components */
			DEBUG("Found component was defined\n");

			/* Initializing all components */
			members = jd_conf_get_members(conf, group_node, NULL);
			for (listnode = members; listnode; listnode = g_list_next(listnode)) {
				/* Get component name */
				comp_name = (gchar *)listnode->data;
				
				/* create component */
				comp = jd_component_new(judaemon, comp_name);

				/* Initializing component */
				jd_component_init(judaemon, comp, jd_conf_get_member(conf, group_node, comp_name, NULL));
				g_ptr_array_add(judaemon->components, comp);
			}
		}
	} else {
		/* TODO: Build up default general settings here */
	}

	/* TODO: Release Conf object */
}

void
jd_config_file_init(JuDaemon *judaemon)
{
	gchar *confdir;
	gchar *confpath;

	/* Main config path */
	confdir = g_build_filename(g_get_user_config_dir(), "judaemon", NULL);
	DEBUG("Check config path: %s\n", confdir);
	if (!g_file_test(confdir, G_FILE_TEST_EXISTS))
		g_mkdir_with_parents(confdir, S_IRUSR | S_IWUSR | S_IXUSR);

	/* Main config */
	confpath = g_build_filename(confdir, "settings.conf", NULL);
	DEBUG("Check config file: %s\n", confpath);
	if (!g_file_test(confpath, G_FILE_TEST_EXISTS)) {
		//jd_load_default_settings(judaemon);
		return;
	}

	jd_load_main_config(judaemon, confpath);
}

gboolean
jd_xevent_filter(XEvent *ev, ClutterEvent *cev, JuDaemon *judaemon)
{
	/* XRandr Extension Event */
	switch(ev->type - judaemon->xrandr_event_base) {
	case RRScreenChangeNotify:
		DEBUG("Got RRScreenChangeNotify\n");
		break;
	}

	return CLUTTER_X11_FILTER_CONTINUE;
}

void init_x11(JuDaemon *judaemon)
{
	Display *disp;
	int screen;

	/* Get current display and screen */
	disp = clutter_x11_get_default_display();
	screen = clutter_x11_get_default_screen();

	/* XRandr extension */
	XRRQueryVersion(disp, &judaemon->rr_major_version, &judaemon->rr_minor_version);
	if (judaemon->rr_major_version < 1 || (judaemon->rr_major_version == 1 && judaemon->rr_minor_version < 2)) {
		g_print("RANDR extension is too old (must be at least 1.2)\n");
		return EXIT_FAILURE;
	}

	XRRSelectInput(disp, DefaultRootWindow(disp), RRScreenChangeNotifyMask);
	XRRQueryExtension(disp, &judaemon->xrandr_event_base, &judaemon->xrandr_error_base);
}

int
main(int argc, char *argv[])
{
	JuDaemon *judaemon;

	DEBUG("Starting JuDaemon\n");
	clutter_x11_set_use_argb_visual(TRUE);
	clutter_init(&argc, &argv);

	/* Initializing Application */
	DEBUG("Initializing JuDaemon\n");
	judaemon = (JuDaemon *)g_slice_new(JuDaemon);
	judaemon->modules = g_ptr_array_new();
	judaemon->components = g_ptr_array_new();

	init_x11(judaemon);

	jd_config_file_init(judaemon);

	/* X Events */
	clutter_x11_add_filter(jd_xevent_filter, judaemon);

	/* Loop */
	clutter_main();

	return EXIT_SUCCESS;
}
