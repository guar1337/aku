#include <TVectorT.h>

void macro()
{
std::vector<float> stdVector;

for (int iii = 0; iii < 100; ++iii)
{
	stdVector.push_back(iii);
}

TVectorT<float> *TVector = new TVectorT<float>(stdVector.size(), &stdVector[0]);
TVectorT<float> *TVector2 = new TVectorT<float>;
TVector2->Add(*TVector);
}