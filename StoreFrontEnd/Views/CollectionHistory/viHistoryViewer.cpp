#include "viHistoryViewer.h"
#include "vicBlogItem.h"

BEGIN_EVENT_TABLE( viHistoryViewer, wxFrame )
EVT_SIZE( viHistoryViewer::onResize )
END_EVENT_TABLE()

viHistoryViewer::viHistoryViewer( wxWindow* aptParent,
                                  wxWindowID aiID,
                                  std::shared_ptr<CollectionInterface> aptInterface)
   : wxFrame( aptParent, aiID, "History", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP ), m_ptInterface( aptInterface )
{
   wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL );
   this->SetSizer( sizer );

   wxScrolledWindow* scrollWindow = new wxScrolledWindow( this );
   wxBoxSizer* scrollsizer = new wxBoxSizer( wxVERTICAL );
   scrollWindow->SetSizer( scrollsizer );
   scrollWindow->SetScrollRate( 10, 20 );

   auto mapHist = aptInterface->GetHistoryGroups();

   // Want to start with most recent.
   auto riter_hist = mapHist.rbegin();
   for( ; riter_hist != mapHist.rend(); ++riter_hist )
   {
      wxString szTitle = " (";
      szTitle += std::to_string( riter_hist->second.size() ) + ") Change";
      if( riter_hist->second.size() > 1 )
      {
         szTitle += "s";
      }

      vicBlogItem* blogItem = new vicBlogItem( scrollWindow,
                                               szTitle,
                                               StringInterface::ToTimeString( riter_hist->first, "%D %T" ),
                                               riter_hist->second );
      scrollsizer->Add( blogItem, wxSizerFlags( 0 ).Expand() );
   }

   sizer->Add( scrollWindow, wxSizerFlags( 1 ).Expand() );

}


viHistoryViewer::~viHistoryViewer()
{
}

void
viHistoryViewer::onResize( wxSizeEvent &ev )
{
   ev.Skip();
}