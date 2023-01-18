#ifndef ATTABMAIN_H
#define ATTABMAIN_H

#include "AtEvent.h"    // IWYU pragma: keep
#include "AtRawEvent.h" // IWYU pragma: keep
#include "AtTabBase.h"

#include <Rtypes.h> // for Int_t, Bool_t, THashConsistencyHolder, Color_t
#include <TEvePointSet.h>
#include <TString.h> // for TString

#include <memory> // for shared_ptr
#include <set>
#include <string> // for string

class TBuffer;
class TClass;
class TMemberInspector;
class AtEventManagerNew;
class AtMap;
class TCanvas;
class TEvePointSet;
class TEveRGBAPalette;
class TH2Poly;
class TH1I;
class TPaletteAxis;
class AtTabInfo;

class AtTabMain : public AtTabBase {
protected:
   // Information for drawing 3D events
   Int_t fThreshold;
   // std::unique_ptr<TEvePointSet> fHitSet;
   TEvePointSet *fHitSet;

   Color_t fHitColor;
   Size_t fHitSize;
   Style_t fHitStyle;

   TCanvas *fCvsPadPlane;
   TH2Poly *fPadPlane;
   TCanvas *fCvsPadWave;
   TH1I *fPadWave;

   Int_t fMultiHit{10};

   std::string fInfoEventName{"AtEvent"};
   std::string fInfoRawEventName{"AtRawEvent"};

   TEveRGBAPalette *fRGBAPalette;

public:
   AtTabMain();
   void InitTab() override;
   void UpdateTab() override {}
   void Reset() override;
   void MakeTab() override;

   void DrawEvent() override;
   void DrawPad(Int_t PadNum) override;

   void SetThreshold(Int_t val) { fThreshold = val; }
   void SetHitAttributes(Color_t, Size_t, Style_t);
   void SetMultiHit(Int_t hitMax);

private:
   AtEvent *GetEvent();
   AtEvent *GetPatternEvent();
   AtRawEvent *GetRawEvent();

   // Functions to draw the initial canvases
   void DrawPadPlane();
   void DrawPadWave();

   // Functions to update the data on the canvases
   void UpdateCvsPadPlane();
   void UpdateCvsPadWave();

   // Functions for drawing hits
   void DrawHitPoints();
   bool DrawWave(Int_t PadNum);
   // std::unique_ptr<TEvePointSet> GetPointsFromHits(const std::vector<std::unique_ptr<AtHit>> &hits);
   TEvePointSet *GetPointsFromHits(const std::vector<std::unique_ptr<AtHit>> &hits);
   void FillPadPlane(const std::vector<std::unique_ptr<AtHit>> &hits);

   ClassDefOverride(AtTabMain, 1)
};

#endif
