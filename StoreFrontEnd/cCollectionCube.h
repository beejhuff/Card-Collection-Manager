#pragma once
#include"wx\wxprec.h"
#include"IMenuEventHandler.h"
#include<map>

class vCollectionCube;
class MainFrame;

class cCollectionCube : public IMenuEventHandler
{
public:
   enum
   {
      Menu_DeckEditor = 0x4001,
      Menu_Save = 0x4501,
      Menu_Stats = 0x5321,
      Menu_View_As_Deck = 0x4502
   };

   cCollectionCube( MainFrame* aParent, const wxString& aszColName );
   virtual ~cCollectionCube();

   wxPanel* GetView() override;

   void BindEventHandler();

protected:
   void handleEvent( unsigned int aiEvent );

private:
   vCollectionCube* m_wxCube;
   wxString m_ColID;
   std::map<wxString, unsigned int> m_mapTitleToEventID;
};