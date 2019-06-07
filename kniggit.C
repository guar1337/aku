#  include <QFileDialog>
#  include <QString>
#  include "TString.h"

void kniggit()
{
   QString fileName = QFileDialog::getOpenFileName ();
   std::string flnm = fileName.toStdString();
}		
