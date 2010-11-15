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
#include "ObjectViewer.h"
#include "IFCEngineInteract.h"

#include "ObjectDoc.h"

extern	STRUCT_INSTANCES	* first_instance;
extern	char	* ifcSchemaName;

/////////////////////////////////////////////////////////////////////////////
// CObjectDoc

IMPLEMENT_DYNCREATE(CObjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CObjectDoc, CDocument)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectDoc construction/destruction

CObjectDoc::CObjectDoc()
{
	// TODO: add one-time construction code here
}

CObjectDoc::~CObjectDoc()
{
}

BOOL CObjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CObjectDoc serialization

void CObjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		InitIFCEngineInteract();
		//
		//	Load and parse IFC file and build up internal structure
		//
		switch	(RetrieveObjectGroups(((CString) ar.m_strFileName).GetBuffer(0))) {
			case  0:
				//
				//	Retrieve geometrical data
				//
				EnrichObjectGroups();
				break;
			default:
				char	error[512] = "Model in IFC Engine, could not be created, probably due to missing IFC Schema in executable directory.\nSearched schema location: ";
				memcpy(&error[strlen(error)], ifcSchemaName, strlen(ifcSchemaName));
				MessageBox(GetActiveWindow(), error, "ERROR loading IFC file", 0);
				break;
		}
	}
}