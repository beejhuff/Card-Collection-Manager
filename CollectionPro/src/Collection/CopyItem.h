#pragma once
#include "MetaTag.h"
#include "TraitItem.h"
#include "AddressBook.h"
#include "../Addressing/Addresser.h"

#include <string>
#include <set>
#include <vector>
#include <map>
#include <memory>

class CollectionObject;

// Each Copy Item has a Unique ID and a Class Hash ID and its last modified session date.
// UID is a 3 digit hex number, this is also called the Chain ID.
// Hash ID is an MD5 has of various traits.
// Last modified session date is an integer.
class CopyItem
{
public:
   enum HashType : int
   {
      Ids = 0x2,
      Meta = 0x4,
      Default = 0x7
   };

private:
   // Use static constructor to build this class.
   CopyItem( const Identifier& aAddrParentIdentifier,
             CollectionObject* aptClass );
   CopyItem( const Identifier& aAddrParentIdentifier,
             const std::vector<Tag>& alstMetaTags,
             CollectionObject* aptClass);

public:
   CopyItem( const CopyItem& aCopy );
   ~CopyItem();

   std::string GetHash(HashType aiHashType = Default);
   std::string GetSession() const;
   Address GetAddress() const;
   std::string GetUID() const;
   CollectionObject* GetObject() const;

   bool IsVirtual() const;

   void SetParent( const Identifier& aAddrTestAddress );
   bool IsParent( const Location& aAddrTestAddress ) const;
   std::string GetParent() const;

   void AddResident( const Identifier& aAddrAddress );
   int RemoveResident( const Identifier& aAddrAddress,
                       unsigned int aiRemoveType = 0 );

   bool IsResidentIn( const Location& aAddrAddress ) const;
   bool IsReferencedBy( const Location& aAddrAddress ) const;
   std::vector<Address> GetResidentIn() const;

   void SetMetaTag( const std::string& aszKey,
                    const std::string& aszVal,
                    MetaTagType atagType,
                    bool bTimeChange = true );
   std::string GetMetaTag(const std::string& aszKey, MetaTagType atagType) const;
   std::vector<Tag> GetMetaTags(MetaTagType atagType) const;

   // This expects that the input is valid. Does not verify that
   // the value is an allowed value.
   bool SetIdentifyingAttribute( const std::string& aszKey,
                                 const std::string& aszValue,
                                 bool bTimeChange = true );

   std::string GetIdentifyingAttribute(std::string aszKey);
   std::vector<Tag> GetIdentifyingAttributes() const;

   void SetAddressBook( std::shared_ptr<AddressBook> aptBook );

private:
   bool m_bNeedHash;

   // I didn't want to do this. But here I am.
   CollectionObject* m_ptCollectionObject;

   std::shared_ptr<AddressBook> m_ptAddressBook;

   void itemChanged();
   void setUID(std::string aszNewID);
   void setMetaTag( const std::string& aszKey,
                    const std::string& aszVal,
                    MetaTagType atagType,
                    bool bTimeChange = true );

   std::map<std::string, MetaTag> m_lstMetaTags;
   std::map<std::string, std::string> m_lstIdentifyingTags;
public:
   static std::shared_ptr<CopyItem> CreateCopyItem( CollectionObject* aoConstructor,
                                                    const Identifier& aAddrParentIdentifier,
                                                    const std::vector<Tag>& alstIDAttrs,
                                                    const std::vector<Tag>& alstMetaTags );

   static MetaTagType DetermineMetaTagType(std::string aszTagKey);

   static std::string GetUIDKey();
   static std::string GetSessionKey();
   static std::string GetHashKey();
   static std::string GetAddressKey();
   static std::string MakeIgnoredTag(const std::string aszTag);
   static std::string MakeTrackingTag(const std::string aszTag);
};

