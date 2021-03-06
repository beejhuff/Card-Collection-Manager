#pragma once
#include <map>
#include <wx\wxprec.h>
#include <wx\string.h>
#include <wx/event.h>
#include <wx/menu.h>

class IMenuEventSource;

// Requires      registerSendMenuEvents to be put in the constructor
// so that the event receiver knows to register event handlers
class IMenuEventHandler
{
public:
   IMenuEventHandler( IMenuEventSource* aParent );
   virtual ~IMenuEventHandler();

   void MenuEvent(wxCommandEvent& awxEvt);

   virtual void BindEventHandler() = 0;

   void ReleaseEventHandler();

protected:
   virtual void handleEvent(unsigned int aiEvent) = 0;

   void registerSendMenuEvents();
   
   void prepareMenuItem(const wxString& aszTitle, const unsigned int aiID);

   void registerMenu(const wxString& aszMenuName);

   IMenuEventSource* m_MFParent;
private:
   std::map<wxString, unsigned int> m_mapTitleToEventID;
};