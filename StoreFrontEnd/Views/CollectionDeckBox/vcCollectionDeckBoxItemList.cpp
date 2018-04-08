#include "vcCollectionDeckBoxItemList.h"
#include "../StoreFrontEnd/StoreFrontEnd.h"
#include "../StoreFrontEnd/CardInterface.h"
#include "../StoreFrontEnd/CollectionInterface.h"
#include "../StoreFrontEnd/Group.h"

wxBEGIN_EVENT_TABLE(vcCollectionDeckBoxItemList, wxPanel)
EVT_LIST_ITEM_SELECTED(List, vcCollectionDeckBoxItemList::onItemSelection)
EVT_LIST_ITEM_DESELECTED(List, vcCollectionDeckBoxItemList::onItemDeselection)
wxEND_EVENT_TABLE()


vcCollectionDeckBoxItemList::vcCollectionDeckBoxItemList( wxWindow* aptParent,
                                                          std::shared_ptr<CollectionInterface> aptInt )
   : wxPanel(aptParent), m_ptColInt(aptInt)
{
   m_iSelection = -1;
   m_wxListControl = new wxListCtrl( this, List,
                                     wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
   m_wxListControl->InsertColumn(0, "#");
   m_wxListControl->InsertColumn(1, "Name");
   m_wxListControl->InsertColumn(2, "Mana Cost");
   m_wxListControl->InsertColumn(3, "Card Type");
   m_wxListControl->InsertColumn(4, "Set");

   wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
   this->SetSizer(boxSizer);

   boxSizer->Add(m_wxListControl, 1, wxEXPAND);

   RefreshList();
}


vcCollectionDeckBoxItemList::~vcCollectionDeckBoxItemList()
{

}

void 
vcCollectionDeckBoxItemList::RefreshList()
{
   m_ptColInt->Refresh();

   m_wxListControl->Freeze();
   m_wxListControl->DeleteAllItems();
   displayGrouping(performGrouping(m_ptColInt->GetItemInterfaces()));
   m_wxListControl->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
   m_wxListControl->SetColumnWidth(1, wxLIST_AUTOSIZE);
   m_wxListControl->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
   m_wxListControl->SetColumnWidth(3, wxLIST_AUTOSIZE);
   m_wxListControl->SetColumnWidth(4, wxLIST_AUTOSIZE);
   m_wxListControl->Thaw();
   
   this->Layout();
}

CardInterface 
vcCollectionDeckBoxItemList::GetItemByListIndex(int Ind)
{
   if( ( Ind < m_vecDataItemsDisplayOrder.size() ) && 
       ( m_vecDataItemsDisplayOrder[Ind] != NULL ) )
   {
      return *m_vecDataItemsDisplayOrder[Ind];
   }
   else
   {
      return CardInterface();
   }
}

CardInterface 
vcCollectionDeckBoxItemList::GetFirst()
{
   if( m_vecDataItemsDisplayOrder.size() > 0 )
   {
      size_t i = 0;
      while( i < m_vecDataItemsDisplayOrder.size()  &&
             m_vecDataItemsDisplayOrder[i] == NULL )
      {
         i++;
      }
      if( m_vecDataItemsDisplayOrder[i] != NULL )
      {
         return *m_vecDataItemsDisplayOrder[i];
      }
   }
   return CardInterface();
}

int 
vcCollectionDeckBoxItemList::GetFirstInt()
{
   if( m_vecDataItemsDisplayOrder.size() > 0 )
   {
      size_t i = 0;
      while( i < m_vecDataItemsDisplayOrder.size() &&
         m_vecDataItemsDisplayOrder[i] == NULL )
      {
         i++;
      }
      if( m_vecDataItemsDisplayOrder[i] != NULL )
      {
         return i;
      }
   }
   return -1;
}

bool 
vcCollectionDeckBoxItemList::IsEmpty()
{
   return m_ptColInt->GetItemInterfaces().size() == 0;
}

void
vcCollectionDeckBoxItemList::onItemSelection(wxListEvent& awxEvt)
{
   m_iSelection = awxEvt.GetIndex();
   if( m_iSelection != -1 )
   {
      if( m_vecDataItemsDisplayOrder[m_iSelection] != NULL )
      {
         awxEvt.SetString( m_vecDataItemsDisplayOrder[m_iSelection]->GetHash() );
         awxEvt.Skip();
      }
   }
}

void
vcCollectionDeckBoxItemList::onItemDeselection(wxListEvent& awxEvt)
{
   m_iSelection = -1;
   awxEvt.StopPropagation();
}

// Returns a list of pointers to the input vector. SO DONT DELETE THE VECTOR BEFORE
// USING THE RETURN.
std::map<wxString, std::vector<CardInterface*>>
vcCollectionDeckBoxItemList::performGrouping(std::vector<CardInterface>& avecItems)
{
   Group overrideGrp;
   // TODO: Use the stringIface to get the collection.group. write this func.
   overrideGrp.GroupOn("group", true);

   Group defaultGrp;
   defaultGrp.GroupOn("type", false)
             .BroadenGroup("Creature")
             .BroadenGroup("Instant")
             .BroadenGroup("Sorcery")
             .BroadenGroup("Enchantment")
             .BroadenGroup("Artifact")
             .BroadenGroup("Planeswalker")
             .BroadenGroup("Land")
             .OverrideGrouping(overrideGrp);


   std::map<wxString, std::vector<CardInterface*>> mapGroups;
   // So you assign each item in your collection to a CardInterface,
   // then the do something like below to extract the group that they should belong.
   for( auto& data : avecItems )
   {
      // TODO: Need way to get meta tags from server so we can sort on them.
      mapGroups[defaultGrp.GetGroup(data)].push_back(&data);
   }

   return mapGroups;
}

void 
vcCollectionDeckBoxItemList::displayGrouping(const std::map<wxString,
                                             std::vector<CardInterface*>>& amapGrouping)
{
   unsigned int iCount = 0;
   for( auto& group : amapGrouping )
   {
      wxString buf = group.first;
      int i = m_wxListControl->GetItemCount();
      long tmp = m_wxListControl->InsertItem(i, "", 0);
      m_wxListControl->SetItem(tmp, 1, buf);
      wxListItem item;
      item.m_itemId = i;
      item.SetBackgroundColour(*wxLIGHT_GREY);
      m_wxListControl->SetItem(item);
      m_vecDataItemsDisplayOrder.push_back(0);
      for( auto& item : group.second )
      {
         addListItem(*item);
         m_vecDataItemsDisplayOrder.push_back(item);
      }
   }
}

void 
vcCollectionDeckBoxItemList::addListItem(CardInterface& aData)
{
   wxString buf = std::to_string(aData.GetNumber());
   int i = m_wxListControl->GetItemCount();
   long tmp = m_wxListControl->InsertItem(i, buf, 0);
   m_wxListControl->SetItemData(tmp, i);

   buf = aData.GetName();
   m_wxListControl->SetItem(tmp, 1, buf);

   buf = aData.GetManaCost();
   m_wxListControl->SetItem(tmp, 2, buf);

   buf = aData.GetCardType();
   m_wxListControl->SetItem(tmp, 3, buf);

   buf = aData.GetSet();
   m_wxListControl->SetItem(tmp, 4, buf);
}