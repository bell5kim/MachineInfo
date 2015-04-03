#include "machineinfo.h"
#include "ui_machineinfo.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDomElement>
#include <QDir>
#include <QMessageBox>
#include <QSettings>


using namespace std;
#include <iostream>
#include <cmath>


MachineInfo::MachineInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MachineInfo)
{
    ui->setupUi(this);
}

MachineInfo::~MachineInfo()
{
    delete ui;
}


User *usr = new User;


void MachineInfo::init() {
 QRegExp regExp2d("[1-9]\\d{0,1}");
 QRegExp regExp3d("[1-9]\\d{0,2}");
 QRegExp regExpReal("\\d*\\.\\d+");

 ui->EnergyLineEdit->setValidator(new QRegExpValidator(regExp2d, this));
 ui->MaxFSWLineEdit->setValidator(new QRegExpValidator(regExp3d, this));
 ui->MaxFSLLineEdit->setValidator(new QRegExpValidator(regExp3d, this));
 ui->SFDLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 //ui->AvalLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->ESCDLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->SUJDLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->SLJDLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->UJTLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->LJTLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->SMDLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->tMLCLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->rMLCLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->cMLCLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->nMLCLineEdit->setValidator(new QRegExpValidator(regExp3d, this));
 ui->tkMLCLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 ui->iMLCLineEdit->setValidator(new QRegExpValidator(regExp3d, this));
 ui->thMLCLineEdit->setValidator(new QRegExpValidator(regExpReal, this));
 usr->Aval = "9.0";
}

void MachineInfo::clearModifiedAll()
{
   ui->FileNameLineEdit->clear();
   ui->ManufacturerLineEdit->clear();
   ui->ModelLineEdit->clear();
   ui->EnergyLineEdit->clear();
   ui->MaxFSWLineEdit->clear();
   ui->rMLCLineEdit->clear();
   ui->tkMLCLineEdit->clear();
   ui->ESCDLineEdit->clear();
   ui->SLJDLineEdit->clear();
   ui->SUJDLineEdit->clear();
   ui->SMDLineEdit->clear();
   ui->cMLCLineEdit->clear();
   ui->nMLCLineEdit->clear();
   ui->LJTLineEdit->clear();
   ui->tMLCLineEdit->clear();
   ui->UJTLineEdit->clear();
   ui->SFDLineEdit->clear();
   ui->AvalLineEdit->clear();
   ui->MaxFSLLineEdit->clear();
   ui->iMLCLineEdit->clear();
   ui->thMLCLineEdit->clear();

}

void MachineInfo::updateAll()
{
   ui->FileNameLineEdit->setText(usr->CurrentModelFile.simplified());
   ui->ManufacturerLineEdit->setText(usr->VENDOR.simplified());
   if (usr->MLCtype.contains("None"))ui->comboBoxMLCtype->setCurrentIndex(0);
   if (usr->MLCtype.contains("SIMPLE-MLC"))ui->comboBoxMLCtype->setCurrentIndex(1);
   if (usr->MLCtype.contains("DBLFOCUS-MLC"))ui->comboBoxMLCtype->setCurrentIndex(2);
   if (usr->MLCtype.contains("RNDFOCUS-MLC") )ui->comboBoxMLCtype->setCurrentIndex(3);
   if (usr->MLCtype.contains("ELEKTA-MLC"))ui->comboBoxMLCtype->setCurrentIndex(4);
   if (usr->MLCtype.contains("VARIAN-MLC"))ui->comboBoxMLCtype->setCurrentIndex(5);
   ui->ModelLineEdit->setText(usr->MODEL.simplified());
   ui->LineEditMLCtype->setText(usr->XIOMLC.simplified());
   ui->EnergyLineEdit->setText(usr->E0.simplified());
   ui->MaxFSWLineEdit->setText(usr->MAXFW.simplified());
   ui->rMLCLineEdit->setText(usr->rMLC.simplified());
   ui->tkMLCLineEdit->setText(usr->tkMLC.simplified());
   ui->ESCDLineEdit->setText(usr->ESCD.simplified());
   ui->SLJDLineEdit->setText(usr->SLJD.simplified());
   ui->SUJDLineEdit->setText(usr->SUJD.simplified());
   ui->SMDLineEdit->setText(usr->SMD.simplified());
   ui->cMLCLineEdit->setText(usr->cMLC.simplified());
   ui->nMLCLineEdit->setText(usr->nMLC.simplified());
   ui->LJTLineEdit->setText(usr->LJT.simplified());
   ui->tMLCLineEdit->setText(usr->tMLC.simplified());
   ui->UJTLineEdit->setText(usr->UJT.simplified());
   ui->SFDLineEdit->setText(usr->SFD.simplified());
   ui->AvalLineEdit->setText(usr->Aval.simplified());
   ui->MaxFSLLineEdit->setText(usr->MAXFL.simplified());
   ui->iMLCLineEdit->setText(usr->iMLC.simplified());
   ui->thMLCLineEdit->setText(usr->thMLC.simplified());
#ifdef XVMC
   if (usr->isMLC.contains("1")) {
     ui->isMLCcheckBox->setChecked(true);
   } else {
     ui->isMLCcheckBox->setChecked(false);
   }
#endif
   if (usr->MX.contains("1")) {
      ui->xMLCcheckBox->setChecked(true);
   } else {
      ui->xMLCcheckBox->setChecked(false);
   }
   if (usr->MY.contains("1")) {
      ui->yMLCcheckBox->setChecked(true);
   }  else {
      ui->yMLCcheckBox->setChecked(false);
   }

   if (usr->oMLC.contains("None"))ui->oMLCcomboBox->setCurrentIndex(0);
   if (usr->oMLC.contains("X"))ui->oMLCcomboBox->setCurrentIndex(1);
   if (usr->oMLC.contains("Y"))ui->oMLCcomboBox->setCurrentIndex(2);

   usr->isMachineModified=false;

}

void MachineInfo::setMDIR(char *usrText) {
 usr->MDIR = usrText;
 // QTextOStream(&usr->MDIR) << usrText;
}

void MachineInfo::setLHOME(char *usrText) {
 usr->LHOME = usrText;
}

void MachineInfo::setMODEL(char *usrText) {
 usr->MODEL = usrText;
 usr->CurrentMachine = usrText;
}

void MachineInfo::setModelFile(char *usrText) {
 usr->CurrentModelFile = usrText;
}

void MachineInfo::setVendor(char *usrText) {
 usr->VENDOR = usrText;
}

void MachineInfo::setTMPDIR(char *usrText) {
 usr->TMPDIR = usrText;
}

QString MachineInfo::mm2cm(QString mm) {
  bool ok;
  float value = mm.toFloat(&ok)/10.0;
  mm.sprintf("%7.2f",value);
  mm.simplified();
  return(mm);
}

void MachineInfo::clearMachineInfo() {
  usr->VERSION="";
  usr->CHARGE="";
  usr->MODEL="";
  usr->VENDOR="";
  usr->E0="";
  usr->REFDIST="";
  usr->REFDEPTH="";
  usr->MLCtype="";
  usr->MAXFW="";
  usr->MAXFL="";
  usr->ESCD="";
  usr->SMD="";
  usr->SUJD="";
  usr->SLJD="";
  usr->SFD="";
  usr->Aval="";
  usr->tMLC="";
  usr->UJT="";
  usr->LJT="";
  usr->rMLC="";
  usr->cMLC="";
  usr->MX="";
  usr->MY="";
  usr->oMLC="";
  usr->isMLC="";
  usr->nMLC="";
  usr->iMLC="";
  usr->tkMLC="";
  usr->thMLC="";
  usr->firstJaw="";
  usr->secondJaw="";
  usr->thirdJaw="";
  usr->XIOMLC="";
  usr->MLCDIRECT="";
  usr->XIOMLCID="";
  usr->MLCREFDIST="";
  for (int i=0; i<100; i++)  usr->xMLC[i]=0.0; // MLC position
}


void MachineInfo::readParm(QString mDir) {
  // cout << mDir << endl;
  QFile pFile( mDir );  // parm file in machine directory
  if (pFile.exists()) {
    QTextStream stream( &pFile );
    QString sLine;
    pFile.open( QIODevice::ReadOnly );

     // File Version Number
    sLine = stream.readLine().simplified();
     QTextStream(&sLine) >> usr->VERSION;

     // Description
    usr->MODEL = stream.readLine().simplified();

     // particle Charge
    usr->CHARGE = stream.readLine().simplified();

     // Machine Year
    sLine = stream.readLine().simplified();

     // Machine Manufacturer
    sLine = stream.readLine().simplified();

     // Machine Model
    sLine = stream.readLine().simplified();

     // Target to Flattening Filter Distance
    usr->SFD = stream.readLine().simplified();
    // QTextIStream(&sLine) >> usr->SFD;
    usr->SFD = mm2cm(usr->SFD);

     // Nominal Energy
    usr->E0 = stream.readLine().simplified();
     //QTextIStream(&sLine) >> usr->E0;

     // Reference Depth
    usr->REFDEPTH = stream.readLine().simplified();
     //QTextIStream(&sLine) >> usr->REFDEPTH;

     // Reference Distance (SCD/SAD)
    sLine = stream.readLine().simplified();
     QTextStream(&sLine) >> usr->REFDIST;

     // Horizontal Scan Reference Position
    usr->REFDIST = stream.readLine().simplified();
     //QTextIStream(&sLine) >> usr->HSCANREF;

     // Vertical Scan Reference Position
    sLine = stream.readLine().simplified();
     QTextStream(&sLine) >> usr->VSCANREF;

     // Maximum Field Width
    usr->MAXFW = stream.readLine().simplified();
     // QTextIStream(&sLine) >> usr->MAXFW;

     // Maximum Field Length
    usr->MAXFL = stream.readLine().simplified();
     //QTextIStream(&sLine) >> usr->MAXFL;

     // Mimimum Field Width
    sLine = stream.readLine().simplified();

     // Mimimum Field Length
    sLine = stream.readLine().simplified();

    pFile.close();
  }
}
/*
void MachineInfo::readParm(QString mDir) {
  // cout << mDir << endl;
  QFile pFile( mDir );  // parm file in machine directory
  if (pFile.exists()) {
    QTextStream stream( &pFile );
    QString sLine;
    pFile.open( IO_ReadOnly );
    for (int i=0;i<15;i++) {
      sLine = stream.readLine();  // skip 8 lines and set 9th line to sLine
      // cout << i << "  |  " << sLine << endl;
      if (i == 0) QTextIStream(&sLine) >> usr->VERSION;
      if (i == 1) QTextIStream(&sLine) >> usr->MODEL;
      if (i == 2) QTextIStream(&sLine) >> usr->CHARGE;
      if (i == 6) {
         QTextIStream(&sLine) >> usr->SFD;
         usr->SFD = mm2cm(usr->SFD);
      }
      if (i == 7) QTextIStream(&sLine) >> usr->E0;
      if (i == 8) QTextIStream(&sLine) >> usr->REFDEPTH;
      if (i == 9) QTextIStream(&sLine) >> usr->REFDIST;
      if (i == 9) QTextIStream(&sLine) >> usr->HSCANREF;
      if (i == 10) QTextIStream(&sLine) >> usr->VSCANREF;
      if (i == 12) QTextIStream(&sLine) >> usr->MAXFW;
      if (i == 13) QTextIStream(&sLine) >> usr->MAXFL;
    }
    pFile.close();
  }
}
*/
void MachineInfo::readCollim(QString mDir) {
  QFile cFile( mDir );  // collim file in machine directory
  if (cFile.exists()) {
    QTextStream stream( &cFile );
    QString sLine;
    cFile.open( QIODevice::ReadOnly );

     // Version Number
    usr->VERSION = stream.readLine().simplified();
     // QTextIStream(&sLine) >> usr->VERSION;

     // Effective Source to Collimator Distance
    usr->ESCD = stream.readLine().simplified();
     // QTextIStream(&sLine) >> usr->ESCD;
    usr->ESCD = mm2cm(usr->ESCD);

     // Collimator Angle
     QString colAngle = stream.readLine().simplified();
     // QTextIStream(&sLine) >> colAngle;

     // Collimator Angle Setting
     QString cAngle = stream.readLine().simplified();
     // QTextIStream(&sLine) >> cAngle;

     // Source to Tray Distance, minSTD, and max STD
     QString STD, minSTD, maxSTD;
    STD = stream.readLine().simplified();
     // QTextIStream(&sLine) >> STD;
     minSTD = STD.section(',',1,1);
     maxSTD = STD.section(',',2,2);
     STD = STD.section(',',0,0);

     // HLV of Tray
     QString hvlTray = stream.readLine().simplified();
     // QTextIStream(&sLine) >> hvlTray;

     // Thickness of Tray
     QString tTray  = stream.readLine().simplified();
     // QTextIStream(&sLine) >> tTray;

     // Material of Tray
     QString mTray = stream.readLine().simplified();
     // QTextIStream(&sLine) >> mTray;

     bool ok;
     // cout << hvlTray.toFloat(&ok) << "  " << tTray.toFloat(&ok) << endl;
     // if (hvlTray.toFloat(&ok) != 0.0 && tTray.toFloat(&ok) != 0.0) {

         // Default Values of number of HVL, thikness of HVL, and material of HVL
         QString nHVL, tHVL, mHVL;
        nHVL = stream.readLine().simplified();
         // QTextIStream(&sLine) >> nHVL;
         tHVL = nHVL.section(',',1,1);
         mHVL = mHVL.section(',',2,2);
         nHVL = nHVL.section(',',0,0);

         // Number of Trays
         QString nTrays = stream.readLine().simplified();
         // QTextIStream(&sLine) >> nTrays;
         int nTray = nTrays.toInt(&ok, 10);

         for (int iTray=0; iTray<nTray; iTray++){
            // Description of Tray
             QString dTray = stream.readLine().simplified();
             // QTextIStream(&sLine) >> dTray;

            // Tray Factor
             QString fTray  = stream.readLine().simplified();
             // QTextIStream(&sLine) >> fTray;

            // Tray Material
             QString matTray  = stream.readLine().simplified();
             // QTextIStream(&sLine) >> matTray;

            // Thickness of Tray
             QString thickTray  = stream.readLine().simplified();
             // QTextIStream(&sLine) >> thickTray;


            // Default Tray Material and Thickness but not separated
             QString mtTray  = stream.readLine().simplified();
             // QTextIStream(&sLine) >> mtTray;
         }

         // Number of Trays
         QString defTray  = stream.readLine().simplified();
         // QTextIStream(&sLine) >> defTray;
         // cout << "Number of Trays = " << defTray << endl;

         // MLC Type
        usr->XIOMLC = stream.readLine().simplified();
         // QTextIStream(&sLine) >> usr->XIOMLC;
         // cout << "usr->XIOMLC = " << usr->XIOMLC << endl;

         // Source to MLC Distance
        usr->SMD = stream.readLine().simplified();
         // QTextIStream(&sLine) >> usr->SMD;
         usr->SMD = mm2cm(usr->SMD);

         // MLC Edge AL
         QString edgeMLC = stream.readLine().simplified();
         // QTextIStream(&sLine) >> edgeMLC;

         // MLC Offset
         QString offsetMLC = stream.readLine().simplified();
         // QTextIStream(&sLine) >> offsetMLC;

         // MLC Type Number
         QString nTypeMLC = stream.readLine().simplified();
         // QTextIStream(&sLine) >> nTypeMLC;

         // MLC Leakage, Thickness, and Material
         usr->tMLC = stream.readLine().simplified();
       //QTextIStream(&sLine) >> usr->tMLC;
       usr->tMLC = mm2cm(usr->tMLC.section(',',1,1));

         // MLC Order (Length and Width)
       QString jawPosition = stream.readLine().simplified();
       // QTextIStream(&sLine) >> jawPosition;
       usr->firstJaw = jawPosition.section(',',0,0);
       usr->secondJaw = jawPosition.section(',',1,1);

       // Source to Upper Jaw Distance
        usr->SUJD = stream.readLine().simplified();
       // QTextIStream(&sLine) >> usr->SUJD;
       usr->SUJD = mm2cm(usr->SUJD);

         // Upper Jaw Thickness and Material
        usr->UJT = stream.readLine().simplified();
         // QTextIStream(&sLine) >> usr->UJT;
         usr->UJT = mm2cm(usr->UJT.section(',',0,0));

         // Upper Jaw Width and Length
         QString UJWL = stream.readLine().simplified();
         // QTextIStream(&sLine) >> UJWL;

       // Source to Lower Jaw Distance
        usr->SLJD = stream.readLine().simplified();
       // QTextIStream(&sLine) >> usr->SLJD;
       usr->SLJD = mm2cm(usr->SLJD);

         // Lower Jaw Thickness and Material
        usr->LJT = stream.readLine().simplified();
         // QTextIStream(&sLine) >> usr->LJT;
         usr->LJT = mm2cm(usr->LJT.section(',',0,0));

         // Lower Jaw Width and Length
         QString LJWL = stream.readLine().simplified();
         // QTextIStream(&sLine) >> LJWL;
     // }
    cFile.close();
  }
}

void MachineInfo::readMlc(QString mDir) {
  QFile mlcFile( mDir );  // mlc file in machine directory
  if (mlcFile.exists()) {
    QTextStream stream( &mlcFile );
    QString sLine;
    mlcFile.open( QIODevice::ReadOnly );

    sLine = stream.readLine();
    QTextStream(&sLine) >> usr->VERSION;

    QString MLCinfo="";
    sLine = stream.readLine();
    usr->XIOMLCID = sLine.section(',',0,0).simplified();
    usr->MLCDIRECT = sLine.section(',',1,1).simplified();
    if (usr->MLCDIRECT.contains('0')) usr->oMLC = "X";
    if (usr->MLCDIRECT.contains('1')) usr->oMLC = "Y";
    usr->nMLC = sLine.section(',',2,2).simplified();

    sLine = stream.readLine();
    usr->MLCREFDIST = mm2cm(sLine);

    bool ok;
    int nMLC = usr->nMLC.toInt(&ok,10);
    // cout << "nMLC = " << nMLC << endl;
    int iStart = 0; // MLC width change starts
    int iEnd = 0;   // MLC width change ends
    float tkMLC = 0.0;
    float thMLC = 0.0;

    for (int i=0;i<nMLC;i++) {
      sLine = stream.readLine();
      QString xMLC = mm2cm(sLine.section(',',0,0));
      bool ok;
      usr->xMLC[i] = xMLC.toFloat(&ok);
      // cout << i << "  " << usr->xMLC[i] << endl;
      if (i == 1) tkMLC = fabs(usr->xMLC[i] - usr->xMLC[i-1]);
      if (i > 0) {
     float mWidth = fabs(usr->xMLC[i] - usr->xMLC[i-1]);
         if (fabs(mWidth)-tkMLC != 0.0) {
            if (iStart == 0) {
              iStart = i;
              thMLC = mWidth;
            }
            else {
              iEnd = i;
            }
         }
      }
    }
    // cout << "iStart = " << iStart << "  " << "iEnd = " << iEnd << endl;
    int iMLC = (iEnd - iStart) + 1;
    if (iMLC == 1) iMLC = 0;
    usr->iMLC.sprintf("%d",iMLC);
    usr->tkMLC.sprintf("%d",(int)(tkMLC*10));
    usr->thMLC.sprintf("%d",(int)(thMLC*10));

    if (usr->XIOMLC.contains("MILLENNIUM120") ||
        usr->XIOMLC.contains("VARIAN40") ||
        usr->XIOMLC.contains("VARIAN26") ) {
       usr->VENDOR = "Varian";
       usr->MLCtype = "VARIAN-MLC";
       usr->rMLC = "8.00";
       usr->cMLC = usr->SMD;
       usr->MX = "0";
       usr->MY = "0";
    }
    if (usr->XIOMLC.contains("SIEMENSV50") ||
        usr->XIOMLC.contains("SIEMENSIEC") ) {
       usr->VENDOR = "Siemens";
       usr->MLCtype = "DBLFOCUS-MLC";
       usr->rMLC = "";
       usr->cMLC = "";
       usr->MX = "0";
       usr->MY = "0";
    }
    if (usr->XIOMLC.contains("ElektaBM80Leaf") ||
        usr->XIOMLC.contains("PHILIPSMLC") ) {
       usr->VENDOR = "Elekta";
       usr->MLCtype = "ELEKTA-MLC";
       usr->rMLC = "";
       usr->cMLC = "";
       usr->isMLC = "1";
       if (usr->MLCDIRECT.contains('0')) usr->MX = "1";
       if (usr->MLCDIRECT.contains('1')) usr->MY = "1";
       usr->iMLC = "0";
       usr->thMLC = "0";
    }

    mlcFile.close();
  }
}

void MachineInfo::getMachineInfo() {
  QString localInfo = usr->LHOME + usr->CurrentMachine
                    + "/" + usr->CurrentMachine + ".info";
  QFile infoFile(localInfo);  // mlc file in machine directory
  if (infoFile.exists()) {
     getLocalInfo(localInfo);
     usr->CurrentModelFile = usr->CurrentMachine + ".info";
  } else {
     getXiOInfo();
     usr->CurrentModelFile = "XiO Machine Files";
  }
}

void MachineInfo::resetMachine() {
   getXiOInfo();
   usr->CurrentModelFile = "XiO Machine Files";
   updateAll();
}

void MachineInfo::getXiOInfo() {
  clearMachineInfo();
  QString mDir;

  mDir = usr->MDIR + "/" + usr->CurrentMachine + "/parm" ;
  readParm(mDir);

  mDir = usr->MDIR + "/" + usr->CurrentMachine + "/collim" ;
  readCollim(mDir);

  mDir = usr->MDIR + "/" + usr->CurrentMachine + "/mlc" ;
  readMlc(mDir);
}

void MachineInfo::getLocalInfo(QString modelFile) {
 QFile mFile( modelFile );
 if (mFile.exists()) {
  QTextStream stream( &mFile );
  QString sLine;
  mFile.open( QIODevice::ReadOnly );
  // cout << modelFile << " is open" << endl;
  while ( !stream.atEnd() ) {
   sLine = stream.readLine();
   QString strLine = sLine.simplified();
   QString keyWord = strLine.section('=',0,0);
   QString keyValueTmp = strLine.section('#',0,0).section('=',1,1);
   QString keyValue = keyValueTmp.simplified();
   // cout << "keyWord = " << keyWord << "  keyValue = " << keyValue << endl;
   // if (keyWord.find("MODEL",0,true) != -1)  usr->MODEL = keyValue;
   if (keyWord.indexOf("MODEL",0) != -1)  usr->MODEL = keyValue;
   if (keyWord.contains("MODEL"))  usr->MODEL = keyValue;
   if (keyWord.contains("VENDOR")) usr->VENDOR = keyValue;
   if (keyWord.contains("E0"))     usr->E0 = keyValue;
   if (keyWord.contains("MLCtype")) usr->MLCtype = keyValue;
   if (keyWord.contains("MAXFW"))  usr->MAXFW = keyValue;
   if (keyWord.contains("MAXFL"))  usr->MAXFL = keyValue;
   if (keyWord.contains("ESCD"))   usr->ESCD = keyValue;
   if (keyWord.contains("SMD"))    usr->SMD = keyValue;
   if (keyWord.contains("SUJD"))   usr->SUJD = keyValue;
   if (keyWord.contains("SLJD"))   usr->SLJD = keyValue;
   if (keyWord.contains("SFD"))    usr->SFD = keyValue;
   if (keyWord.contains("AVAL"))   usr->Aval = keyValue;
   if (keyWord.contains("tMLC"))   usr->tMLC = keyValue;
   if (keyWord.contains("UJT"))    usr->UJT = keyValue;
   if (keyWord.contains("LJT"))    usr->LJT = keyValue;
   if (keyWord.contains("rMLC"))   usr->rMLC = keyValue;
   if (keyWord.contains("cMLC"))   usr->cMLC = keyValue;
   if (keyWord.contains("MX"))     usr->MX = keyValue;
   if (keyWord.contains("MY"))     usr->MY = keyValue;
   if (keyWord.contains("oMLC"))   usr->oMLC = keyValue;
   if (keyWord.contains("isMLC"))  usr->isMLC = keyValue;
   if (keyWord.contains("nMLC"))   usr->nMLC = keyValue;
   if (keyWord.contains("iMLC"))   usr->iMLC = keyValue;
   if (keyWord.contains("tkMLC"))  usr->tkMLC = keyValue;
   if (keyWord.contains("thMLC"))  usr->thMLC = keyValue;
   if (keyWord.contains("XIOMLC"))  usr->XIOMLC = keyValue;
  }
 }
 mFile.close();

}

void MachineInfo::writeModified (QString group){
 QDateTime currentDateTime = QDateTime::currentDateTime();
 QString DT = currentDateTime.toString();
 // cout << "Modified = " << group << "  " << usr->LHOME +usr->CurrentMachine << endl;
 QSettings settings;
 QString mDir = usr->LHOME + usr->CurrentMachine;
 // settings.insertSearchPath(QSettings::Unix, mDir);
 settings.setPath(QSettings::IniFormat, QSettings::UserScope, mDir);
 settings.beginGroup(group);
 settings.setValue("MachineModified", "Modified");
 settings.setValue("MachineModified_DT", DT);
 settings.setValue("Energy", usr->E0);
 settings.setValue("Energy_DT", DT);
 settings.setValue("ModelFile", usr->CurrentModelFile);
 settings.setValue("ModelFile_DT", DT);
 settings.setValue("MLCtype", usr->MLCtype);
 settings.setValue("MLCtype_DT", DT);
 settings.endGroup();
 // cout << "End of writeSetting" << endl;
}

void MachineInfo::writeNotModified (QString group){
 QDateTime currentDateTime = QDateTime::currentDateTime();
 QString DT = currentDateTime.toString();
 // cout << "Not Modified = " << group << "  " << usr->LHOME+usr->CurrentMachine << endl;
 QSettings settings;
 QString mDir = usr->LHOME + usr->CurrentMachine;
 settings.setPath(QSettings::IniFormat, QSettings::UserScope, mDir);
 settings.beginGroup(group);
 settings.setValue("MachineModified", "NotModified");
 settings.setValue("MachineModified_DT", DT);
 //settings.setValue("Energy", usr->E0);
 //settings.setValue("ModelFile", usr->CurrentModelFile);
 //settings.setValue("MLCtype", usr->MLCtype);
 settings.endGroup();
 // cout << "End of writeSetting" << endl;
}

void MachineInfo::writeMachineInfo() {
  usr->CurrentModelFile = usr->CurrentMachine + ".info";
  QString oFileName = usr->LHOME
                    + usr->CurrentMachine + "/"
                    + usr->CurrentModelFile;
  // cout << oFileName << endl;
  QFile oFile( oFileName );
  oFile.open( QIODevice::Unbuffered | QIODevice::ReadWrite );
  QTextStream oStream( &oFile );

  oStream << "MODEL = " << ui->ModelLineEdit->text()
          << "   # Model " << endl ;
  oStream << "VENDOR = " << usr->VENDOR
          << "   # Vendor " << endl ;
  oStream << "MLCtype = " << ui->comboBoxMLCtype->currentText()
          << "   # MLC Type" << endl;
  oStream << "E0 = " << ui->EnergyLineEdit->text()
          << "   # Nominal Photon Energy" << endl ;
  oStream << "MAXFW = " << ui->MaxFSWLineEdit->text()
          << "   # Max Field Width (mm)" << endl ;
  oStream << "MAXFL = " << ui->MaxFSLLineEdit->text()
          << "   # Max Field Length (mm)" << endl ;
  oStream << "ESCD = " << ui->ESCDLineEdit->text()
          << "   # Effective Source to Collimator Distance (cm)" << endl ;
  oStream << "SMD = " << ui->SMDLineEdit->text()
          << "   # Source to MLC (Middle) Distance (cm)" << endl ;
  oStream << "SUJD = " << ui->SUJDLineEdit->text()
          << "   # Source to Upper Jaw Distance (cm)" << endl ;
  oStream << "SLJD = " << ui->SLJDLineEdit->text()
          << "   # Source to Lower Jaw Distance (cm)" << endl ;
  oStream << "SFD = " << ui->SFDLineEdit->text()
          << "   # Source to Flattening Filter Bottom Distance (cm)" << endl ;
  oStream << "AVAL = " << ui->AvalLineEdit->text()
          << "   # Flattening Filter Attenuation Factor (A-VALUE)" << endl ;
  oStream << "tMLC = " << ui->tMLCLineEdit->text()
          << "   # MLC Thickness (cm)" << endl ;
  oStream << "UJT = " << ui->UJTLineEdit->text()
          << "   # Upper Jaw Thickness (cm)" << endl ;
  oStream << "LJT = " << ui->LJTLineEdit->text()
          << "   # Lower Jaw Thickness (cm)" << endl ;
  oStream << "rMLC = " << ui->rMLCLineEdit->text()
          << "   # Radius of Round Leaf (cm)" << endl ;
  oStream << "cMLC = " << ui->cMLCLineEdit->text()
          << "   # Center of Round Leaf (cm)" << endl ;
  if(ui->xMLCcheckBox->isChecked()) {
    oStream << "MX = 1   # MLC Including for X Penumbra Calculation (1/0)\n";
  } else {
    oStream << "MX = 0   # MLC Including for X Penumbra Calculation (1/0)\n";
  }
  if(ui->yMLCcheckBox->isChecked()) {
    oStream << "MY = 1   # MLC Including for Y Penumbra Calculation (1/0)\n";
  } else {
    oStream << "MY = 0   # MLC Including for Y Penumbra Calculation (1/0)\n";
  }
  oStream << "oMLC = " << ui->oMLCcomboBox->currentText()
          << "   # Orientation of MLC Travel (X/Y)" << endl;
#ifdef XVMC
   if(ui->isMLCcheckBox->isChecked()) {
     oStream << "isMLC = 1    # MLC Including in Model (1/0)\n";
   } else {
     oStream << "isMLC = 0    # MLC Including in Model (1/0)\n";
   }
#else
     oStream << "isMLC = 0    # MLC Including in Model (1/0)\n";
#endif
   oStream << "nMLC = " << ui->nMLCLineEdit->text()
           << "   # Number of Leaf Pairs" << endl ;
   oStream << "iMLC = " << ui->iMLCLineEdit->text()
           << "   # Number of Inner (thin) MLCs" << endl ;
   oStream << "tkMLC = " << ui->tkMLCLineEdit->text()
           << "   # Thick MLC width (mm)" << endl ;
   oStream << "thMLC = " << ui->thMLCLineEdit->text()
           << "   # Thin MLC width (mm)" << endl ;
   oStream << "XIOMLC = " << ui->LineEditMLCtype->text()
           << "   # XiO MLC Type" << endl ;

  oFile.close();
}

void MachineInfo::checkModified(){

 if (ui->ModelLineEdit->isModified()) usr->isMachineModified = true;
 if (usr->MLCtype.contains(ui->comboBoxMLCtype->currentText()))
                                 usr->isMachineModified = true;
 if (ui->EnergyLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->MaxFSWLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->MaxFSLLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->ESCDLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->SMDLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->SUJDLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->SLJDLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->SFDLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->AvalLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->tMLCLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->UJTLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->LJTLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->rMLCLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->cMLCLineEdit->isModified()) usr->isMachineModified = true;

 if(ui->xMLCcheckBox->isChecked()) {
   if (usr->MX.contains("0")) usr->isMachineModified = true;
 } else {
   if (usr->MX.contains("1")) usr->isMachineModified = true;
 }
 if(ui->yMLCcheckBox->isChecked()) {
   if (usr->MY.contains("0")) usr->isMachineModified = true;
 } else {
   if (usr->MY.contains("1")) usr->isMachineModified = true;
 }
 if (usr->oMLC.contains(ui->oMLCcomboBox->currentText()))
     usr->isMachineModified = true;
#ifdef XVMC
 if(isMLCcheckBox->isChecked()) {
   if (usr->isMLC.contains("0")) usr->isMachineModified = true;
 } else {
   if (usr->isMLC.contains("1")) usr->isMachineModified = true;
 }
#endif
 if (ui->nMLCLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->iMLCLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->tkMLCLineEdit->isModified()) usr->isMachineModified = true;
 if (ui->thMLCLineEdit->isModified()) usr->isMachineModified = true;

 writeMachineInfo();
  if (usr->isMachineModified == true) {
   // cout << "Save the new machine specification into " << usr->LHOME << "/"
   //         << usr->CurrentMachine << "/" << usr->CurrentMachine << ".info" << endl;
   writeModified(usr->CurrentMachine);

  QString mDir = usr->LHOME + usr->CurrentMachine;
  QDir *afitDir = new QDir;
  afitDir->setPath(mDir+"/afit");
  if(afitDir->exists()) {
     QString AFIT_INP_TMP = mDir + "/afit/afit.inp.tmp";
     QFile mFile(AFIT_INP_TMP);
     if (mFile.exists()) {
        QString CMD = "rm " + AFIT_INP_TMP;
        if (system(CMD.toStdString().c_str()) != 0) cout
                << "ERROR: Somethings are wrong: " << CMD.toStdString() << endl ;
     }
  }
  } else {
   writeNotModified(usr->CurrentMachine);
  }


  close();
}

void MachineInfo::Cancel(){
  writeNotModified(usr->CurrentMachine);
  close();
}
