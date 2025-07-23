#ifndef cluster_Data_Object_H
#define cluster_Data_Object_H

#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TTree.h"

using namespace std;

class cluster_Data_Object // This file's primary purpose is to serve as the object that saves all the data from the tree.
{
    public:
        // --------------
        // Creating the variables.
        // The segmenting here is both for readability and to break it into smaller sections.
        // The commented numbering at the back is the item's usual Branch Number(s) in the tree file.

        // There is some commented out code below, it is broken and IDK how to fix it.
        // I don't need it at the moment so until its needed it will remain commented out.
        std::vector<Float_t>            *GEPCellsTower_et       = {}; // 0
        std::vector<Float_t>            *GEPCellsTower_eta      = {}; // 1
        std::vector<Float_t>            *GEPCellsTower_phi      = {}; // 2
        std::vector<Float_t>            *GEPCellsTower_m        = {}; // 3
        std::vector<Int_t>              *GEPCellsTower_Ncells   = {}; // 4
        std::vector<std::vector<Int_t>> *GEPCellsTower_cell_ids = {}; // 5
        
        std::vector<Float_t>            *OfflineCellsTower_et       = {}; // 6
        std::vector<Float_t>            *OfflineCellsTower_eta      = {}; // 7
        std::vector<Float_t>            *OfflineCellsTower_phi      = {}; // 8
        std::vector<Float_t>            *OfflineCellsTower_m        = {}; // 9
        std::vector<Int_t>              *OfflineCellsTower_Ncells   = {}; // 10
        std::vector<std::vector<Int_t>> *OfflineCellsTower_cell_ids = {}; // 11

        std::vector<Float_t>            *CaloTopoClusters_et       = {}; // 12
        std::vector<Float_t>            *CaloTopoClusters_eta      = {}; // 13
        std::vector<Float_t>            *CaloTopoClusters_phi      = {}; // 14
        std::vector<Float_t>            *CaloTopoClusters_m        = {}; // 15
        std::vector<Int_t>              *CaloTopoClusters_Ncells   = {}; // 16
        std::vector<std::vector<Int_t>> *CaloTopoClusters_cell_ids = {}; // 17

        std::vector<Float_t>            *CaloTopoClusters422_et       = {}; // 18
        std::vector<Float_t>            *CaloTopoClusters422_eta      = {}; // 19
        std::vector<Float_t>            *CaloTopoClusters422_phi      = {}; // 20
        std::vector<Float_t>            *CaloTopoClusters422_m        = {}; // 21
        std::vector<Int_t>              *CaloTopoClusters422_Ncells   = {}; // 22
        std::vector<std::vector<Int_t>> *CaloTopoClusters422_cell_ids = {}; // 23

        std::vector<Float_t>            *GEPBasicClusters_et       = {}; // 24
        std::vector<Float_t>            *GEPBasicClusters_eta      = {}; // 25
        std::vector<Float_t>            *GEPBasicClusters_phi      = {}; // 26
        std::vector<Float_t>            *GEPBasicClusters_m        = {}; // 27
        std::vector<Int_t>              *GEPBasicClusters_Ncells   = {}; // 28
        std::vector<std::vector<Int_t>> *GEPBasicClusters_cell_ids = {}; // 29

        std::vector<Float_t>              *GEPCellsTowerModAntikTJets_pt             = {}; // 30
        std::vector<Float_t>              *GEPCellsTowerModAntikTJets_eta            = {}; // 31
        std::vector<Float_t>              *GEPCellsTowerModAntikTJets_phi            = {}; // 32
        std::vector<Float_t>              *GEPCellsTowerModAntikTJets_m              = {}; // 33
        std::vector<Int_t>                *GEPCellsTowerModAntikTJets_nConstituents  = {}; // 34
        //std::vector<std::vector<Float_t>> *GEPCellsTowerModAntikTJets_constituentPt  = {}; // 35
        //std::vector<std::vector<Float_t>> *GEPCellsTowerModAntikTJets_constituentEta = {}; // 36
        //std::vector<std::vector<Float_t>> *GEPCellsTowerModAntikTJets_constituentPhi = {}; // 37

        std::vector<Float_t>              *GEPOfflineCellsTowerModAntikTJets_pt             = {}; // 38
        std::vector<Float_t>              *GEPOfflineCellsTowerModAntikTJets_eta            = {}; // 39
        std::vector<Float_t>              *GEPOfflineCellsTowerModAntikTJets_phi            = {}; // 40
        std::vector<Float_t>              *GEPOfflineCellsTowerModAntikTJets_m              = {}; // 41
        std::vector<Int_t>                *GEPOfflineCellsTowerModAntikTJets_nConstituents  = {}; // 42
        //std::vector<std::vector<Float_t>> *GEPOfflineCellsTowerModAntikTJets_constituentPt  = {}; // 43
        //std::vector<std::vector<Float_t>> *GEPOfflineCellsTowerModAntikTJets_constituentEta = {}; // 44
        //std::vector<std::vector<Float_t>> *GEPOfflineCellsTowerModAntikTJets_constituentPhi = {}; // 45

        std::vector<Float_t>              *GEPCaloTopoClustersModAntikTJets_pt             = {}; // 46
        std::vector<Float_t>              *GEPCaloTopoClustersModAntikTJets_eta            = {}; // 47
        std::vector<Float_t>              *GEPCaloTopoClustersModAntikTJets_phi            = {}; // 48
        std::vector<Float_t>              *GEPCaloTopoClustersModAntikTJets_m              = {}; // 49
        std::vector<Int_t>                *GEPCaloTopoClustersModAntikTJets_nConstituents  = {}; // 50
        //std::vector<std::vector<Float_t>> *GEPCaloTopoClustersModAntikTJets_constituentPt  = {}; // 51
        //std::vector<std::vector<Float_t>> *GEPCaloTopoClustersModAntikTJets_constituentEta = {}; // 52
        //std::vector<std::vector<Float_t>> *GEPCaloTopoClustersModAntikTJets_constituentPhi = {}; // 53

        std::vector<Float_t>              *GEPCaloTopoClusters422ModAntikTJets_pt             = {}; // 54
        std::vector<Float_t>              *GEPCaloTopoClusters422ModAntikTJets_eta            = {}; // 55
        std::vector<Float_t>              *GEPCaloTopoClusters422ModAntikTJets_phi            = {}; // 56
        std::vector<Float_t>              *GEPCaloTopoClusters422ModAntikTJets_m              = {}; // 57
        std::vector<Int_t>                *GEPCaloTopoClusters422ModAntikTJets_nConstituents  = {}; // 58
        //std::vector<std::vector<Float_t>> *GEPCaloTopoClusters422ModAntikTJets_constituentPt  = {}; // 59
        //std::vector<std::vector<Float_t>> *GEPCaloTopoClusters422ModAntikTJets_constituentEta = {}; // 60
        //std::vector<std::vector<Float_t>> *GEPCaloTopoClusters422ModAntikTJets_constituentPhi = {}; // 61

        std::vector<Float_t>              *GEPBasicClustersModAntikTJets_pt             = {}; // 62
        std::vector<Float_t>              *GEPBasicClustersModAntikTJets_eta            = {}; // 63
        std::vector<Float_t>              *GEPBasicClustersModAntikTJets_phi            = {}; // 64
        std::vector<Float_t>              *GEPBasicClustersModAntikTJets_m              = {}; // 65
        std::vector<Int_t>                *GEPBasicClustersModAntikTJets_nConstituents  = {}; // 66
        //std::vector<std::vector<Float_t>> *GEPBasicClustersModAntikTJets_constituentPt  = {}; // 67
        //std::vector<std::vector<Float_t>> *GEPBasicClustersModAntikTJets_constituentEta = {}; // 68
        //std::vector<std::vector<Float_t>> *GEPBasicClustersModAntikTJets_constituentPhi = {}; // 69

        std::vector<Float_t>              *AntiKt4GepGEPCellsTowerAlgJets_pt             = {}; // 30
        std::vector<Float_t>              *AntiKt4GepGEPCellsTowerAlgJets_eta            = {}; // 31
        std::vector<Float_t>              *AntiKt4GepGEPCellsTowerAlgJets_phi            = {}; // 32
        std::vector<Float_t>              *AntiKt4GepGEPCellsTowerAlgJets_m              = {}; // 33
        std::vector<Int_t>                *AntiKt4GepGEPCellsTowerAlgJets_nConstituents  = {}; // 34
        //std::vector<std::vector<Float_t>> *AntiKt4GepGEPCellsTowerAlgJets_constituentPt  = {}; // 35
        //std::vector<std::vector<Float_t>> *AntiKt4GepGEPCellsTowerAlgJets_constituentEta = {}; // 36
        //std::vector<std::vector<Float_t>> *AntiKt4GepGEPCellsTowerAlgJets_constituentPhi = {}; // 37

        std::vector<Float_t>              *AntiKt4GepOfflineCellsTowerAlgJets_pt             = {}; // 38
        std::vector<Float_t>              *AntiKt4GepOfflineCellsTowerAlgJets_eta            = {}; // 39
        std::vector<Float_t>              *AntiKt4GepOfflineCellsTowerAlgJets_phi            = {}; // 40
        std::vector<Float_t>              *AntiKt4GepOfflineCellsTowerAlgJets_m              = {}; // 41
        std::vector<Int_t>                *AntiKt4GepOfflineCellsTowerAlgJets_nConstituents  = {}; // 42
        //std::vector<std::vector<Float_t>> *AntiKt4GepOfflineCellsTowerAlgJets_constituentPt  = {}; // 43
        //std::vector<std::vector<Float_t>> *AntiKt4GepOfflineCellsTowerAlgJets_constituentEta = {}; // 44
        //std::vector<std::vector<Float_t>> *AntiKt4GepOfflineCellsTowerAlgJets_constituentPhi = {}; // 45

        std::vector<Float_t>              *AntiKt4GepCaloTopoClustersAlgJets_pt             = {}; // 46
        std::vector<Float_t>              *AntiKt4GepCaloTopoClustersAlgJets_eta            = {}; // 47
        std::vector<Float_t>              *AntiKt4GepCaloTopoClustersAlgJets_phi            = {}; // 48
        std::vector<Float_t>              *AntiKt4GepCaloTopoClustersAlgJets_m              = {}; // 49
        std::vector<Int_t>                *AntiKt4GepCaloTopoClustersAlgJets_nConstituents  = {}; // 50
        //std::vector<std::vector<Float_t>> *AntiKt4GepCaloTopoClustersAlgJets_constituentPt  = {}; // 51
        //std::vector<std::vector<Float_t>> *AntiKt4GepCaloTopoClustersAlgJets_constituentEta = {}; // 52
        //std::vector<std::vector<Float_t>> *AntiKt4GepCaloTopoClustersAlgJets_constituentPhi = {}; // 53

        std::vector<Float_t>              *AntiKt4GepCaloTopoClusters422AlgJets_pt             = {}; // 54
        std::vector<Float_t>              *AntiKt4GepCaloTopoClusters422AlgJets_eta            = {}; // 55
        std::vector<Float_t>              *AntiKt4GepCaloTopoClusters422AlgJets_phi            = {}; // 56
        std::vector<Float_t>              *AntiKt4GepCaloTopoClusters422AlgJets_m              = {}; // 57
        std::vector<Int_t>                *AntiKt4GepCaloTopoClusters422AlgJets_nConstituents  = {}; // 58
        //std::vector<std::vector<Float_t>> *AntiKt4GepCaloTopoClusters422AlgJets_constituentPt  = {}; // 59
        //std::vector<std::vector<Float_t>> *AntiKt4GepCaloTopoClusters422AlgJets_constituentEta = {}; // 60
        //std::vector<std::vector<Float_t>> *AntiKt4GepCaloTopoClusters422AlgJets_constituentPhi = {}; // 61

        std::vector<Float_t>              *AntiKt4GepGEPBasicClustersAlgJets_pt             = {}; // 62
        std::vector<Float_t>              *AntiKt4GepGEPBasicClustersAlgJets_eta            = {}; // 63
        std::vector<Float_t>              *AntiKt4GepGEPBasicClustersAlgJets_phi            = {}; // 64
        std::vector<Float_t>              *AntiKt4GepGEPBasicClustersAlgJets_m              = {}; // 65
        std::vector<Int_t>                *AntiKt4GepGEPBasicClustersAlgJets_nConstituents  = {}; // 66
        //std::vector<std::vector<Float_t>> *AntiKt4GepGEPBasicClustersAlgJets_constituentPt  = {}; // 67
        //std::vector<std::vector<Float_t>> *AntiKt4GepGEPBasicClustersAlgJets_constituentEta = {}; // 68
        //std::vector<std::vector<Float_t>> *AntiKt4GepGEPBasicClustersAlgJets_constituentPhi = {}; // 69

        std::vector<Float_t>              *AntiKt4TruthJets_pt             = {}; // 70
        std::vector<Float_t>              *AntiKt4TruthJets_eta            = {}; // 71
        std::vector<Float_t>              *AntiKt4TruthJets_phi            = {}; // 72
        std::vector<Float_t>              *AntiKt4TruthJets_m              = {}; // 73
        std::vector<Int_t>                *AntiKt4TruthJets_nConstituents  = {}; // 74
        //std::vector<std::vector<Float_t>> *AntiKt4TruthJets_constituentPt  = {}; // 75
        //std::vector<std::vector<Float_t>> *AntiKt4TruthJets_constituentEta = {}; // 76
        //std::vector<std::vector<Float_t>> *AntiKt4TruthJets_constituentPhi = {}; // 77

        std::vector<Float_t> *L1_eEMRoI_et  = {}; // 78
        std::vector<Float_t> *L1_eEMRoI_eta = {}; // 79
        std::vector<Float_t> *L1_eEMRoI_phi = {}; // 80

        std::vector<Float_t> *L1_eTauRoI_et       = {}; // 81
        std::vector<Float_t> *L1_eTauRoI_eta      = {}; // 82
        std::vector<Float_t> *L1_eTauRoI_phi      = {}; // 83
        std::vector<Int_t>   *L1_eTauRoI_bdtScore = {}; // 84

        Int_t   eventNumber;                    // 85
        Int_t   runNumber;                      // 86
        Float_t weight;                         // 87
        Int_t   distFrontBunchTrain;            // 88
        Float_t averageInteractionsPerCrossing; // 89

        std::vector<Float_t> *cells_e           = {}; // 90
        std::vector<Float_t> *cells_et          = {}; // 91
        std::vector<Float_t> *cells_time        = {}; // 92
        std::vector<Int_t>   *cells_quality     = {}; // 93
        std::vector<Int_t>   *cells_provenance  = {}; // 94
        std::vector<Int_t>   *cells_ID          = {}; // 95

        std::vector<Float_t> *ph_parent = {}; // 96
        std::vector<Int_t>   *ph_pt     = {}; // 97
        std::vector<Int_t>   *ph_eta    = {}; // 98
        std::vector<Int_t>   *ph_phi    = {}; // 99

        std::vector<Float_t> *el_parent = {}; // 100
        std::vector<Int_t>   *el_pt     = {}; // 101
        std::vector<Int_t>   *el_eta    = {}; // 102
        std::vector<Int_t>   *el_phi    = {}; // 103
        
        cluster_Data_Object(TTree *tree) // The constructor
        {
            // This sets up all the data for the files.
            tree->SetBranchAddress("GEPCellsTower_et",       &GEPCellsTower_et);
            tree->SetBranchAddress("GEPCellsTower_eta",      &GEPCellsTower_eta);
            tree->SetBranchAddress("GEPCellsTower_phi",      &GEPCellsTower_phi);
            tree->SetBranchAddress("GEPCellsTower_m",        &GEPCellsTower_m);
            tree->SetBranchAddress("GEPCellsTower_Ncells",   &GEPCellsTower_Ncells);
            tree->SetBranchAddress("GEPCellsTower_cell_ids", &GEPCellsTower_cell_ids);
            
            tree->SetBranchAddress("OfflineCellsTower_et",       &OfflineCellsTower_et);
            tree->SetBranchAddress("OfflineCellsTower_eta",      &OfflineCellsTower_eta);
            tree->SetBranchAddress("OfflineCellsTower_phi",      &OfflineCellsTower_phi);
            tree->SetBranchAddress("OfflineCellsTower_m",        &OfflineCellsTower_m);
            tree->SetBranchAddress("OfflineCellsTower_Ncells",   &OfflineCellsTower_Ncells);
            tree->SetBranchAddress("OfflineCellsTower_cell_ids", &OfflineCellsTower_cell_ids);

            tree->SetBranchAddress("CaloTopoClusters_et",       &CaloTopoClusters_et);
            tree->SetBranchAddress("CaloTopoClusters_eta",      &CaloTopoClusters_eta);
            tree->SetBranchAddress("CaloTopoClusters_phi",      &CaloTopoClusters_phi);
            tree->SetBranchAddress("CaloTopoClusters_m",        &CaloTopoClusters_m);
            tree->SetBranchAddress("CaloTopoClusters_Ncells",   &CaloTopoClusters_Ncells);
            tree->SetBranchAddress("CaloTopoClusters_cell_ids", &CaloTopoClusters_cell_ids);

            tree->SetBranchAddress("CaloTopoClusters422_et",       &CaloTopoClusters422_et);
            tree->SetBranchAddress("CaloTopoClusters422_eta",      &CaloTopoClusters422_eta);
            tree->SetBranchAddress("CaloTopoClusters422_phi",      &CaloTopoClusters422_phi);
            tree->SetBranchAddress("CaloTopoClusters422_m",        &CaloTopoClusters422_m);
            tree->SetBranchAddress("CaloTopoClusters422_Ncells",   &CaloTopoClusters422_Ncells);
            tree->SetBranchAddress("CaloTopoClusters422_cell_ids", &CaloTopoClusters422_cell_ids);

            tree->SetBranchAddress("GEPBasicClusters_et",       &GEPBasicClusters_et);
            tree->SetBranchAddress("GEPBasicClusters_eta",      &GEPBasicClusters_eta);
            tree->SetBranchAddress("GEPBasicClusters_phi",      &GEPBasicClusters_phi);
            tree->SetBranchAddress("GEPBasicClusters_m",        &GEPBasicClusters_m);
            tree->SetBranchAddress("GEPBasicClusters_Ncells",   &GEPBasicClusters_Ncells);
            tree->SetBranchAddress("GEPBasicClusters_cell_ids", &GEPBasicClusters_cell_ids);

            /*
            tree->SetBranchAddress("GEPCellsTowerModAntikTJets_pt",             &GEPCellsTowerModAntikTJets_pt);
            tree->SetBranchAddress("GEPCellsTowerModAntikTJets_eta",            &GEPCellsTowerModAntikTJets_eta);
            tree->SetBranchAddress("GEPCellsTowerModAntikTJets_phi",            &GEPCellsTowerModAntikTJets_phi);
            tree->SetBranchAddress("GEPCellsTowerModAntikTJets_m",              &GEPCellsTowerModAntikTJets_m);
            tree->SetBranchAddress("GEPCellsTowerModAntikTJets_nConstituents",  &GEPCellsTowerModAntikTJets_nConstituents);
            //tree->SetBranchAddress("GEPCellsTowerModAntikTJets_constituentPt",  &GEPCellsTowerModAntikTJets_constituentPt);
            //tree->SetBranchAddress("GEPCellsTowerModAntikTJets_constituentEta", &GEPCellsTowerModAntikTJets_constituentEta);
            //tree->SetBranchAddress("GEPCellsTowerModAntikTJets_constituentPhi", &GEPCellsTowerModAntikTJets_constituentPhi);

            tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_pt",             &GEPOfflineCellsTowerModAntikTJets_pt);
            tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_eta",            &GEPOfflineCellsTowerModAntikTJets_eta);
            tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_phi",            &GEPOfflineCellsTowerModAntikTJets_phi);
            tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_m",              &GEPOfflineCellsTowerModAntikTJets_m);
            tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_nConstituents",  &GEPOfflineCellsTowerModAntikTJets_nConstituents);
            //tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_constituentPt",  &GEPOfflineCellsTowerModAntikTJets_constituentPt);
            //tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_constituentEta", &GEPOfflineCellsTowerModAntikTJets_constituentEta);
            //tree->SetBranchAddress("GEPOfflineCellsTowerModAntikTJets_constituentPhi", &GEPOfflineCellsTowerModAntikTJets_constituentPhi);

            tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_pt",             &GEPCaloTopoClustersModAntikTJets_pt);
            tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_eta",            &GEPCaloTopoClustersModAntikTJets_eta);
            tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_phi",            &GEPCaloTopoClustersModAntikTJets_phi);
            tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_m",              &GEPCaloTopoClustersModAntikTJets_m);
            tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_nConstituents",  &GEPCaloTopoClustersModAntikTJets_nConstituents);
            //tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_constituentPt",  &GEPCaloTopoClustersModAntikTJets_constituentPt);
            //tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_constituentEta", &GEPCaloTopoClustersModAntikTJets_constituentEta);
            //tree->SetBranchAddress("GEPCaloTopoClustersModAntikTJets_constituentPhi", &GEPCaloTopoClustersModAntikTJets_constituentPhi);

            tree->SetBranchAddress("GEPBasicClustersModAntikTJets_pt",             &GEPBasicClustersModAntikTJets_pt);
            tree->SetBranchAddress("GEPBasicClustersModAntikTJets_eta",            &GEPBasicClustersModAntikTJets_eta);
            tree->SetBranchAddress("GEPBasicClustersModAntikTJets_phi",            &GEPBasicClustersModAntikTJets_phi);
            tree->SetBranchAddress("GEPBasicClustersModAntikTJets_m",              &GEPBasicClustersModAntikTJets_m);
            tree->SetBranchAddress("GEPBasicClustersModAntikTJets_nConstituents",  &GEPBasicClustersModAntikTJets_nConstituents);
            //tree->SetBranchAddress("GEPBasicClustersModAntikTJets_constituentPt",  &GEPBasicClustersModAntikTJets_constituentPt);
            //tree->SetBranchAddress("GEPBasicClustersModAntikTJets_constituentEta", &GEPBasicClustersModAntikTJets_constituentEta);
            //tree->SetBranchAddress("GEPBasicClustersModAntikTJets_constituentPhi", &GEPBasicClustersModAntikTJets_constituentPhi);

            tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_pt",             &AntiKt4GepGEPCellsTowerAlgJets_pt);
            tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_eta",            &AntiKt4GepGEPCellsTowerAlgJets_eta);
            tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_phi",            &AntiKt4GepGEPCellsTowerAlgJets_phi);
            tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_m",              &AntiKt4GepGEPCellsTowerAlgJets_m);
            tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_nConstituents",  &AntiKt4GepGEPCellsTowerAlgJets_nConstituents);
            //tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_constituentPt",  &AntiKt4GepGEPCellsTowerAlgJets_constituentPt);
            //tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_constituentEta", &AntiKt4GepGEPCellsTowerAlgJets_constituentEta);
            //tree->SetBranchAddress("AntiKt4GepGEPCellsTowerAlgJets_constituentPhi", &AntiKt4GepGEPCellsTowerAlgJets_constituentPhi);

            tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_pt",             &AntiKt4GepOfflineCellsTowerAlgJets_pt);
            tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_eta",            &AntiKt4GepOfflineCellsTowerAlgJets_eta);
            tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_phi",            &AntiKt4GepOfflineCellsTowerAlgJets_phi);
            tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_m",              &AntiKt4GepOfflineCellsTowerAlgJets_m);
            tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_nConstituents",  &AntiKt4GepOfflineCellsTowerAlgJets_nConstituents);
            //tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_constituentPt",  &AntiKt4GepOfflineCellsTowerAlgJets_constituentPt);
            //tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_constituentEta", &AntiKt4GepOfflineCellsTowerAlgJets_constituentEta);
            //tree->SetBranchAddress("AntiKt4GepOfflineCellsTowerAlgJets_constituentPhi", &AntiKt4GepOfflineCellsTowerAlgJets_constituentPhi);

            tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_pt",             &AntiKt4GepCaloTopoClustersAlgJets_pt);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_eta",            &AntiKt4GepCaloTopoClustersAlgJets_eta);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_phi",            &AntiKt4GepCaloTopoClustersAlgJets_phi);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_m",              &AntiKt4GepCaloTopoClustersAlgJets_m);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_nConstituents",  &AntiKt4GepCaloTopoClustersAlgJets_nConstituents);
            //tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_constituentPt",  &AntiKt4GepCaloTopoClustersAlgJets_constituentPt);
            //tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_constituentEta", &AntiKt4GepCaloTopoClustersAlgJets_constituentEta);
            //tree->SetBranchAddress("AntiKt4GepCaloTopoClustersAlgJets_constituentPhi", &AntiKt4GepCaloTopoClustersAlgJets_constituentPhi);

            tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_pt",             &AntiKt4GepCaloTopoClusters422AlgJets_pt);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_eta",            &AntiKt4GepCaloTopoClusters422AlgJets_eta);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_phi",            &AntiKt4GepCaloTopoClusters422AlgJets_phi);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_m",              &AntiKt4GepCaloTopoClusters422AlgJets_m);
            tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_nConstituents",  &AntiKt4GepCaloTopoClusters422AlgJets_nConstituents);
            //tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_constituentPt",  &AntiKt4GepCaloTopoClusters422AlgJets_constituentPt);
            //tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_constituentEta", &AntiKt4GepCaloTopoClusters422AlgJets_constituentEta);
            //tree->SetBranchAddress("AntiKt4GepCaloTopoClusters422AlgJets_constituentPhi", &AntiKt4GepCaloTopoClusters422AlgJets_constituentPhi);

            tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_pt",             &AntiKt4GepGEPBasicClustersAlgJets_pt);
            tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_eta",            &AntiKt4GepGEPBasicClustersAlgJets_eta);
            tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_phi",            &AntiKt4GepGEPBasicClustersAlgJets_phi);
            tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_m",              &AntiKt4GepGEPBasicClustersAlgJets_m);
            tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_nConstituents",  &AntiKt4GepGEPBasicClustersAlgJets_nConstituents);
            //tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_constituentPt",  &AntiKt4GepGEPBasicClustersAlgJets_constituentPt);
            //tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_constituentEta", &AntiKt4GepGEPBasicClustersAlgJets_constituentEta);
            //tree->SetBranchAddress("AntiKt4GepGEPBasicClustersAlgJets_constituentPhi", &AntiKt4GepGEPBasicClustersAlgJets_constituentPhi);
            */

            tree->SetBranchAddress("AntiKt4TruthJets_pt",             &AntiKt4TruthJets_pt);
            tree->SetBranchAddress("AntiKt4TruthJets_eta",            &AntiKt4TruthJets_eta);
            tree->SetBranchAddress("AntiKt4TruthJets_phi",            &AntiKt4TruthJets_phi);
            tree->SetBranchAddress("AntiKt4TruthJets_m",              &AntiKt4TruthJets_m);
            tree->SetBranchAddress("AntiKt4TruthJets_nConstituents",  &AntiKt4TruthJets_nConstituents);
            //tree->SetBranchAddress("AntiKt4TruthJets_constituentPt",  &AntiKt4TruthJets_constituentPt);
            //tree->SetBranchAddress("AntiKt4TruthJets_constituentEta", &AntiKt4TruthJets_constituentEta);
            //tree->SetBranchAddress("AntiKt4TruthJets_constituentPhi", &AntiKt4TruthJets_constituentPhi);

            tree->SetBranchAddress("L1_eEMRoI_et",  &L1_eEMRoI_et);
            tree->SetBranchAddress("L1_eEMRoI_eta", &L1_eEMRoI_eta);
            tree->SetBranchAddress("L1_eEMRoI_phi", &L1_eEMRoI_phi);

            tree->SetBranchAddress("L1_eTauRoI_et",       &L1_eTauRoI_et);
            tree->SetBranchAddress("L1_eTauRoI_eta",      &L1_eTauRoI_eta);
            tree->SetBranchAddress("L1_eTauRoI_phi",      &L1_eTauRoI_phi);
            tree->SetBranchAddress("L1_eTauRoI_bdtScore", &L1_eTauRoI_bdtScore);

            tree->SetBranchAddress("eventNumber",                    &eventNumber);
            tree->SetBranchAddress("runNumber",                      &runNumber);
            tree->SetBranchAddress("weight",                         &weight);
            tree->SetBranchAddress("distFrontBunchTrain",            &distFrontBunchTrain);
            tree->SetBranchAddress("averageInteractionsPerCrossing", &averageInteractionsPerCrossing);

            //tree->SetBranchAddress("cells_e",          &cells_e);
            tree->SetBranchAddress("cells_et",         &cells_et);
            tree->SetBranchAddress("cells_time",       &cells_time);
            tree->SetBranchAddress("cells_quality",    &cells_quality);
            tree->SetBranchAddress("cells_provenance", &cells_provenance);
            tree->SetBranchAddress("cells_ID",         &cells_ID);

            tree->SetBranchAddress("ph_parent", &ph_parent);
            tree->SetBranchAddress("ph_pt",     &ph_pt);
            tree->SetBranchAddress("ph_eta",    &ph_eta);
            tree->SetBranchAddress("ph_phi",    &ph_phi);

            tree->SetBranchAddress("el_parent", &el_parent);
            tree->SetBranchAddress("el_pt",     &el_pt);
            tree->SetBranchAddress("el_eta",    &el_eta);
            tree->SetBranchAddress("el_phi",    &el_phi);
        }
        
};

#endif