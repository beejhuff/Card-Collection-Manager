#include "vCollectionsOverview.h"
#include "vcCollectionsMenuList.h"
#include "../StoreFrontEnd/StoreFrontEnd.h"
#include "../CollectionPreviewer/viCollectionSelector.h"
#include <wx/listctrl.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>


wxBEGIN_EVENT_TABLE(vCollectionsOverview, wxPanel)
EVT_BUTTON(vCollectionsOverview::Load_Collection, vCollectionsOverview::OnLoadCollection)
EVT_BUTTON( viCollectionSelector::Load_Button, vCollectionsOverview::onLoadCollection )
wxEND_EVENT_TABLE()

vCollectionsOverview::vCollectionsOverview( wxWindow* aptParent,
                                            wxWindowID aiWID = wxID_ANY ) 
   : wxPanel(aptParent, aiWID)
{
   wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);
   this->SetSizer(boxSizer);

   this->GetParent()->SetMinSize(wxSize(350, 500));
   if( this->GetParent()->GetSize().GetWidth() < this->GetParent()->GetMinSize().GetWidth() ||
       this->GetParent()->GetSize().GetHeight() < this->GetParent()->GetMinSize().GetHeight() )
   {
      this->GetParent()->SetSize( wxSize( 350, 500 ) );
   }

   buildCollectionSelector();
   getLoadedCollections();
}


vCollectionsOverview::~vCollectionsOverview()
{
   delete m_vcCollectionsPanel;
}

void 
vCollectionsOverview::onLoadCollection( wxCommandEvent& awxEvt )
{
   StoreFront* ptSF = StoreFrontEnd::Server();
   auto szPath = awxEvt.GetString();

   // Load collection returns the Col ID.
   auto szColID = ptSF->LoadCollection( szPath.ToStdString() );
   auto szColName = ptSF->GetCollectionName( szColID );
   m_vcCollectionsPanel->AddCollectionOption( szColName );

   // This event is handled.
   awxEvt.StopPropagation();
}

void 
vCollectionsOverview::buildCollectionsPreview() 
{

}

void 
vCollectionsOverview::buildCollectionSelector() 
{
   m_vcCollectionsPanel = new vcCollectionsMenuList(this);
   this->GetSizer()->Add(m_vcCollectionsPanel, 1, wxEXPAND);
}

void 
vCollectionsOverview::getLoadedCollections()
{
   auto ptSF = StoreFrontEnd::Server();
   auto vecCols = ptSF->GetLoadedCollections();
   for( auto& szColID : vecCols )
   {
      auto szColName = ptSF->GetCollectionName(szColID);
      m_vcCollectionsPanel->AddCollectionOption(szColName);
   }
}


void
vCollectionsOverview::OnLoadCollection(wxCommandEvent& awxEvt)
{
/*
   wxFileDialog openFileDialog( this, _("Open Collection file"), "", "",
                                "text files (*.txt)|*.txt",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST );

   if( openFileDialog.ShowModal() == wxID_CANCEL )
      return; 

   // proceed loading the file chosen by the user;
   // this can be done with e.g. wxWidgets input streams:
   wxFileInputStream input_stream(openFileDialog.GetPath());
   if( !input_stream.IsOk() )
   {
      wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
      return;
   }

   StoreFront* ptSF = StoreFrontEnd::Server();
   auto szPath = openFileDialog.GetPath().ToStdString();

   // Load collection returns the Col ID.
   auto szColID = ptSF->LoadCollection(szPath);
   auto szColName = ptSF->GetCollectionName(szColID);
   m_vcCollectionsPanel->AddCollectionOption(szColName);

   // This event is handled.
   awxEvt.StopPropagation();
*/
   auto sel = new viCollectionSelector( this, 4 );
   wxFrame* pTargetFrame = sel;
   sel->Show();
   sel->SetMinSize( wxSize( 450, 600 ) );
   if( sel->GetSize().GetWidth() < sel->GetMinSize().GetWidth() ||
      sel->GetSize().GetHeight() < sel->GetMinSize().GetHeight() )
   {
      sel->SetSize( sel->GetMinSize() );
   }
}
