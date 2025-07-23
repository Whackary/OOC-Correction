#ifndef CaloCellsMap_H
#define CaloCellsMap_H

#include <cmath> //Needed for the pow() function.
#include <iostream>
//#include <map>
#include <vector>

#include "TROOT.h"
#include "TTree.h"

using namespace std;

// --------------
// This file's primary purpose is to serve as the object that saves all the data for the Calo Cells and their location.
class CaloCellsMap
{
    public:
        // There is some commented out code below, it is broken and IDK how to fix it.
        // I don't need it at the moment so until its needed it will remain commented out.
        std::vector<Float_t> *cells_e = {}; // 0
        std::vector<Float_t> *cells_et = {}; // 1

        std::vector<Float_t> *cells_time = {}; // 2

        //std::vector<std::vector<Int_t>> *cells_quality = {}; // 3
        //std::vector<std::vector<Int_t>> *cells_provenance = {}; // 4

        std::vector<Float_t> *cells_eta = {}; // 5
        std::vector<Float_t> *cells_phi = {}; // 6
        std::vector<Float_t> *cells_sinTh = {}; // 7
        std::vector<Float_t> *cells_cosTh = {}; // 8
        std::vector<Float_t> *cells_sinPhi = {}; // 9
        std::vector<Float_t> *cells_cosPhi = {}; // 10
        std::vector<Float_t> *cells_cotTh = {}; // 11

        std::vector<Float_t> *cells_x = {}; // 12
        std::vector<Float_t> *cells_y = {}; // 13
        std::vector<Float_t> *cells_z = {}; // 14

        std::vector<Float_t> *cells_etaMin = {}; // 15
        std::vector<Float_t> *cells_etaMax = {}; // 16
        std::vector<Float_t> *cells_phiMin = {}; // 17
        std::vector<Float_t> *cells_phiMax = {}; // 18

        std::vector<Float_t> *cells_etaGranularity = {}; // 19
        std::vector<Float_t> *cells_phiGranularity = {}; // 20

        std::vector<Int_t> *cells_layer = {}; // 21
        std::vector<Int_t> *cells_ID = {}; // 22

        std::vector<Float_t> *cells_totalNoise = {}; // 23
        std::vector<Float_t> *cells_electronicNoise = {}; // 24

        std::vector<string> *cells_detName = {}; // 25

        std::vector<Int_t> *cells_sampling = {}; // 26

        std::vector<bool> *cells_badcell = {}; // 27

        std::vector<bool> *cells_IsEM = {}; // 28
        std::vector<bool> *cells_IsEM_Barrel = {}; // 29
        std::vector<bool> *cells_IsEM_EndCap = {}; // 30
        std::vector<bool> *cells_IsEM_BarrelPos = {}; // 31
        std::vector<bool> *cells_IsFCAL = {}; // 32
        std::vector<bool> *cells_IsHEC = {}; // 33
        std::vector<bool> *cells_IsTile = {}; // 34

        std::vector<std::vector<Int_t>> *cells_neighbours = {}; // 35

        CaloCellsMap(TTree *calo_tree)
        {
            calo_tree->SetBranchAddress("cells_e", &cells_e);
            calo_tree->SetBranchAddress("cells_et", &cells_et);

            calo_tree->SetBranchAddress("cells_time", &cells_time);

            //calo_tree->SetBranchAddress("cells_quality", &cells_quality);
            //calo_tree->SetBranchAddress("cells_provenance", &cells_provenance);

            calo_tree->SetBranchAddress("cells_eta", &cells_eta);
            calo_tree->SetBranchAddress("cells_phi", &cells_phi);
            calo_tree->SetBranchAddress("cells_sinTh", &cells_sinTh);
            calo_tree->SetBranchAddress("cells_cosTh", &cells_cosTh);
            calo_tree->SetBranchAddress("cells_sinPhi", &cells_sinPhi);
            calo_tree->SetBranchAddress("cells_cosPhi", &cells_cosPhi);
            calo_tree->SetBranchAddress("cells_cotTh", &cells_cotTh);

            calo_tree->SetBranchAddress("cells_x", &cells_x);
            calo_tree->SetBranchAddress("cells_y", &cells_y);
            calo_tree->SetBranchAddress("cells_z", &cells_z);

            calo_tree->SetBranchAddress("cells_etaMin", &cells_etaMin);
            calo_tree->SetBranchAddress("cells_etaMax", &cells_etaMax);
            calo_tree->SetBranchAddress("cells_phiMin", &cells_phiMin);
            calo_tree->SetBranchAddress("cells_phiMax", &cells_phiMax);

            calo_tree->SetBranchAddress("cells_etaGranularity", &cells_etaGranularity);
            calo_tree->SetBranchAddress("cells_phiGranularity", &cells_phiGranularity);

            calo_tree->SetBranchAddress("cells_layer", &cells_layer);
            calo_tree->SetBranchAddress("cells_ID", &cells_ID);

            calo_tree->SetBranchAddress("cells_totalNoise", &cells_totalNoise);
            calo_tree->SetBranchAddress("cells_electronicNoise", &cells_electronicNoise);

            calo_tree->SetBranchAddress("cells_detName", &cells_detName);

            calo_tree->SetBranchAddress("cells_sampling", &cells_sampling);

            calo_tree->SetBranchAddress("cells_badcell", &cells_badcell);

            calo_tree->SetBranchAddress("cells_IsEM", &cells_IsEM);
            calo_tree->SetBranchAddress("cells_IsEM_Barrel", &cells_IsEM_Barrel);
            calo_tree->SetBranchAddress("cells_IsEM_EndCap", &cells_IsEM_EndCap);
            calo_tree->SetBranchAddress("cells_IsEM_BarrelPos", &cells_IsEM_BarrelPos);
            calo_tree->SetBranchAddress("cells_IsFCAL", &cells_IsFCAL);
            calo_tree->SetBranchAddress("cells_IsHEC", &cells_IsHEC);
            calo_tree->SetBranchAddress("cells_IsTile", &cells_IsTile);

            calo_tree->SetBranchAddress("cells_neighbours", &cells_neighbours);
        }
};

#endif