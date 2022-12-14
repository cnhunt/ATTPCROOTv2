#ifndef AtEVENTMANAGERNEW_H
#define AtEVENTMANAGERNEW_H

#include <FairRunAna.h>

#include <Rtypes.h>
#include <TEveEventManager.h>
#include <TEveManager.h>

#include <vector>

class FairRootManager;
class FairTask;
class TBuffer;
class TCanvas;
class TH2F;
class TClass;
class TGNumberEntry;
class TGTextButton;
class TMemberInspector;
class TGListTreeItem;
class AtEvent;
class TClonesArray;
class TList;

class AtEventManagerNew : public TEveEventManager {
private:
   FairRootManager *fRootManager;
   FairRunAna *fRunAna;
   TClonesArray *cArray;
   AtEvent *cevent;

   Int_t fEntry;
   TGListTreeItem *fEvent;
   TGNumberEntry *fCurrentEvent;
   TGNumberEntry *f3DThresDisplay;
   TCanvas *fCvsPadPlane;
   TCanvas *fPadWave;

   Bool_t kToggleData;

   Int_t fEntries;
   Int_t fTabTaskNum;

   TList *fTabList;

   static AtEventManagerNew *fInstance;

public:
   static AtEventManagerNew *Instance();
   AtEventManagerNew();
   virtual ~AtEventManagerNew();

   virtual void GotoEvent(Int_t event); ///< *MENU*
   virtual void NextEvent();            ///< *MENU*
   virtual void PrevEvent();            ///< *MENU*
   virtual void make_gui();
   virtual void SelectEvent();

   static void SelectPad();
   static void DrawUpdates(Int_t padNum);

   void AddTask(FairTask *task) { fRunAna->AddTask(task); }
   void AddTabTask(FairTask *task);
   virtual void Init();

   virtual Int_t GetCurrentEvent() { return fEntry; }

   TList *GetTabList() { return fTabList; }

   void RunEvent();

   AtEventManagerNew(const AtEventManagerNew &);
   AtEventManagerNew &operator=(const AtEventManagerNew &);

   ClassDef(AtEventManagerNew, 1);
};

#endif
