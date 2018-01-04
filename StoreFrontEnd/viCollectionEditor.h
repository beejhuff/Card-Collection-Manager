#pragma once
#include "wx/wxprec.h"
#include <wx/timer.h>
#include <vector>
#include <string>
#include "StoreFront.h"
#include "vicListSelector.h"

class vicListSelector;
class vicCollectionEditorList;

class viCollectionEditor : public wxPanel
{
public:
   enum
   {
      Changes_Accept = 0x132,
      Changes_Decline = 0x99
   };

   enum Selectors : int
   {
      Add = 0x0,
      Remove = 0x1
   };

   viCollectionEditor(wxWindow* aptParent, wxWindowID aiWID, wxString aszColID);
   ~viCollectionEditor();

private:
   wxDECLARE_EVENT_TABLE();
   wxTimer m_timer;
   wxString m_szCollectionID;
   vicListSelector* m_vAddSelector;
   vicListSelector* m_vRemSelector;
   vicCollectionEditorList* m_vListView;
   bool m_bHandleTextEvent;
   bool m_bIsWaitingForDrop;
   unsigned long m_ulTimeLastKeyStroke;

   void buildSelectors();
   void buildListView();
   void buildButtons();

   void onComboBoxTextChanged(wxCommandEvent& awxEvt);
   void onComboBoxAccept(wxCommandEvent& awxEvt);
   void onDropDownDelay(wxTimerEvent& event);

   unsigned long getTime();

   std::vector<vicListSelector::Option>
      parseCollectionItemsList(const std::vector<std::string>& avecItems);

   const char* ADD_BUTTON_TEXT = "Add";
   const char* REMOVE_BUTTON_TEXT = "Remove/Replace";
};

