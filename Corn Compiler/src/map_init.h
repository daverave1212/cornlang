#ifndef MAP_INIT_H_INCLUDED
#define MAP_INIT_H_INCLUDED

#include "map_words_definitions.h"
#include "object_finder.h"


void initMap(Map<int> &m){

	m.create();
	m.setNullElementTo(NOT_FOUND);

	m.push("import", IMPORT);
	m.push("class", CLASS);
	m.push("int", PRIMITIVE);
	m.push("bool", PRIMITIVE);
	m.push("char", PRIMITIVE);
	m.push("float", PRIMITIVE);
	m.push("string", PRIMITIVE);
	m.push("if", IF);
	m.push("public", PUBLIC);
	m.push("private", PRIVATE);
	m.push("end", BRACKET);
	m.push("static", STATIC);

}

#endif // MAP_INIT_H_INCLUDED
