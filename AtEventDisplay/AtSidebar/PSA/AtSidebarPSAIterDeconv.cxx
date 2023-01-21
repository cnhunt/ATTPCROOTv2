#include "AtSidebarPSAIterDeconv.h"

#include "AtPSAIterDeconv.h"

ClassImp(AtSidebarPSAIterDeconv);

void AtSidebarPSAIterDeconv::FillFrame()
{
   AtSidebarPSADeconv::FillFrame();

   AddIntBox(fIterations, "SetIterations()", 0, 10);

   SetIntNumber(fIterations, dynamic_cast<AtPSAIterDeconv *>(fPSA)->GetIterations());
}

void AtSidebarPSAIterDeconv::SetIterations()
{
   auto value = GetIntNumber(fIterations);
   dynamic_cast<AtPSAIterDeconv *>(fPSA)->SetIterations(value);
   std::cout << fIterations << " set: " << value << std::endl;
}
