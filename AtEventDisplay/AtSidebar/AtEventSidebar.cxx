#include "AtEventSidebar.h"

#include "AtSidebarFrames.h" // for AtSidebarFrame, AtSidebarBranchControl
#include "AtViewerManager.h"

#include <FairLogger.h>

#include <TGClient.h> // for TGClient, gClient
#include <TGLayout.h> // for TGLayoutHints, kLHintsExpandX

#include <algorithm> // for max
void AtEventSidebar::FillFrames()
{
   for (auto frame : fFrames)
      frame->FillFrame();

   MapSubwindows();
   Resize();
   MapWindow();
}

AtEventSidebar::AtEventSidebar(DataHandling::AtTreeEntry &entryNum, DataHandling::AtBranch &rawEvent,
                               DataHandling::AtBranch &event, DataHandling::AtBranch &patternEvent)
   : TGMainFrame(gClient->GetRoot(), 1000, 600)
{
   SetWindowName("XX GUI");
   SetCleanup(kDeepCleanup);

   // Add frame components that are always there
   auto runInfo = new AtSidebarRunInfo(this);
   auto runControl = new AtSidebarEventControl(entryNum, this);
   auto branchControl = new AtSidebarBranchControl(rawEvent, event, patternEvent, this);
   auto padControl = new AtSidebarPadControl(AtViewerManager::Instance()->GetPadNum(), this);

   AddSidebarFrame(runInfo);
   AddSidebarFrame(runControl);
   AddSidebarFrame(branchControl);
   AddSidebarFrame(padControl);
}

void AtEventSidebar::AddSidebarFrame(AtSidebarFrame *frame)
{
   if (frame->GetParent() != this)
      LOG(fatal) << "Cannot pass a sidebar frame whose parent (" << frame->GetParent() << ") isn't the sidebar ("
                 << this << ")";

   fFrames.push_back(frame);
   TGMainFrame::AddFrame(frame, new TGLayoutHints(kLHintsExpandX));
   frame->Layout();
}

void AtEventSidebar::UsePictureButtons(bool val)
{
   for (auto frame : fFrames)
      frame->UsePictureButtons(val);
}
