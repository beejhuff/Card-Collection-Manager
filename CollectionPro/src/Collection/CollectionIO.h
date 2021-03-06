#pragma once
#include "../Config.h"
#include "../Support/StringHelper.h"
#include "../Support/TypeDefs.h"
#include "CopyItem.h"
#include "CollectionObject.h"
#include "Collection.h"
#include "CollectionFactory.h"
#include "CollectionSource.h"

#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>

class CollectionFactory;
class Collection;
class CollectionObject;

class CollectionIO
{
public:
   CollectionIO( Collection* aptCollection );
   ~CollectionIO();

   bool InitializeCollection( const std::string& aszFileName );

   bool LoadCollection( const std::string& aszFileName, CollectionFactory* aoFactory );
   
   void SaveCollection();

   void ExportCollection( Query aQuery );

   std::map<unsigned long, std::vector<std::string>> GetHistoryTransactions( unsigned int aiStart, unsigned int aiEnd );

private:
   struct ItemLoadToken
   {
   public:
      CollectionObject* Item;
      std::vector<std::shared_ptr<CopyItem>> ConfirmedCopyItems;
      std::vector<std::shared_ptr<CopyItem>> ReplacedByNewlyLoadedItems;
      std::vector<std::shared_ptr<CopyItem>> OutDatedRemovedItems;
      std::vector<std::shared_ptr<CopyItem>> ItemsLikelyAddedWhileUnloaded;
      std::map<std::shared_ptr<CopyItem>, std::shared_ptr<CopyItem>> NewerExistingItems;
   };

   // Used to store data that must persist between steps.
   struct LoadToken
   {
   public:
      std::string CollectionName;
      std::string CollectionFileName;
      std::string CollectionFilePath;
      std::string CollectionAddress;
      std::string CollectionChildCount;
      std::string CollectionSessionTime;
      std::vector<std::string> MetaTagLines;
      std::vector<std::string> OverheadPropertyLines;
      std::vector<std::string> OverheadProcessLines;
      std::vector<std::string> CardLines;
      std::map<std::string,std::vector<std::shared_ptr<CopyItem>>> CardItems;
      std::vector<ItemLoadToken> ItemLoadTokens;
   };
private:
   Collection* m_ptCollection;
   CollectionFactory* m_ptFactory;
   std::unique_ptr<LoadToken> m_ptLoadToken;

   // Capitalized b/c main algo.
   bool PrepareCollectionInitialization( const std::string& aszFileName );

   bool PrepareCollectionItems();

   bool PopulateCollectionFields();

   bool ConsolodateItems();

   bool FinalizeLoad();

   bool loadOverheadFile();
   bool loadOverheadProcessLine( const std::string& aszLine );
   bool loadOverheadPropertyLine( const std::string& aszLine );
   bool storeOverheadProperyLineValue( const std::string& aszLine );
   bool loadPotentialItem( const string& aszName,
                           const vector<Tag>& alstAttrs,
                           const vector<Tag>& alstMetaTags );
   bool loadMetaTagFile();
   bool bindMetaTagLine( const std::string& aszLine );
   bool isAOlderThanB( const std::shared_ptr<CopyItem>& aA, const std::shared_ptr<CopyItem>& aB );
   bool isAOlderThanB( const std::string& aA, const std::string& aB );
   bool transferCopyFirstToSecond( const std::shared_ptr<CopyItem>& aA, const std::shared_ptr<CopyItem>& aB );

   void saveHistory();
   void saveMeta();
   void saveOverhead();
   void saveRequiredPeekValues( ofstream& aFile );
   void saveCollection();
   void exportCollection(Query aQuery);

public:
   static bool CollectionFileExists( std::string aszFileName );
   static std::string StripFileName( std::string aszFilePath );
   static std::string StripFileName( std::string aszFilePath, string& rszDirectory );
   static std::string GetCollectionFile( std::string aszCollectionName );
   static std::string GetMetaFile( std::string aszCollectionName );
   static std::string GetHistoryFile( std::string aszCollectionName );
   static std::string GetOverheadFile( std::string aszCollectionName );

   static bool GetFileLines( std::string aszFileName,
                             std::vector<std::string>& rlstFileLines );
   static bool GetNameAndCollectionLines( std::vector<std::string> alstAllLines,
                                          std::string& rszName,
                                          std::vector<std::string>& rlstCardLines );
};

