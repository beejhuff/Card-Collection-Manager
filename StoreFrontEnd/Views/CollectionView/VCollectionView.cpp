#include "VCollectionView.h"
#include "../Views/CardEditor/viCardEditor.h"

wxBEGIN_EVENT_TABLE( VCollectionView, wxPanel )
//EVT_BUTTON( viCardEditor::Changes_Submit, vCollectionCube::onCardChanged )
//EVT_BUTTON( viCardEditor::Image_Changed, vCollectionCube::onNewItemSelectView )
//EVT_GRID_CELL_LEFT_CLICK( vCollectionCube::onNewItemSelected )
//EVT_BUTTON( viCollectionEditor::Changes_Accept, vCollectionCube::onEditorAccept )
//EVT_BUTTON( viCollectionEditor::Changes_Decline, vCollectionCube::onEditorDecline )
wxEND_EVENT_TABLE()

VCollectionView::VCollectionView( wxFrame* aParent, wxWindowID aiWID )
   : wxPanel(aParent, aiWID)
{
   wxFlexGridSizer* boxSizer = new wxFlexGridSizer( 1, 3, 0, 0 );

   boxSizer->AddGrowableCol( 0 );
   boxSizer->AddGrowableRow( 0 );

   this->SetSizer( boxSizer );

   this->GetParent()->SetMinSize( wxSize( 550, 500 ) );
   this->GetParent()->Layout();
}

VCollectionView::~VCollectionView()
{
   // Don't need to destroy this because wxwidgets will.
   //m_ptRenderer->Destroy();
}

void 
VCollectionView::SetController( CCollectionView* aptController )
{
   m_ptController = aptController;
}

// Takes ownership
void 
VCollectionView::SetRenderer( GroupRenderer* aptRenderer )
{
   m_ptRenderer = aptRenderer;

   // TODO: this is ugly;
   auto panel = dynamic_cast<wxPanel*>(aptRenderer);
   if( panel != nullptr )
   {
      GetSizer()->Add( panel, wxSizerFlags( 1 ).Expand() );
   }
}

void 
VCollectionView::Draw( std::vector<CardInterface*> avecItemData )
{
   if( m_ptRenderer != nullptr )
   {
      m_ptRenderer->Draw( avecItemData );
   }
}