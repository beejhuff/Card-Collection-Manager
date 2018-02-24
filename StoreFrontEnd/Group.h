#pragma once
#include "wx/wxprec.h"
#include <map>
#include <memory>

class GroupItemData;

class Group
{
public:
   class SortingOperator
   {
   public:
      virtual bool operator()( const wxString& agrpLeft, const wxString& agrpRight ) const;
   };

   class Sorting
   {
   public:
      Sorting();
      Sorting( SortingOperator* aptSorting );
      virtual bool operator()( const wxString& agrpLeft, const wxString& agrpRight ) const;
   private:
      std::shared_ptr<SortingOperator> m_ptSorter;
   };
   Group(bool abIsEmpty = false);
   Group& GroupOn( const wxString& aszKey, bool abIsMetaKey = true );

   // Applied last. Any group matching aszGroup exactly will appear as aszAlias.
   Group& AliasGroup( const wxString& aszGroup, const wxString& aszAlias );

   // Any group containing this value will appear AS this value.
   Group& BroadenGroup( const wxString& aszValue );
   Group& OverrideGrouping( const Group& aGrouping );
   Group& AddSubGroup( const wxString& aszMajorGroup, const Group& aGrouping );
   Group& SetSortingFunctor( SortingOperator* aptFunctor );

   wxString GetGroup( const GroupItemData& aData ) const;
   Group GetSubGroup( const wxString& aszGroup ) const;
   std::shared_ptr<Sorting> GetSortingFunctor() const;
   bool IsEmpty() const;

private:
   wxString Key;
   bool MetaKey;
   bool BIsEmpty;
   std::vector<wxString> BroadenedValues;
   std::map<wxString, wxString> Aliases;
   std::map<wxString, Group> SubGroups;
   std::vector<Group> Overrides;
   std::shared_ptr<Sorting> SortingFunctor;
};