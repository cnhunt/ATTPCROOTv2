#include "AtSidebarPSADeconv.h"

#include "AtPSADeconv.h"

ClassImp(AtSidebarPSADeconv);

void AtSidebarPSADeconv::FillFrame()
{
   AtSidebarPSA::FillFrame();

   AddIntBox(fOrder, "SetFilterOrder()", 0, 16);
   AddIntBox(fCutoff, "SetCutoffFreq()", 0, 512);

   SetIntNumber(fOrder, dynamic_cast<AtPSADeconv *>(fPSA)->GetFilterOrder());
   SetIntNumber(fCutoff, dynamic_cast<AtPSADeconv *>(fPSA)->GetCutoffFreq());
}

void AtSidebarPSADeconv::SetFilterOrder()
{
   auto value = GetIntNumber(fOrder);
   dynamic_cast<AtPSADeconv *>(fPSA)->SetFilterOrder(value);
   std::cout << fOrder << " set: " << value << std::endl;
}

void AtSidebarPSADeconv::SetCutoffFreq()
{
   auto value = GetIntNumber(fCutoff);
   dynamic_cast<AtPSADeconv *>(fPSA)->SetCutoffFreq(value);
   std::cout << fCutoff << " set: " << value << std::endl;
}
