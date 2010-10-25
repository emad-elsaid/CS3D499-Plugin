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


#include "stdafx.h"
#include "IFCEngineInteract.h"
#include "ObjectRightView.h"

STRUCT_INSTANCES	* first_instance, * last_instance;

int		model = 0, noVertices, noIndices, * pIndices;
float	* pVertices;
char	* ifcSchemaName = NULL;

void	InitIFCEngineInteract()
{
	first_instance = NULL;
	last_instance = NULL;
}

STRUCT_INSTANCES	* AddObject(STRUCT_INSTANCES * parent, int id, char * name)
{
	if	(last_instance) {
		last_instance->next = new(STRUCT_INSTANCES);
		last_instance = last_instance->next;
	} else {
		first_instance = new(STRUCT_INSTANCES);
		last_instance = first_instance;
	}

	if	( (name)  &&
		  (name[0]) ) {
		last_instance->name = name;
	} else {
		last_instance->name = _T("<no text available>");
	}
	last_instance->parent = parent;
	last_instance->next = NULL;
	last_instance->select = ITEM_CHECKED;
	last_instance->id = id;

	return	last_instance;
}

void	RetrieveObjects(char * ObjectSPFFName, char * ObjectGroupName)
{
	STRUCT_INSTANCES	* parent;
	int					i, object, * objects, noObjects;
	char				* string;

	objects = sdaiGetEntityExtentBN(model, ObjectSPFFName);
	noObjects = sdaiGetMemberCount(objects);
	if	(noObjects) {
		parent = AddObject(NULL, 0, ObjectGroupName);

		for (i = 0; i < noObjects; ++i) {
			engiGetAggrElement(objects, i, sdaiINSTANCE, &object);

			//
			//	The loaded schema in openSPFFFile is needed to interpret 'GlobalId' in this function
			//
			sdaiGetAttrBN(object, "GlobalId", sdaiSTRING, &string);

			AddObject(parent, object, string);
		}
	}
}

int		RetrieveObjectGroups(char * fileName)
{
    if  (model) {
		sdaiCloseModel(model);
        model = 0;
    }

	model = sdaiOpenModelBN(0, fileName, ifcSchemaName);

	if	(model) {
		RetrieveObjects(_T("IFCANNOTATION"), _T("Annotations"));
		RetrieveObjects(_T("IFCBEAM"), _T("Beams"));
		RetrieveObjects(_T("IFCBUILDING"), _T("Buildings"));
        RetrieveObjects(_T("IFCBUILDINGELEMENTPART"), _T("Building Element Parts"));		
        RetrieveObjects(_T("IFCBUILDINGELEMENTPROXY"), _T("Building Element Proxies"));		
		RetrieveObjects(_T("IFCBUILDINGSTOREY"), _T("Building Stories"));
		RetrieveObjects(_T("IFCCHAMFEREDGEFEATURE"), _T("Chamfer Edge Features"));
		RetrieveObjects(_T("IFCCOLUMN"), _T("Columns"));		
		RetrieveObjects(_T("IFCCOVERING"), _T("Coverings"));		
		RetrieveObjects(_T("IFCCURTAINWALL"), _T("Curtain Walls"));
		RetrieveObjects(_T("IFCDISCRETEACCESSORY"), _T("Discrete Accessories"));		
		RetrieveObjects(_T("IFCDISTRIBUTIONCHAMBERELEMENT"), _T("Distribution Chamber Elements"));
		RetrieveObjects(_T("IFCDISTRIBUTIONCONTROLELEMENT"), _T("Distribution Control Elements"));
		RetrieveObjects(_T("IFCDISTRIBUTIONELEMENT"), _T("Distribution Elements"));
		RetrieveObjects(_T("IFCDISTRIBUTIONFLOWELEMENT"), _T("Distribution Flow Elements"));
		RetrieveObjects(_T("IFCDISTRIBUTIONPORT"), _T("Distribution Ports"));
		RetrieveObjects(_T("IFCDOOR"), _T("Doors"));		
		RetrieveObjects(_T("IFCELECTRICALELEMENT"), _T("Electrical Elements"));		
		RetrieveObjects(_T("IFCELECTRICDISTRIBUTIONPOINT"), _T("Electric Distribution Points"));		
		RetrieveObjects(_T("IFCELEMENTASSEMBLY"), _T("Element Assemblies"));		
		RetrieveObjects(_T("IFCENERGYCONVERSIONDEVICE"), _T("Energy Conversion Devices"));	
		RetrieveObjects(_T("IFCEQUIPMENTELEMENT"), _T("Equipment Elements"));	
		RetrieveObjects(_T("IFCFASTENER"), _T("Fasteners"));		
		RetrieveObjects(_T("IFCFLOWCONTROLLER"), _T("Flow Controllers"));		
		RetrieveObjects(_T("IFCFLOWFITTING"), _T("Flow Fittings"));		
		RetrieveObjects(_T("IFCFLOWMOVINGDEVICE"), _T("Flow Moving Devices"));		
		RetrieveObjects(_T("IFCFLOWSEGMENT"), _T("Flow Segments"));		
		RetrieveObjects(_T("IFCFLOWSTORAGEDEVICE"), _T("Flow Storage Devices"));		
		RetrieveObjects(_T("IFCFLOWTERMINAL"), _T("Flow Terminals"));		
		RetrieveObjects(_T("IFCFLOWTREATMENTDEVICE"), _T("Flow Treatment Devices"));		
		RetrieveObjects(_T("IFCFOOTING"), _T("Footings"));		
		RetrieveObjects(_T("IFCFURNISHINGELEMENT"), _T("Furnishing Elements"));		
		RetrieveObjects(_T("IFCGRID"), _T("Grids"));
		RetrieveObjects(_T("IFCMECHANICALFASTENER"), _T("Mechanical Fasteners"));		
		RetrieveObjects(_T("IFCMEMBER"), _T("Members"));		
		RetrieveObjects(_T("IFCOPENINGELEMENT"), _T("Opening Elements"));		
		RetrieveObjects(_T("IFCPILE"), _T("Piles"));		
		RetrieveObjects(_T("IFCPLATE"), _T("Plates"));		
		RetrieveObjects(_T("IFCPROJECTIONELEMENT"), _T("Projection Elements"));		
		RetrieveObjects(_T("IFCPROXY"), _T("Proxies"));
		RetrieveObjects(_T("IFCRAILING"), _T("Railings"));		
		RetrieveObjects(_T("IFCRAMP"), _T("Ramps"));		
		RetrieveObjects(_T("IFCRAMPFLIGHT"), _T("Ramp Flights"));		
		RetrieveObjects(_T("IFCREINFORCINGBAR"), _T("Reinforcing Bars"));		
		RetrieveObjects(_T("IFCREINFORCINGMESH"), _T("Reinforcing Meshes"));		
		RetrieveObjects(_T("IFCROOF"), _T("Roofs"));		
		RetrieveObjects(_T("IFCROUNDEDEDGEFEATURE"), _T("Rounded Edge Features"));		
		RetrieveObjects(_T("IFCSITE"), _T("Sites"));		
		RetrieveObjects(_T("IFCSLAB"), _T("Slabs"));		
		RetrieveObjects(_T("IFCSPACE"), _T("Spaces"));		
		RetrieveObjects(_T("IFCSTAIR"), _T("Stairs"));		
		RetrieveObjects(_T("IFCSTAIRFLIGHT"), _T("Stair Flights"));		
		RetrieveObjects(_T("IFCSTRUCTURALCURVECONNECTION"), _T("Structural Curve Connections"));		
		RetrieveObjects(_T("IFCSTRUCTURALCURVEMEMBER"), _T("Structural Curve Members"));		
		RetrieveObjects(_T("IFCSTRUCTURALCURVEMEMBERVARYING"), _T("Structural Curve Member Varyings"));		
		RetrieveObjects(_T("IFCSTRUCTURALLINEARACTION"), _T("Structural Linear Actions"));		
		RetrieveObjects(_T("IFCSTRUCTURALLINEARACTIONVARYING"), _T("Structural Linear Action Varyings"));		
		RetrieveObjects(_T("IFCSTRUCTURALPLANARACTION"), _T("Structural Planar Actions"));		
		RetrieveObjects(_T("IFCSTRUCTURALPLANARACTIONVARYING"), _T("Structural Planar Action Varyings"));		
		RetrieveObjects(_T("IFCSTRUCTURALPOINTACTION"), _T("Structural Point Actions"));		
		RetrieveObjects(_T("IFCSTRUCTURALPOINTCONNECTION"), _T("Structural Point Connections"));		
		RetrieveObjects(_T("IFCSTRUCTURALPOINTREACTION"), _T("Structural Point Reactions"));		
		RetrieveObjects(_T("IFCSTRUCTURALSURFACECONNECTION"), _T("Structural Surface Connections"));		
		RetrieveObjects(_T("IFCSTRUCTURALSURFACEMEMBER"), _T("Structural Surface Members"));		
		RetrieveObjects(_T("IFCSTRUCTURALSURFACEMEMBERVARYING"), _T("Structural Surface Member Varyings"));		
		RetrieveObjects(_T("IFCTENDON"), _T("Tendons"));		
		RetrieveObjects(_T("IFCTENDONANCHOR"), _T("Tendon Anchors"));		
		RetrieveObjects(_T("IFCTRANSPORTELEMENT"), _T("Transport Elements"));		
		RetrieveObjects(_T("IFCVIRTUALELEMENT"), _T("Virtual Elements"));		
		RetrieveObjects(_T("IFCWALL"), _T("Walls"));		
		RetrieveObjects(_T("IFCWALLSTANDARDCASE"), _T("Walls Standard Cases"));		
		RetrieveObjects(_T("IFCWINDOW"), _T("Windows"));
	} else {
		return	-1;
	}

	return	0;
}

void	EnrichObjectGroups()
{
	STRUCT_INSTANCES	* instance;

	if	(first_instance) {
		//
		//	We need to build up the 3D structure in the IFC Engine DLL to retrieve geometrical data
		//
		initializeModelling(model, &noVertices, &noIndices, 1);
		pVertices = (float *) malloc(noVertices * sizeof(CUSTOMVERTEX));
		pIndices = (int *) malloc(noIndices * sizeof(int));
		finalizeModelling(model, &pVertices[0], &pIndices[0], D3DFVF_CUSTOMVERTEX);

		instance = first_instance;

		while  (instance) {
			if	(instance->parent) {
				getInstanceInModelling(model, instance->id, 1, &instance->startVertex, &instance->startIndex, &instance->primitiveCount);
			}

			instance = instance->next;
		}
	}
}