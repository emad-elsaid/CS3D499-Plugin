////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  $Date: 2010-07-30 12:00:24 +0200 (Fri, 30 Jul 2010) $
//  $Revision: 3330 $
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


#if !defined(AFX_IFCENGINE_H__E61DCDC8_CF8E_48DD_A8A3_C62AB6E95095__INCLUDED_)
#define AFX_IFCENGINE_H__E61DCDC8_CF8E_48DD_A8A3_C62AB6E95095__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef WIN64
	#define int __int64
#endif

#ifdef __LP64__
	#include <stdint.h>
	#define int int64_t 
#endif

#ifdef _WINDOWS
	#ifdef _USRDLL
		#define DECL __declspec(dllexport) 
	#else
		#define DECL __declspec(dllimport) 
	#endif
	#define STDC __stdcall
#else
	#define DECL /*nothing*/
	#define STDC /*nothing*/
#endif


#ifdef __cplusplus
    extern "C" {
#endif

#ifndef __cplusplus
    typedef char bool; /* define the boolean type not available in c */
#endif

#define		sdaiADB					1
#define		sdaiAGGR				sdaiADB + 1
#define		sdaiBINARY				sdaiAGGR + 1
#define		sdaiBOOLEAN				sdaiBINARY + 1
#define		sdaiENUM				sdaiBOOLEAN + 1
#define		sdaiINSTANCE			sdaiENUM + 1
#define		sdaiINTEGER				sdaiINSTANCE + 1
#define		sdaiLOGICAL				sdaiINTEGER + 1
#define		sdaiREAL				sdaiLOGICAL + 1
#define		sdaiSTRING				sdaiREAL + 1
#define		sdaiUNICODE				sdaiSTRING + 1
#define		sdaiEXPRESSSTRING		sdaiUNICODE + 1

//
//	Note on sdaiSTRING and sdaiUNICODE
//
//	sdaiUNICODE
//		this will convert all internal strings from/too unicode, the internal representation and what is written to the IFC file is mapped
//			"\" will be converted into "\\" to enable basic parses to still interpret file paths
//			"'" will be converted to \X1\hh\X0\ or \X2\00hh\X0\ to prevent basic interpreters to read files with strings containing these characters
//
//	sdaiSTRING
//		this will leave all information as is in the IFC file, the rules are that char's ( int ) 32 to 126 (inclusive) will be kept
//		all other strings will be converted to \X1\hh\X0\ or \X2\00hh\X0\ 


#define     sdaiARRAY               1
#define     sdaiLIST                2
#define     sdaiSET                 3
#define     sdaiBAG                 4

typedef	int				* SdaiAggr;
typedef	void			* SdaiAttr;
typedef	int				SdaiInstance;
typedef	int				SdaiInteger;
typedef	int				SdaiModel;
typedef	int				SdaiPrimitiveType;
typedef	int				* SdaiSet;
typedef	char			* SdaiString;

int DECL STDC setStringUnicode(
										bool	unicode
									);

int DECL * STDC xxxxGetEntityAndSubTypesExtent(	//		SdaiSet
										int		model,					//			SdaiModel
										int		entity					//			SdaiEntity
									);

int DECL * STDC xxxxGetEntityAndSubTypesExtentBN(	//		SdaiAggr
										int		model,					//			SdaiModel
										char	* entityName			//			SdaiString
									);

int DECL STDC xxxxIsKindOf(                       //      SdaiBoolean
                                                 int instance, int entity); 



int DECL * STDC xxxxGetInstancesUsing(			//		SdaiAggr
										int		instance				//			SdaiInstance
									);

int DECL STDC xxxxDeleteFromAggregation(	        //		SdaiAggr
										int		instance,				//			SdaiInstance
										int		* aggregate,			//			SdaiAggr
										int		elementIndex			//			SdaiInteger
									);

void DECL * STDC xxxxGetAttrDefinitionByValue(	//		SdaiAttr
										int		instance,				//			SdaiInstance
										void	* value		            //			void (aggregation or instance)
									);

void DECL STDC xxxxGetAttrNameByIndex(          
                                        int		instance,				//			SdaiInstance
										int 	index,			        //			SdaiAttr
                                        char**  name                    //          name
                                    );

int DECL STDC xxxxOpenModelByStream(
										int		repository,
										void	* callback,
										char	* schemaName
									);


int DECL STDC sdaiOpenModelBN(
										int		repository,
										char	* fileName,
										char	* schemaName
									);


int DECL STDC sdaiCreateModelBN(
										int		repository,
										char	* fileName,
										char	* schemaName
									);

int DECL STDC GetSPFFHeaderItem(
										int		model,
										int		itemIndex,
										int		itemSubIndex,
										int		valueType,
                                        char    ** value
                                    );

int DECL STDC SetSPFFHeaderItem(
										int		model,
										int		itemIndex,
										int		itemSubIndex,
										int		valueType,
                                        char    * value
                                    );

void DECL STDC SetSPFFHeader(
										int		model,
                                        char    * description,
                                        char    * implementationLevel,
                                        char    * name,
                                        char    * timeStamp,
                                        char    * author,
                                        char    * organization,
                                        char    * preprocessorVersion,
                                        char    * originatingSystem,
                                        char    * authorization,
                                        char    * fileSchema
                                    );

void DECL STDC sdaiSaveModelBN(
										int		model,
										char	* fileName
									);

void DECL STDC sdaiSaveModelAsXmlBN(
										int		model,
										char	* fileName
									);

void DECL STDC sdaiCloseModel(
										int		model
									);

void DECL STDC setPreProcessing(
										int		model,
										bool	on
									);

void DECL STDC setPostProcessing(
										int		model,
										bool	on
									);

void DECL * STDC engiGetAggrElement(				//		void*
										int		* aggregate,			//			SdaiAggr
										int		elementIndex,			//			SdaiInteger
										int		valueType,				//			SdaiPrimitiveType
										void	* pValue				//			void*
									);

int DECL STDC engiGetInstanceMetaInfo(			//		void*
										int		* instance,				//			SdaiAppInstance
										int		* localId,				//			...
										char	** className,			//			..
										char	** classNameUC			//			...*
									);

void DECL STDC engiGetEntityName(
										int		entity,					//			...
										char	** className			//			..
									);

int DECL STDC engiGetEntityParent(
										int		entity					//			...
									);

void DECL STDC engiGetEntityProperty(
										int		entity,					//			...
										int		index,					//			...
										char	** propertyName,		//			...
										int		* optional,				//			...
										int		* type,					//			...
										int		* array,				//			...
										int		* set,					//			...
										int		* list,					//			...
										int		* bag,					//			...
										int		* min,					//			...
										int		* max,					//			...
										int		* referenceEntity,		//			...
										int		* inverse				//			...
									);

int DECL STDC engiGetInstanceLocalId(				//
										int		instance				//			SdaiAppInstance
									);

char DECL * STDC engiGetInstanceClassInfo(		//
										int		instance				//			SdaiAppInstance
									);

char DECL * STDC engiGetInstanceClassInfoUC(		//
										int		instance				//			SdaiAppInstance
									);
	

void DECL STDC sdaiAppend(						//		void
										int		list,					//			SdaiList
										int		valueType,				//			SdaiPrimitiveType
										void	* value					//			void*
									);

void DECL STDC sdaiBeginning(						//		void
										int		iterator				//			SdaiIterator
									);

void DECL * STDC sdaiCreateADB(					//		void*
										int		valueType,				//			SdaiPrimitive
										void	* value					//			void*
									);

int DECL * STDC sdaiCreateAggr(					//		SdaiAggr
										int		instance,				//			SdaiAppInstance
										void	* attribute				//			SdaiAttr
									);

int DECL * STDC sdaiCreateAggrBN(					//		SdaiAggr
										int		instance,				//			SdaiAppInstance
										char	* attributeName			//			SdaiString
									);

int DECL STDC sdaiCreateInstance(					//		SdaiAppInstance
										int		model,					//			SdaiModel
										int		entity					//			SdaiEntity
									);

int DECL STDC sdaiCreateInstanceEI(					//		SdaiAppInstance
										int		model,					//			SdaiModel
										int		entity,					//			SdaiEntity
										int		express_id				//			
									);

int DECL STDC sdaiCreateInstanceBN(				//		SdaiAppInstance
										int		model,					//			SdaiModel
										char	* entityName			//			SdaiString
									);

int DECL STDC sdaiCreateInstanceBNEI(				//		SdaiAppInstance
										int		model,					//			SdaiModel
										char	* entityName,			//			SdaiString
										int		express_id				//			
									);

void DECL * STDC sdaiCreateIterator(				//		SdaiIterator
										int		* aggregate				//			SdaiAggr
									);

void DECL STDC sdaiDeleteInstance(				//		void
										int		instance				//			SdaiAppInstance
									);

void DECL STDC sdaiDeleteIterator(				//		void
										int		iterator				//			SdaiIterator
									);

void DECL STDC sdaiEnd(							//		void
										int		iterator				//			SdaiIterator
									);

int DECL STDC sdaiErrorQuery(						//		SdaiErrorCode
									);

int DECL  STDC sdaiGetADBType(				//		void
										void	* ADB	 				//			sdaiADB
									);

char DECL * STDC sdaiGetADBTypePath(				//		void
										void	* ADB,	 				//			sdaiADB
										int		typeNameNumber			//			int
									);

void DECL STDC sdaiGetADBValue(				//		void
										void	* ADB,	 				//			sdaiADB
										int		valueType,				//			SdaiPrimitiveType
										void	* value					//			void*
									);

void DECL * STDC sdaiGetAggrByIterator(			//		void*
										int		iterator,				//			SdaiIterator
										int		valueType,				//			SdaiPrimitiveType
										void	* value					//			void*
									);

void DECL * STDC sdaiGetAttr(						//		void*
										int		instance,				//			SdaiInstance
										void	* attribute,			//			SdaiAttr
										int		valueType,				//			SdaiPrimitiveType
										void	* value					//			void*
									);

void DECL * STDC	sdaiGetAttrBN(					//		void*
										int		instance,				//			SdaiInstance
										char	* attributeName,		//			SdaiString
										int		valueType,				//			SdaiPrimitiveType
										void	* value					//			void*
									);

void DECL * STDC sdaiGetAttrDefinition(			//		SdaiAttr
										int		entity,					//			SdaiEntity
										char	* attributeName			//			SdaiString
									);

int DECL STDC	sdaiGetEntity(						//		SdaiEntity
										int		model,					//			SdaiModel
										char	* entityName			//			SdaiString
									);

int DECL * STDC sdaiGetEntityExtent(				//		SdaiAggr
										int		model,					//			SdaiModel
										int		entity					//			SdaiEntity
									);

int DECL * STDC sdaiGetEntityExtentBN(			//		SdaiAggr
										int		model,					//			SdaiModel
										char	* entityName			//			SdaiString
									);

int DECL STDC sdaiGetInstanceType(				//		SdaiEntity
										int		instance				//			SdaiInstance
									);

int	DECL STDC	sdaiGetMemberCount(					//		SdaiInteger
										int		* aggregate				//			SdaiAggr
									);

int DECL STDC sdaiIsInstanceOf(					//		SdaiBoolean
										int		instance,				//			SdaiInstance
										int		entity					//			SdaiEntity
									);

int DECL STDC sdaiIsInstanceOfBN(				//		SdaiBoolean
										int		instance,				//			SdaiInstance
										char	* entityName			//			SdaiString
									);

int DECL STDC sdaiNext(							//		SdaiBoolean
										int		iterator				//			SdaiIterator
									);

void DECL STDC sdaiPrepend(						//		void
										int		list,					//			SdaiList
										int		valueType,				//			SdaiPrimitiveType
										void	* value					//			void*
									);

int DECL STDC sdaiPrevious(						//		SdaiBoolean
										int		iterator				//			SdaiIterator
									);

void DECL STDC sdaiPutADBTypePath(				//		void
										void	* ADB,					//			sdaiADB
										int		pathCount,				//			int
										char	* path					//			char*
									);

void DECL STDC sdaiPutAggrByIterator(				//		void
										int		iterator,				//			SdaiIterator
										int		valueType,				//			SdaiPrimitiveType
										void	* value					//			void*
									);

void DECL STDC sdaiPutAttr(						//		void
										int		instance,				//			SdaiInstance
										void	* attribute,			//			SdaiAttr
										int		valueType,				//			SdaiPrimitive
										void	* value					//			void*
									);

void DECL STDC sdaiPutAttrBN(						//		void
										int		instance,				//			SdaiInstance
										char	* attributeName,		//			SdaiString
										int		valueType,				//			SdaiPrimitive
										void	* value					//			void*
									);

int DECL STDC sdaiTestAttr(						//		SdaiBoolean
										int		instance,				//			SdaiInstance
										void	* attribute				//			SdaiAttr
									);

int DECL STDC sdaiTestAttrBN(					//		SdaiBoolean
										int		instance,				//			SdaiInstance
										char	* attributeName			//			SdaiString
									);


int DECL STDC initializeModelling(
										int		model,
										int		* noVertices,
										int		* noIndices,
										double	scale
									);

int DECL STDC initializeModellingInstance(
										int		model,
										int		* noVertices,
										int		* noIndices,
										double	scale,
										int		instance				//			SdaiInstance
									);

int DECL STDC initializeModellingInstanceEx(
										int		model,
										int		* noVertices,
										int		* noIndices,
										double	scale,
										int		instance,				//			SdaiInstance
										int		instanceList			//			SdaiInstance
									);

int DECL STDC finalizeModelling(
										int		model,
										float	* pVertices,
										int		* pIndices,
										int		FVF
									);

int DECL STDC getInstanceInModelling(
										int		model,
										int		instance,
										int		mode,
										int		* startVertex,
										int		* startIndex,
										int		* primitiveCount
									);

int DECL STDC getInstanceDerivedPropertiesInModelling(
										int		model,
										int		instance,
										double	* height,
										double	* width,
										double	* thickness
									);

int DECL STDC getInstanceDerivedBoundingBox(
										int		model,
										int		instance,
										double	* Ox,
										double	* Oy,
										double	* Oz,
										double	* Vx,
										double	* Vy,
										double	* Vz
									);

int DECL STDC getInstanceDerivedTransformationMatrix(
										int		model,
										int		instance,
										double	* _11,
										double	* _12,
										double	* _13,
										double	* _14,
										double	* _21,
										double	* _22,
										double	* _23,
										double	* _24,
										double	* _31,
										double	* _32,
										double	* _33,
										double	* _34,
										double	* _41,
										double	* _42,
										double	* _43,
										double	* _44
									);

void DECL STDC circleSegments(
										int		circles,
										int		smallCircles
									);

int DECL STDC getTimeStamp(
										int		model
									);

char DECL * STDC getChangedData(
										int		model,
										int		* timeStamp
									);

void DECL STDC setChangedData(
										int		model,
										int		* timeStamp,
										char	* changedData
									);

void DECL * STDC internalGetBoundingBox(
										int		model,
										int		instance
									);

void DECL * STDC internalGetCenter(
										int		model,
										int		instance
									);

void DECL STDC internalSetLink(
										int		instance,				//			SdaiInstance
										char	* attributeName,		//			SdaiString
										int		linked_id
									);

void DECL STDC internalAddAggrLink(				//		void
										int		list,					//			SdaiList
										int		linked_id
									);

char DECL * STDC sdaiGetStringAttrBN(int instance, char * attributeName);

int DECL STDC sdaiGetInstanceAttrBN(int instance, char * attributeName);

int DECL STDC sdaiGetAggregationAttrBN(int instance, char * attributeName);

int	DECL STDC internalGetP21Line(
										int		instance				//			SdaiAppInstance
									);

void DECL STDC engiGetNotReferedAggr(int model, int * pValue);

void DECL STDC engiGetAttributeAggr(int instance, int * pValue);

void DECL STDC engiGetAggrUnknownElement(		//		void
										int		* aggregate,			//			SdaiAggr
										int		elementIndex,			//			SdaiInteger
										int		* valueType,			//			SdaiPrimitiveType
										void	* pValue				//			void*
									);

int DECL STDC sdaiIsKindOf(int instance, int entity);

int DECL * STDC sdaiFindInstanceUsers(int instance, int* domain, int* resultList);

int DECL * STDC sdaiFindInstanceUsedIn(int instance, int* domain, int* resultList);

int DECL STDC sdaiplusGetAggregationType(int instance, int *aggregation);

int DECL STDC engiGetEntityNoArguments(int entity);

char DECL * STDC engiGetEntityArgumentName(int entity, int index);

int DECL STDC engiGetEntityArgumentType(int entity, int index);

#undef DECL 
#undef STDC  

#ifdef __cplusplus
}
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#ifdef __LP64__
	#undef int 
#endif

#endif // !defined(AFX_IFCENGINE_H__E61DCDC8_CF8E_48DD_A8A3_C62AB6E95095__INCLUDED_)

