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
#include "ObjectLeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	STRUCT_INSTANCES	* first_instance;

/////////////////////////////////////////////////////////////////////////////
// CObjectLeftView

IMPLEMENT_DYNCREATE(CObjectLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CObjectLeftView, CTreeView)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectLeftView construction/destruction

CObjectLeftView::CObjectLeftView()
{
	// TODO: add construction code here
}

CObjectLeftView::~CObjectLeftView()
{
}

BOOL CObjectLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CObjectLeftView drawing

void CObjectLeftView::OnDraw(CDC* pDC)
{
	CObjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CObjectLeftView diagnostics

#ifdef _DEBUG
void CObjectLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CObjectLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CObjectDoc* CObjectLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CObjectDoc)));
	return (CObjectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjectLeftView message handlers

void CObjectLeftView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	CImageList* pImageList = new CImageList();
	pImageList->Create(16, 16, ILC_COLOR4, 3, 3);

	CBitmap bitmap;

	bitmap.LoadBitmap(IDB_BITMAP_UNCHECKED);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	bitmap.LoadBitmap(IDB_BITMAP_PARTLY_CHECKED);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	bitmap.LoadBitmap(IDB_BITMAP_CHECKED);
	pImageList->Add(&bitmap, (COLORREF)0x000000);
	bitmap.DeleteObject();

	CTreeCtrl *tst = &GetTreeCtrl();

	::SetWindowLong(*tst, GWL_STYLE, TVS_LINESATROOT|TVS_HASLINES|TVS_HASBUTTONS|::GetWindowLong(*tst, GWL_STYLE));

	GetTreeCtrl().SetImageList(pImageList, TVSIL_NORMAL);
	GetTreeCtrl().DeleteAllItems();

	TV_INSERTSTRUCT		tvstruct;
	STRUCT_INSTANCES	* instance;

	if	(first_instance) {
		tvstruct.hParent = NULL;
		tvstruct.hInsertAfter = TVI_LAST;

		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN | TVIF_STATE;
		tvstruct.item.stateMask = TVIS_STATEIMAGEMASK;
		tvstruct.item.state = INDEXTOSTATEIMAGEMASK(1);

		instance = first_instance;
		while  (instance) {
			if	(instance->parent) {
				tvstruct.item.cChildren = 0;
				tvstruct.hParent = instance->parent->hTreeItem;
			} else {
				tvstruct.item.cChildren = 1;
				tvstruct.hParent = NULL;
			}

			tvstruct.item.lParam = (long) instance;
			tvstruct.item.pszText = instance->name;
			tvstruct.item.iImage = instance->select;
			tvstruct.item.iSelectedImage = instance->select;

			instance->hTreeItem = GetTreeCtrl().InsertItem(&tvstruct);

			instance = instance->next;
		}

		//
		//	Update right window
		//

		this->GetWindow(GW_HWNDNEXT)->SendMessage(ID_INIT_RIGHT_VIEW, 0, 0);
	}
}

void CObjectLeftView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	STRUCT_INSTANCES		* instance, * child_instance, * parent_instance;
	int						noSelected, noUnselected;

	DWORD		pos = GetMessagePos();
	CPoint		pt(LOWORD(pos), HIWORD(pos));
	GetTreeCtrl().ScreenToClient(&pt);

	// Get indexes of the first and last visible items in listview
	// control.
	HTREEITEM	hItem = GetTreeCtrl().GetFirstVisibleItem();

	while  (hItem) {
		CRect r;
		GetTreeCtrl().GetItemRect(hItem, &r, true);
		r.right = r.left-4;
		r.left = r.left-18;

		if (r.PtInRect(pt))
		{
			instance = (STRUCT_INSTANCES *) GetTreeCtrl().GetItemData(hItem);

			if	(instance->parent) {
				//
				//	We found a child tree object
				//
				if	(instance->select == ITEM_UNCHECKED) {
					instance->select = ITEM_CHECKED;
				} else {
					instance->select = ITEM_UNCHECKED;
				}
				GetTreeCtrl().SetItemImage(instance->hTreeItem, instance->select, instance->select);

				//
				//	Update parent
				//
				parent_instance = instance->parent;
				child_instance = parent_instance->next;
				noSelected = 0;
				noUnselected = 0;
				while  ( (child_instance)  &&
						 (child_instance->parent) ) {
					if	(child_instance->select == ITEM_UNCHECKED) {
						noUnselected++;
					} else {
						noSelected++;
					}

					child_instance = child_instance->next;
				}

				if	(noSelected) {
					if	(noUnselected) {
						parent_instance->select = ITEM_PARTLY_CHECKED;
					} else {
						parent_instance->select = ITEM_CHECKED;
					}
				} else {
					parent_instance->select = ITEM_UNCHECKED;
				}
				GetTreeCtrl().SetItemImage(parent_instance->hTreeItem, parent_instance->select, parent_instance->select);
			} else {
				//
				//	We found a root tree object
				//
				if	(instance->select == ITEM_UNCHECKED) {
					instance->select = ITEM_CHECKED;
				} else {
					instance->select = ITEM_UNCHECKED;
				}
				GetTreeCtrl().SetItemImage(instance->hTreeItem, instance->select, instance->select);

				//
				//	Update children
				//
				child_instance = instance->next;
				while  ( (child_instance)  &&
						 (child_instance->parent) ) {
					child_instance->select = instance->select;
					GetTreeCtrl().SetItemImage(child_instance->hTreeItem, child_instance->select, child_instance->select);

					child_instance = child_instance->next;
				}
			}
		}

		hItem = GetTreeCtrl().GetNextVisibleItem(hItem);
	}

	//
	//	Update right window
	//
	this->GetWindow(GW_HWNDNEXT)->SendMessage(ID_UPDATE_RIGHT_VIEW, 0, 0);

	*pResult = 0;
}
