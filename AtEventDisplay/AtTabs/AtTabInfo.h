#ifndef ATTABINFO_H
#define ATTABINFO_H

#include "AtViewerManagerSubject.h"

#include <FairRootManager.h>

#include <TClonesArray.h>
#include <TObject.h> // for TObject
#include <TString.h>

#include <map>
#include <memory> // for allocator
#include <string>
#include <type_traits> // for enable_if_t, is_base_of

/**
 * @defgroup TabData Data for tabs
 *
 * Classes used to provide access to and update the data used by tabs in the visualizer. There are
 two main classes at the moment:

 * AtTabInfoFairRoot which provides access to classes through the FairRoot source file.
 * AtTabInfoHiRAEVT which provides access to classes stored in a HiRAEVT stle TTree.
 * A S800 class will also have to be added.
 *
 * These all follow a composition pattern (similar to AtPad). Each tab owns a single AtTabInfo which
 * can itself contain any number at AtTabInfo-style classes.
 */

/**
 * @brief Interface for AtTabInfo classes.
 * @ingroup TabData
 */
class AtTabInfoBase {

public:
   AtTabInfoBase() = default;
   virtual ~AtTabInfoBase() = default;

   /**
    * @brief Default name for info type.
    */
   virtual std::string GetDefaultName() = 0;
};

/**
 * @brief Contains all the data needed by an AtTab.
 * @ingroup TabData
 */
class AtTabInfo : public AtTabInfoBase {
public:
   using BasePtr = std::shared_ptr<AtTabInfoBase>;

protected:
   std::map<std::string, BasePtr> fInfoAugments;

public:
   AtTabInfo() = default;
   ~AtTabInfo() = default;

   std::string GetDefaultName() override { return "AtTabInfo"; }

   void AddAugment(BasePtr augment);
   void AddAugment(BasePtr augment, std::string name);

   void ReplaceAugment(BasePtr augment);
   void ReplaceAugment(BasePtr augment, std::string name);

   BasePtr GetAugment(std::string name);

   /// Get Augment cast to anticipated type (which must have the proper base class).
   template <typename T, typename std::enable_if_t<std::is_base_of<AtTabInfoBase, T>::value> * = nullptr>
   T *GetAugment(std::string name)
   {
      return dynamic_cast<T *>(GetAugment(name).get());
   }
};

/**
 * @brief Class for tracking the information from a branch of the FairRoot source tree.
 *
 * Templated class, for an AtRawEvent it would be instantiated like AtTabInfo<AtRawEvent>.
 * Switched to template to make adding additional info types stored on the TTree trivial to add.
 * @ingroup TabData
 */
template <typename T>
class AtTabInfoFairRoot : public AtTabInfoBase {

protected:
   DataHandling::AtBranch &fBranchName;
   TString fCurrentBranchName;
   TClonesArray *fArray{nullptr};

public:
   AtTabInfoFairRoot(DataHandling::AtBranch &branch) : AtTabInfoBase(), fBranchName(branch) {}
   ~AtTabInfoFairRoot() {}

   std::string GetDefaultName() override { return T::Class_Name(); }

   T *GetInfo() { return Get(); }
   T *Get()
   {
      if (fCurrentBranchName != fBranchName.GetBranchName()) {
         fCurrentBranchName = fBranchName.GetBranchName();
         fArray = dynamic_cast<TClonesArray *>(FairRootManager::Instance()->GetObject(fCurrentBranchName));
      }
      if (fArray != nullptr && fArray->GetEntries() > 0)
         return dynamic_cast<T *>(fArray->At(0));
      return nullptr;
   }
   const T *operator->() const { return Get(); }
   const T &operator*() const { return *Get(); }
   T *operator->() { return Get(); }
   T &operator*() { return *Get(); }

   const DataHandling::AtBranch &GetBranch() const { return fBranchName; }
};

#endif
