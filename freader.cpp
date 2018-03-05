#include "interface.h"

void freader()
{
TSystemDirectory dir("wrk", s::work_dir.Data());
gSystem->cd(s::work_dir.Data());
//gSystem->cd(s::work_dir.Data());
cout<<gSystem->pwd()<<"\n\n";
TList *flist(dir.GetListOfFiles());
int iii=0;
while (flist->Last() != flist->At(iii-1))
{
printf("%i\n\t",iii);
cout<<flist->At(iii)->GetName();
iii++;
}
//cout<<flist->First();
}