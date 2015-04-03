#include "machineinfo.h"
#include <QApplication>

#include <cmath>
#include <iostream>
#include <cstdio>
using namespace std;

void usage() {
  printf("\n Usage: %s -keyword value\n", "machineinfo.exe");
  printf("        keyword   value\n");
  printf("        -MDIR     XiO tele (absolute) directory\n");
  printf("        -LHOME    Local Home Directory \n");
  printf("        -model    Machine Model\n");
  printf("        -fname    Machine Filename in LHOME/lib\n");
  printf("        -vendor   Machine Vendor Name\n");
  printf("\n");
}


int main(int argc, char *argv[])
{

    if (argc < 9) {
         usage();
         exit (-1);
    }


    char *fName = "Manufacturer.Model.MLC.info";
    char *vendor = "Manufacturer";
    char *model = "Model";
    char *MDIR = "";
    char *LHOME = "";
    char *LLIB = "";

    for(int iArg=0; iArg < argc; iArg++){
        if(iArg < argc-1){
        if( strcmp(argv[iArg],"-i") == 0 || strcmp(argv[iArg],"-fname") == 0) {
                iArg++;
                fName = argv[iArg];
        }
        if( strcmp(argv[iArg],"-model") == 0 || strcmp(argv[iArg],"-Model") == 0) {
                iArg++;
                model = argv[iArg];
        }
        if( strcmp(argv[iArg],"-manufacturer") == 0 || strcmp(argv[iArg],"-vendor") == 0) {
                iArg++;
                vendor = argv[iArg];
        }
        if( strcmp(argv[iArg],"-mdir") == 0 || strcmp(argv[iArg],"-MDIR") == 0) {
                iArg++;
                MDIR = argv[iArg];
        }
            if( strcmp(argv[iArg],"-lhome") == 0 || strcmp(argv[iArg],"-LHOME") == 0) {
                iArg++;
                LHOME = argv[iArg];
        }
            if( strcmp(argv[iArg],"-llib") == 0 || strcmp(argv[iArg],"-LLIB") == 0) {
                iArg++;
                LLIB = argv[iArg];
        }
            if(strcmp("-help", argv[iArg]) == 0 || strcmp("-h", argv[iArg]) == 0 ) {
            usage();
            return(0);
            }
        }
    }


    QApplication app(argc, argv);

    MachineInfo *dialog = new MachineInfo;
    // app.setCentralWidget(dialog);

    dialog->setMDIR(MDIR);
    dialog->setLHOME(LHOME);
    dialog->setMODEL(model);
    dialog->setModelFile(fName);
    dialog->setVendor(vendor);
    dialog->setTMPDIR(LLIB);

    dialog->getMachineInfo();
    dialog->updateAll();

    dialog->show();
    return app.exec();

}
