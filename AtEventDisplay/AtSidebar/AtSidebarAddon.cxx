#include "AtSidebarAddon.h"

#include <TString.h>

ClassImp(AtSidebarAddon);

void AtSidebarAddon::AddIntBox(std::string label, std::string function, int min, int max)
{
   auto bFrame = new TGHorizontalFrame(this);
   auto bLabel = new TGLabel(bFrame, (TString)label + ": ");
   auto bEntry = new TGNumberEntry(bFrame, 0., 6, -1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative,
                                   TGNumberFormat::kNELLimitMinMax, min, max);

   bEntry->Connect("ValueSet(Long_t)", ClassName(), this, (TString)function);
   bFrame->AddFrame(bLabel, new TGLayoutHints(kLHintsLeft | kLHintsCenterY, 1, 2, 1, 1));
   bFrame->AddFrame(bEntry);

   if (fNumbers.find(label) != fNumbers.end())
      std::cout << "Number labeled " << label << "already exists in this addon!" << std::endl;
   else
      fNumbers.insert({label, bEntry});

   this->AddFrame(bFrame);
}

Long_t AtSidebarAddon::GetIntNumber(std::string label)
{
   if (fNumbers.find(label) == fNumbers.end()) {
      std::cout << label << " not defined!" << std::endl;
      return 0;
   } else
      return fNumbers.find(label)->second->GetNumberEntry()->GetIntNumber();
}

void AtSidebarAddon::SetIntNumber(std::string label, Long_t value)
{
   if (fNumbers.find(label) == fNumbers.end())
      std::cout << label << " not defined!" << std::endl;
   else
      fNumbers.find(label)->second->GetNumberEntry()->SetIntNumber(value);
}
