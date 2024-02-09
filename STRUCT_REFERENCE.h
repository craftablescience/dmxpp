#pragma once

#include <cstdint>

namespace dmxpp {

class DMX_v5 {
	char* header = "<!-- dmx encoding binary 5 format %s %i -->\n";

	int		nStrings; // number of strings in StringDict
	char*	StringDict[]; // null-terminated, tightly packed

	int	nElements; // number of elements in the entire data model

	DmeHeader	ElementIndex; // the root element
	DmeBody		ElementBodies[]; // in the same order as the nested index
};

class DmeHeader
{
	int		Type; // string dictionary index
	int		Name; // string dictionary index
	char	GUID[16]; // little-endian

	DmeHeader SubElems[]; // skip elements which already have an index entry
};

class DmeBody
{
	int	nAttributes;
	DmeAttribute Attributes[];
};

class DmAttribute
{
	int		Name; // string dictionary index
	char	AttributeType; // see below
	void*	Value; // see below
};

} // namespace dmxpp
