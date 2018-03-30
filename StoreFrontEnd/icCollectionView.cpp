#include "icCollectionView.h"
#include "MainWindow.h"


icCollectionView::icCollectionView(MainFrame* aParent, const wxString& aszColName)
	: IMenuEventHandler(aParent)
{
   m_ptCollectionInterface = std::make_shared<CollectionInterface>(aszColName.ToStdString());
}


icCollectionView::~icCollectionView()
{

}

// Editors
void 
icCollectionView::ShowCollectionEditor() 
{

}

void
icCollectionView::CloseCollectionEditor()
{

}

void
icCollectionView::ShowStats() 
{

}

void 
icCollectionView::ShowHistory()
{

}

// Loading
void 
icCollectionView::BulkInsert()
{

}

void 
icCollectionView::RemoveItem()
{

}

void 
icCollectionView::InsertItem()
{

}

// CoicCollectionView::ntrol
void 
icCollectionView::RefreshView()
{

}