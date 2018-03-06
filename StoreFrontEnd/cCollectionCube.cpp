#include "cCollectionCube.h"
#include "vCollectionCube.h"
#include "StoreFrontEnd.h"
#include "MainWindow.h"

cCollectionCube::cCollectionCube( MainFrame* aParent, const wxString& aszColName )
   : IMenuEventHandler( aParent ), m_ColID( aszColName )
{
   auto ptSF = StoreFrontEnd::Instance();
   m_wxCube = new vCollectionCube( aParent, 9, m_ColID );

   registerSendMenuEvents();
}

cCollectionCube::~cCollectionCube()
{
   m_wxCube->Destroy();
}

wxPanel*
cCollectionCube::GetView()
{
   return m_wxCube;
}

void
cCollectionCube::BindEventHandler()
{
   prepareMenuItem( "Edit", Menu_DeckEditor );
   prepareMenuItem( "Save", Menu_Save );
   prepareMenuItem( "View As Deck", Menu_View_As_Deck );
   registerMenu( "Collection" );
}

void
cCollectionCube::handleEvent( unsigned int aiEvent )
{
   if( aiEvent == Menu_DeckEditor )
   {
      m_wxCube->ShowCollectionEditor();
   }
   else if( aiEvent == Menu_Save )
   {
      auto ptSF = StoreFrontEnd::Instance();
      ptSF->SaveCollection( m_ColID.ToStdString() );
   }
   else if( aiEvent == cCollectionCube::Menu_View_As_Deck )
   {
      wxCommandEvent updateEvt( wxEVT_MENU );
      updateEvt.SetId( MainFrame::Menu_View_As );
      updateEvt.SetString( m_ColID );
      updateEvt.SetInt( MainFrame::Menu_View_As_Deck );
      ::wxPostEvent( m_wxCube, updateEvt );
   }
}