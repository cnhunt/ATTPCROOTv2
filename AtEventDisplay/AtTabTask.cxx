#include "AtTabTask.h"
// IWYU pragma: no_include <ext/alloc_traits.h>

#include "AtEventManagerNew.h" // for AtEventManager

#include <iostream>

constexpr auto cRED = "\033[1;31m";
constexpr auto cYELLOW = "\033[1;33m";
constexpr auto cNORMAL = "\033[0m";
constexpr auto cGREEN = "\033[1;32m";
constexpr auto cBLUE = "\033[1;34m";

// using namespace std;

ClassImp(AtTabTask);

InitStatus AtTabTask::Init()
{

   std::cout << " =====  AtTabTask::Init =====" << std::endl;

   for (int i = 0; i < fTabs.size(); i++) {
      fTabs[i]->SetTabNumber(i);
      fTabs[i]->Init();
      fTabs[i]->MakeTab();
   }

   std::cout << " AtTabTask::Init : Initialization complete! "
             << "\n";
   return kSUCCESS;
}

void AtTabTask::Exec(Option_t *option)
{
   Reset();

   for (auto &fTab : fTabs) {
      fTab->Update();
      fTab->DrawEvent();
   }
}

void AtTabTask::Reset()
{
   for (auto &fTab : fTabs) {
      fTab->Reset();
   }
}

void AtTabTask::DrawPad(Int_t PadNum)
{
   for (auto &fTab : fTabs) {
      fTab->DrawPad(PadNum);
   }
}
