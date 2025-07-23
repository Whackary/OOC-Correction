#include <chrono> // Needed for the run time measurment.
#include <iostream>
#include <vector>

#include "TFile.h" // Needed for opening the files.
#include "TROOT.h" // Needed for working with ROOT in general.
#include "TTree.h" // Needed for working with the trees.

#include "cluster_Data_Object.h" // Including the custom object that saves all the data for the clusters.
#include "CaloCellsMap.h" // Including the custom object that contains all the data for cells.
#include "Toolkit.h" // Including a custom file for several useful functions and data storage.

using namespace std;
using namespace std::chrono;

// This function's primary purposes is to control and run all the other classes.
void Object_Handler()
{
    // Setting up the tree files.
    TTree *tree;
    TTree *calo_tree;
    
    // Opening the files
    vector<const char*> *fileNames = new vector<const char*>;
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000037.outputGEPNtuple.root"); // Pt 100 sample.
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000049.outputGEPNtuple.root"); // Pt 100 sample.
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000050.outputGEPNtuple.root"); // Pt 100 sample.
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000073.outputGEPNtuple.root"); // Pt 100 sample.
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000079.outputGEPNtuple.root"); // Pt 100 sample.
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000086.outputGEPNtuple.root"); // Pt 100 sample.
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000091.outputGEPNtuple.root"); // Pt 100 sample.
    //fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000093.outputGEPNtuple.root"); // Pt 100 sample.
    fileNames->push_back("/home/zachary-carrender/Desktop/CERN/Files/user.joheinri.mc21_14TeV.900042.PG_singlepiplus_Pt100_etaFlatnp0_43.NTUP_GEP.e8557_s4422_r16128_x250722_EXT0/user.joheinri.45704251.EXT0._000096.outputGEPNtuple.root"); // Pt 100 sample.
    
    //TFile *file = TFile::Open("/home/zachary-carrender/Desktop/CERN/Files/NTUP_GEP.41930061._000069.pool.root"); // Charged pion sample.
    //TFile *file = TFile::Open("/home/zachary-carrender/Desktop/CERN/Files/NTUP_GEP.41864925._000023.pool.root"); // Neutral pion sample.
    

    
    TFile *calo_file = TFile::Open("/home/zachary-carrender/Desktop/CERN/Files/CaloCells.root"); // Detector data.
    if(!calo_file->IsOpen()){exit(EXIT_FAILURE);} // Checks to make sure the file was opened correctly.
    calo_file->GetObject("caloCellsMap", calo_tree);

    CaloCellsMap *calo_data = new CaloCellsMap(calo_tree); // Sets up the Calo Data Object
    calo_tree->GetEntry(0);

    TFile *file = TFile::Open(fileNames->front()); // Opens the file
    if(!file->IsOpen()){exit(EXIT_FAILURE);} // Checks to make sure the file was opened correctly.
    file->GetObject("ntuple", tree);

    cluster_Data_Object *data = new cluster_Data_Object(tree); // Sets up the Events Data Object
    tree->GetEntry(0);


    Toolkit *tools = new Toolkit(data, calo_data); // Sets up the Toolkit.


    int range = 0;
    bool badEvent;

    // Misc.
    auto start = high_resolution_clock::now(); // Clock for timing

    for(int i = 0; i < fileNames->size(); i++)
    {
        file = TFile::Open(fileNames->at(i)); // Opens the next file
        if(!file->IsOpen()){exit(EXIT_FAILURE);} // Checks to make sure the file was opened correctly.
        file->GetObject("ntuple", tree);

        data = new cluster_Data_Object(tree); // Sets up the next Events Data Object

        range = min(500, static_cast<int>(tree->GetEntries())); // How many events are there? tree->GetEntries() for the max from the file.

        std::cout<<"Begin of File: "<<fileNames->at(i)<<endl;

        for(int j = 0; j < range; j++)
        {
            tree->GetEntry(j); // Gets the entry, there are usually 500 in total.

            badEvent = tools->setupEvent(data, data->GEPBasicClusters_cell_ids, data->GEPBasicClusters_et, data->GEPBasicClusters_eta, data->GEPBasicClusters_phi, j); // Sets up the toolkit for the entry.
            if(badEvent){continue;} // Skips the event if it is 'bad' see tools->badEvent() for more info.

            tools->setupBlacklist(data->GEPBasicClusters_cell_ids); // Makes a blacklist filter for cells already in the cluster.
            //tools->setupBlacklist(data->CaloTopoClusters_cell_ids);
            tools->setupFilter(); // Sets up the filter with the most generous paramaters.
            
            tools->runGlobalFilter_fast(); // Filters all the cells with the global paramaters.
            tools->runPositionFilter();    // Filters all the cells with the position paramaters.
            tools->assignOOCCells();       // Assigns all the cells in the whitelist to a cluster.

            tools->createOOCJet(); // Creates the jet guess and resets the OOC energy.

            tools->runSearch(); // Runs the search and makes more jets.

            if(j == range-1 && i == fileNames->size()-1)
            {
                tools->Printout(); // Data Print Section.
                tools->Display(); // Graphics Section.
            }

            tools->eventCleanup(); // Cleans up the memory for the next event.

            if(j%25 == 0)
            {
                std::cout<<"--==-- End of event: ";
                if(j < 10){std::cout<<" ";}
                if(j < 100){std::cout<<" ";}
                std::cout<<j<<". --==--"<<endl;
            }
        }
        std::cout<<"End of File."<<endl;

        
    }

    // Timing Info.
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end-start).count();
    std::cout<<endl<<"Total Runtime: "<<duration<<endl;

    return;
}

