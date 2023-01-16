#ifndef ATTABPAD_H
#define ATTABPAD_H

#include "AtTabBase.h"

#include <Rtypes.h>  // for Int_t, Bool_t, THashConsistencyHolder, Color_t
#include <TString.h> // for TString

#include <unordered_map>
#include <memory>         // for shared_ptr
#include <string>         // for string
#include <utility>        // for pair

class TBuffer;
class TClass;
class TMemberInspector;
class AtEvent;
class AtEventManagerNew;
class AtRawEvent;
class AtMap;
class AtPad;
class TCanvas;
class TEveRGBAPalette;
class TH1D;


class AtTabPad : public AtTabBase {
public:
   enum class PadDrawType{ kADC, kRawADC, kArrAug };

protected:
   AtRawEvent *fRawEvent{nullptr};
   AtEvent *fEvent{nullptr};

   AtPad *fPad{nullptr};

   AtEventManagerNew *fEventManager{nullptr};

   std::shared_ptr<AtMap> fDetmap{nullptr};

   //TString fMap;

   TCanvas *fCvsPad{nullptr};

   Int_t fRows{1};
   Int_t fCols{1};

   std::unordered_map<Int_t, std::pair<PadDrawType, TH1D *>> fDrawMap;
   std::unordered_map<Int_t, TString> fAugNames;

   TString fTabName{"AtPad"};

   TString fEventBranch{"AtEventH"};
   TString fRawEventBranch{"AtRawEvent"};

   std::string fInfoEventName{"AtEventH"};
   std::string fInfoRawEventName{"AtRawEvent"};

   TEveRGBAPalette *fRGBAPalette{nullptr};

public:
   AtTabPad() : AtTabBase(){}
   void InitTab() override;
   void UpdateTab() override;
   void Reset() override;
   void MakeTab() override;
   void SetDrawADC(Int_t pos);
   void SetDrawRawADC(Int_t pos);
   void SetDrawArrayAug(Int_t pos, TString augName);
   void SetMap(std::shared_ptr<AtMap> map) { fDetmap = map; }
   void SetColumns(Int_t cols) { fCols = cols; }
   void SetRows(Int_t rows) {fRows = rows;}
   void SetTabName(TString tabName) { fTabName = tabName; }
   void DrawTree() override { };
   void DrawEvent() override { };
   void DrawPad(Int_t padNum) override;

   void SetEventBranch(TString name) { fEventBranch = name; }
   void SetRawEventBranch(TString name) { fRawEventBranch = name; }

private:
   void SetDraw(Int_t pos, PadDrawType type);
   void DrawPosition(Int_t pos);
   void UpdateCvsPad();

   // Functions for drawing hits

   ClassDefOverride(AtTabPad, 1)
};

#endif
