#pragma once
#include <wx/wxprec.h>

class vcCollectionsMenuList;

class vCollectionsOverview : public wxPanel
{
public:
   enum
   {
      Load_Collection = 0x0,
      Add_Collection = 0x1,
      View_Collection = 0x2
   };

   vCollectionsOverview(wxWindow* aptParent, wxWindowID aiWID);
   ~vCollectionsOverview();

   void OnLoadCollection(wxCommandEvent& awxEvt);


private:
   wxDECLARE_EVENT_TABLE();

   vcCollectionsMenuList* m_vcCollectionsPanel;

   void onLoadCollection( wxCommandEvent& awxEvt );
   void buildCollectionsPreview();
   void buildCollectionSelector();
   void getLoadedCollections();
};
