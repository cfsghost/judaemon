#ifndef JD_CONF_H
#define JD_CONF_H

#include <json-glib/json-glib.h>

struct _JdConf {
	JsonParser *parser;
	JsonNode *root;
};
typedef struct _JdConf JdConf;

#endif
