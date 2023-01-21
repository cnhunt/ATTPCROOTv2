#include "AtSidebarPSA.h"

#include "AtPSA.h"

ClassImp(AtSidebarPSA);

void AtSidebarPSA::FillFrame()
{
   AddIntBox(fThreshold, "SetThreshold()", 0, 4000);

   SetIntNumber(fThreshold, fPSA->GetThreshold());
}

void AtSidebarPSA::SetThreshold()
{
   auto value = GetIntNumber(fThreshold);
   fPSA->SetThreshold(value);
   std::cout << "Threshold set: " << value << std::endl;
}