#ifndef ATTABMAIN_H
#define ATTABMAIN_H

#include "AtTabBase.h"
#include "AtTabInfo.h"

#include <Rtypes.h>  // for Int_t, Bool_t, THashConsistencyHolder, Color_t
#include <TString.h> // for TString

class AtEvent;
class AtEventManagerNew;
class AtRawEvent;
class AtMap;
class TCanvas;
class TEvePointSet;
class TEveRGBAPalette;
class TH2Poly;
class TH1I;
class TPaletteAxis;

class AtTabMain : public AtTabBase {
protected:
   AtRawEvent *fRawEvent;
   AtEvent *fEvent;

   AtEventManagerNew *fEventManager;

   std::shared_ptr<AtMap> fDetmap;

   Int_t fThreshold;
   TString fMap;

   TEvePointSet *fHitSet;

   TPaletteAxis *fPadPlanePal;

   Color_t fHitColor;
   Size_t fHitSize;
   Style_t fHitStyle;

   TCanvas *fCvsPadPlane;
   TH2Poly *fPadPlane;
   TCanvas *fCvsPadWave;
   TH1I *fPadWave;

   Int_t fMultiHit{10};
   Bool_t fIsRawData;

   TString fEventBranch;
   TString fRawEventBranch;

   std::string fInfoEventName;
   std::string fInfoRawEventName;

   TEveRGBAPalette *fRGBAPalette;

public:
   AtTabMain();
   void InitTab() override;
   void UpdateTab() override;
   void Reset() override;
   void MakeTab() override;
   void DrawTree() override { };
   void DrawEvent() override;
   void DrawPad(Int_t PadNum) override;

   AtTabInfo *GetTabInfo() { return fTabInfo; }

   void SetMap(std::shared_ptr<AtMap> map) { fDetmap = map; }
   void SetThreshold(Int_t val) { fThreshold = val; }
   void SetHitAttributes(Color_t, Size_t, Style_t);
   void SetMultiHit(Int_t hitMax);

   void SetEventBranch(TString name) { fEventBranch = name; }
   void SetRawEventBranch(TString name) { fRawEventBranch = name; }

private:
   void DrawPadPlane();
   void DrawPadWave();

   void UpdateCvsPadPlane();
   void UpdateCvsPadWave();

   // Functions for drawing hits
   void DrawHitPoints();
   void DrawWave(Int_t PadNum);

   ClassDefOverride(AtTabMain, 1)
};

#endif
