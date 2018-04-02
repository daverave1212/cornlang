#ifndef MAP_INIT_H_INCLUDED
#define MAP_INIT_H_INCLUDED

#include "map_words_definitions.h"
#include "object_finder.h"


void initMap(Map<int> &m){

	m.create();
	m.setNullElementTo(NOT_FOUND);

	m.push("import", IMPORT);

}

#endif // MAP_INIT_H_INCLUDED
