#ifndef JD_MODULE_H
#define JD_MODULE_H

#include <clutter/x11/clutter-x11.h>

JdModule *jd_module_load(const gchar *filename);
JdModule *jd_module_find_from_file(const gchar *module_name);
JdModule *jd_module_find(JuDaemon *judaemon, const gchar *module_name);
void      jd_module_constructor(JdComponent *comp, JsonNode *node);
void      jd_module_xevent_handler(XEvent *ev, ClutterEvent *cev, JdComponent *comp);

#endif
