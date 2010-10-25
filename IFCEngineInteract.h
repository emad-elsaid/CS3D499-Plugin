////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  Date:    31 July 2010
//  Project: IFC Engine Series (example using DLL)
//
//  This code may be used and edited freely,
//  also for commercial projects in open and closed source software
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:	peter.bonsma@tno.nl
//
//  more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//									pim.vandenhelm@tno.nl
//								    peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "IFCEngine.h"


#define		ITEM_UNCHECKED			0
#define		ITEM_PARTLY_CHECKED		1
#define		ITEM_CHECKED			2

typedef struct STRUCT_INSTANCES {
	int					id;
	char				* name;
	STRUCT_INSTANCES	* parent;
	STRUCT_INSTANCES	* next;
	HTREEITEM			hTreeItem;
	int					select;

	int					startVertex;
	int					startIndex;
	int					primitiveCount;
}	struct_type;


void	InitIFCEngineInteract();
STRUCT_INSTANCES	* AddObject(STRUCT_INSTANCES * parent, int id, char * name);
void	RetrieveObjects(char * ObjectSPFFName, char * ObjectGroupName);
int		RetrieveObjectGroups(char * fileName);
void	EnrichObjectGroups();
