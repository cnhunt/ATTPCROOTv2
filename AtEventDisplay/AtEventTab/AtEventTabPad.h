#ifndef ATEVENTTABPAD_H
#define ATEVENTTABPAD_H

#include "AtEventTab.h"

#include <Rtypes.h>  // for Int_t, Bool_t, THashConsistencyHolder, Color_t
#include <TString.h> // for TString

#include <vector>
#include <unordered_map>

class AtEvent;
class AtEventManagerNew;
class AtRawEvent;
class AtMap;
class AtPad;
class TCanvas;
class TEveRGBAPalette;
class TH1D;
class TPaletteAxis;

enum class PadDrawType{ kADC, kRawADC, kArrAug };

class AtEventTabPad : public AtEventTab {
protected:
   AtRawEvent *fRawEvent;
   AtEvent *fEvent;

   AtPad *fPad;

   AtEventManagerNew *fEventManager;

   std::shared_ptr<AtMap> fDetmap;

   TString fMap;

   TCanvas *fCvsPad;

   Int_t fRows;
   Int_t fCols;

   std::unordered_map<Int_t, std::pair<PadDrawType, TH1D *>> fDrawMap;
   std::unordered_map<Int_t, TString> fAugNames;

   TString fTabName;

   TEveRGBAPalette *fRGBAPalette;

public:
   AtEventTabPad();
   void Init() override;
   void Reset() override;
   void MakeTab() override;
   void SetDrawADC(Int_t pos);
   void SetDrawRawADC(Int_t pos);
   void SetDrawArrayAug(Int_t pos, TString augName);
   void SetMap(std::shared_ptr<AtMap> map) { fDetmap = map; }
   void SetColumns(Int_t cols) { fCols = cols; }
   void SetRows(Int_t rows) {fRows = rows;}
   void SetTabName(TString tabName) { fTabName = tabName; }
   void DrawEvent(AtRawEvent *rawEvent, AtEvent *event) override;
   void DrawPad(Int_t padNum) override;

private:
   void SetDraw(Int_t pos, PadDrawType type);
   void DrawPosition(Int_t pos);
   void UpdateCvsPad();

   // Functions for drawing hits

   ClassDefOverride(AtEventTabPad, 1)
};

#endif
