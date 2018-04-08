#pragma once
#include"../ViewTemplates/IMenuEventHandler.h"
#include <map>
#include <wx\wxprec.h>

class vCollectionDeckBox;
class MainFrame;

class cCollectionDeckBox : public IMenuEventHandler
{
public:
   enum
   {
      Menu_DeckEditor = 0x4001,
      Menu_Save = 0x4501,
      Menu_View_As_Cube = 0x4503
   };

   cCollectionDeckBox( IMenuEventSource* aptParent, vCollectionDeckBox* aptView, const wxString& aszColName );
   virtual ~cCollectionDeckBox();

   wxPanel* GetView() override;

   void BindEventHandler();

protected:
   void handleEvent(unsigned int aiEvent);

private:
   vCollectionDeckBox* m_wxDeckbox;
   wxString m_ColID;
   std::map<wxString, unsigned int> m_mapTitleToEventID;
};