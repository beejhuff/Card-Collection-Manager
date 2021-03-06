#pragma once
#include "../Support/TryGet.h"
#include "../Support/TypeDefs.h"
#include "../Addressing/Addresser.h"
#include "TraitItem.h"
#include "CopyItem.h"

#include <string>
#include <memory>

using namespace std;

enum CollectionObjectType : int
{
   Local = 0x1,
   Borrowed = 0x2,
   Real = 0x3,
   Virtual = 0x4,
   All = 0xF
};

enum FindType : int
{
   UID = 0x1,
   Hash = 0x2
};

// CollectionObject
//  Contains all the common data related to the object of this type.
//  Maintains a list of all instances and their variations via copy items.
//  Acts as a manager of Copy Items.
class CollectionObject
{
public:
   // Aids in the construction of CopyItems
   class PseudoIdentifier
   {
   public:
      PseudoIdentifier();
      PseudoIdentifier(unsigned int aiCount, string aszName,
         string aszDetails, string aszMeta);
      ~PseudoIdentifier();

      unsigned int Count;
      string Name;
      string DetailString;
      string MetaString;
      vector<Tag> Identifiers;
      vector<Tag> MetaTags;
   };

public:
   CollectionObject( const string& aszItemName,
                     const vector<Tag>& alstCommon,
                     const vector<TraitItem>& alstRestrictions );
   ~CollectionObject();

   shared_ptr<CopyItem> CreateCopy( const Identifier& aAddrColID,
                                    const vector<Tag>& alstAttrs = vector<Tag>(),
                                    const vector<Tag>& alstMetaTags = vector<Tag>() );

   // Adds an item to the list of copies.
   shared_ptr<CopyItem> AddCopy( const Location& aAddrColID,
                                 const vector<Tag>& alstAttrTags,
                                 const vector<Tag>& alstMetaTags );
   shared_ptr<CopyItem> AddCopy( const shared_ptr<CopyItem>& aCopy );

   bool RemoveCopy( const Location& aAddrColID,
                    const string aszUniqueID );

   string GenerateHash( const Identifier& aAddrIdentifier,
                        const vector<Tag>& alstAttrs,
                        const vector<Tag>& alstMetaTags );

   // Deletes an item from the list of copies.
   void DeleteCopy(const string& aszUniqueHash);

   TryGetCopy<shared_ptr<CopyItem>> FindCopy( const string& aszUniqueID,
                                              FindType aiType = UID ) const;
   TryGetCopy<shared_ptr<CopyItem>> FindCopy( const string& aszUniqueID,
                                              FindType aiType,
                                              const vector<shared_ptr<CopyItem>>& avecCopies ) const;
   vector<shared_ptr<CopyItem>> FindCopies( const Identifier& aCollection,
                                            CollectionObjectType aSearchType ) const;
   vector<shared_ptr<CopyItem>> FindCopies( const Location& aCollection,
                                            CollectionObjectType aSearchType ) const;
   string GetName() const;
   string GetProtoType() const;
   string GetCommonTrait(const string& aszTrait) const;

private:
   string m_szName;
   map<string, string> m_lstCommonTraits;
   map<string, TraitItem> m_lstIdentifyingTraits;

   vector<shared_ptr<CopyItem>> m_lstCopies;

   void ledgerCopy( shared_ptr<CopyItem> aptCopy );

   // Copy Item Interface
   //
public:
   map<string, TraitItem> GetIdentifyingTraits();
   bool MatchIdentifyingTrait( const string& aszValue,
                               string& rszKey );

   bool SetIdentifyingTraits( shared_ptr<CopyItem> aptCopy,
                              const vector<Tag>& avecTraits,
                              const vector<Tag>& avecMeta,
                              bool bSession = true  ) const;

   // Attempts to set an identifying trait on a copy item.
   // Returns true if the value is valid.
   bool SetIdentifyingTrait( shared_ptr<CopyItem> aptCopy,
                             const string& aszTraitKey,
                             const string& aszTraitValue,
                             bool bSession = true ) const;

   bool SetIdentifyingTrait( shared_ptr<CopyItem> aptCopy,
                             const string& aszTraitKey,
                             const string& aszTraitValue,
                             const vector<string> avecUpComingTraits,
                             bool bSession = true ) const;

   void SetIdentifyingTraitDefaults( shared_ptr<CopyItem> aptCopy ) const;

   void DeleteCopy( shared_ptr<CopyItem> aptCopy );
   string CopyToString( shared_ptr<CopyItem> aptItem,
                        const MetaTagType& aAccessType = MetaTagType::Public,
                        const Identifier& aAddrCompareID = Location() ) const;


private:
   void setCopyPairAttrs( shared_ptr<CopyItem> aptItem, const string& aszKey, int iVal ) const;
   void setCopyPairAttrs( shared_ptr<CopyItem> aptItem, const string& aszKey, int iVal,
                          vector<string> avecSkipAttrs ) const;

public:
   static bool ParseCardLine(const string& aszLine, PseudoIdentifier& rPIdentifier);

   static string ToCardLine( const Identifier& aAddrParentID,
                             const string& aszName,
                             const vector<Tag>& alstAttrs = vector<Tag>(),
                             const vector<Tag>& alstMetaTags = vector<Tag>(),
                             const Identifier& aAddrCompareID = Location(),
                             const unsigned int aiCount = 0 );
};                                                                                                                                                                                                                                                                                                                                