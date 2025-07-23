#ifndef Toolkit_H
#define Toolkit_H

#include <algorithm>
#include <chrono> // Needed for the run time measurment.
#include <iostream> // Needed for c++ in general.
#include <TLorentzVector.h> // Needed for measuring distance and fastjet.
#include <vector>

#include "TCanvas.h"
#include "TGaxis.h"
#include "TGraph2D.h"
#include "TView.h"
#include "TPaveText.h"
#include "TPolyMarker3D.h"

#include "cluster_Data_Object.h" // Including the custom object that saves all the data for the clusters.
#include "CaloCellsMap.h" // Including the custom object that contains all the data for cells.

#include "fastjet/AreaDefinition.hh" // Needed for fastjet. (Probably)
#include "fastjet/ClusterSequenceArea.hh" // Needed for fastjet. (Probably)
#include "fastjet/PseudoJet.hh" // Needed for fastjet. (Probably)
#include "/home/zachary-carrender/Desktop/CERN/Code/GlobalTrigger_HIST_production_Repository/include/topo_cluster.h" // Needed for fastjet.
#include "/home/zachary-carrender/Desktop/CERN/Code/GlobalTrigger_HIST_production_Repository/include/jet_finder.h" // Needed for fastjet. (Probably)

using namespace std;
using namespace std::chrono;

class Data // This class holds all the data needed by the program, and is used to call the data.
{
    private:
        cluster_Data_Object *Event_Data;    // Local data holding the info of the events.
        CaloCellsMap *Calo_Data;            // Local calo data object holding the data of the detector.

        map<Int_t, Int_t> ID_Map; // A map file that when given an ID returns its index in the vector.
                                  // Fix later, replace with something with O(1) speed, currently has O(15) speed on average.
    
    public:
        Data(cluster_Data_Object *event_data, CaloCellsMap *calo_data) // The constructor.
        {
            Event_Data = event_data; // Saves the data of the event.
            Calo_Data = calo_data;   // Saves the data of the detector.

            ID_Map = {};         // Setting up the Map File.
            Int_t tempIndex = 0; // Some temp local variables for lambda capture expressions.
            map<int, int> tempID_Map = {};
            for_each(event_data->cells_ID->begin(), event_data->cells_ID->end(), [&tempID_Map, &tempIndex] (Int_t i)
            {
                tempID_Map[i] = tempIndex;
                tempIndex++;
            });
            ID_Map = tempID_Map; // Saves the data of the ID Map.
        }

        void updateEvent(cluster_Data_Object *event_data){Event_Data = event_data;} // Updates the event data for a new event. 

        Int_t I(Int_t ID){return ID_Map[ID];} // The Index of a Given ID.

        Float_t E(Int_t i) // The energy of a cell.
        {
            if(Event_Data->cells_e != NULL)
            {
                return Event_Data->cells_e->at(i);
            }
            return Event_Data->cells_et->at(i) * std::cosh(Eta(i));
        }
        Float_t ET(Int_t i){return Event_Data->cells_et->at(i);} // The transverse energy of a cell.
        Float_t EN(Int_t i){return E(i) / TotalNoise(i);} // The normalized energy of a cell.
        Float_t ENT(Int_t i){return ET(i) / TotalNoise(i);} // The normalized transverse energy of a cell.

        Float_t X(Int_t i){return Calo_Data->cells_x->at(i);} // The x position of a cell.
        Float_t Y(Int_t i){return Calo_Data->cells_y->at(i);} // The y position of a cell.
        Float_t Z(Int_t i){return Calo_Data->cells_z->at(i);} // The z position of a cell.

        Float_t Eta(Int_t i){return Calo_Data->cells_eta->at(i);} // The eta position of a cell.
        Float_t Phi(Int_t i){return Calo_Data->cells_phi->at(i);} // The phi position of a cell.

        Float_t Radius(Int_t i){return sqrt(X(i)*X(i)+X(i)*Y(i)+Z(i)*Z(i));} // The distance from the orign of a cell.
        Float_t DeltaR(Int_t i, Float_t eta, Float_t phi) // The Delta R distance between a cell and a given eta and phi.
        {
            Float_t deta = Eta(i)-eta;
            Float_t dphi = TVector2::Phi_mpi_pi(Phi(i)-phi);
            return sqrt(deta*deta + dphi*dphi);
        }

        Float_t TotalNoise(Int_t i){return Calo_Data->cells_totalNoise->at(i);} // The total noise of a cell.
        bool BadCell(Int_t i){return Calo_Data->cells_badcell->at(i);} // Is the cell a bad cell? Returns true if it is.

        vector<Float_t>* AntiKt4TruthJets_eta(){return Event_Data->AntiKt4TruthJets_eta;} // The eta of the truth jets.
        vector<Float_t>* AntiKt4TruthJets_phi(){return Event_Data->AntiKt4TruthJets_phi;} // The phi of the truth jets.
        vector<Float_t>* AntiKt4TruthJets_pt() {return Event_Data->AntiKt4TruthJets_pt;}  // The pt of the truth jets.

};

class Cluster // Stores the IDs of the Cells in the cluster along with info about the cluster.
{
    private:
        Data *data;
    public:
        vector<Int_t> *cluster = new vector<Int_t>(); // Holds all the indexes of each cell in the cluster.

        Float_t Eta;    // The eta location of the sigma 4 cell in the cluster.
        Float_t Phi;    // The phi location of the sigma 4 cell in the cluster.

        struct clusterData // Cluster Energy and Position Structure.
        {
            Float_t total   = 0;    // The total sum of all the values of the cluster.
            Float_t OOC     = 0;    // The Out of Cluster energy.

            Int_t min;              // The index of the minimum cell in the cluster.
            Int_t max;              // The index of the maximum cell in the cluster
        }
        *e = new clusterData(),
        *et = new clusterData(),
        *en = new clusterData(),
        *ent = new clusterData(),
        *x = new clusterData(),
        *y = new clusterData(),
        *z = new clusterData(),
        *eta = new clusterData(),
        *phi = new clusterData(),
        *radius = new clusterData(),
        *delr = new clusterData();

        Cluster(vector<Int_t> *indices, Float_t transverse_energy, Float_t eta_var, Float_t phi_var, Data *d) // The Constructor.
        {
            if(indices->empty()){throw invalid_argument("Empty vector passed to the Cluster!");} // Empty Check

            data = d; // Saves the data.

            cluster->insert(cluster->end(), indices->begin(), indices->end()); // Saves the cells

            Eta = eta_var; // Saves the celtral Eta of the cluster.
            Phi = phi_var; // Saves the celtral Phi of the cluster.
            
            // Setting up the energy part 1.
            e->total   = data->E(front());
            et->total  = transverse_energy;
            en->total  = data->EN(front());
            ent->total = data->ENT(front());

            // Setting up the position part 1.
            x->min = front();        x->max = front();
            y->min = front();        y->max = front();
            z->min = front();        z->max = front();
            
            eta->min = front();      eta->max = front();
            phi->min = front();      phi->max = front();
            
            radius->min = front();   radius->max = front();
            
            delr->min = 0;           delr->max = front();

            for(int i = 1; i < size(); i++) // Fix later, turn into a for_each or accumulate or something.
            {
                // Setting up the energy part 2.
                e->total   += data->E(at(i));
                en->total  += data->EN(at(i));
                ent->total += data->ENT(at(i));

                // Setting up the position part 2.
                     if(data->X(x->min) > data->X(at(i))){x->min = at(i);}
                else if(data->X(x->max) < data->X(at(i))){x->max = at(i);}
                     if(data->Y(y->min) > data->Y(at(i))){y->min = at(i);}
                else if(data->Y(y->max) < data->Y(at(i))){y->max = at(i);}
                     if(data->Z(z->min) > data->Z(at(i))){z->min = at(i);}
                else if(data->Z(z->max) < data->Z(at(i))){z->max = at(i);}

                     if(data->Eta(eta->min) > data->Eta(at(i))){eta->min = at(i);}
                else if(data->Eta(eta->max) < data->Eta(at(i))){eta->max = at(i);}
                     if(data->Phi(phi->min) > data->Phi(at(i))){phi->min = at(i);}
                else if(data->Phi(phi->max) < data->Phi(at(i))){phi->max = at(i);}

                     if(data->Radius(radius->min) > data->Radius(at(i))){radius->min = at(i);}
                else if(data->Radius(radius->max) < data->Radius(at(i))){ radius->max = at(i);}

                     if(data->DeltaR(delr->max, Eta, Phi) < data->DeltaR(at(i), Eta, Phi)){delr->max = at(i);}
            }
        }
        
        Int_t size()        {return cluster->size();}
        Int_t at(int i)     {return cluster->at(i);}
        Int_t front()       {return cluster->front();}

        void OOC_Correction(Int_t i) // Adds to the OOC energies based on a single cell.
        {
            e->OOC   += data->E(i);
            et->OOC  += data->ET(i);
            en->OOC  += data->EN(i);
            ent->OOC += data->ENT(i);
        }
        void OOC_Correction(Int_t i, Float_t em, Float_t etm, Float_t enm, Float_t entm) // Adds to the OOC energies based on a single cell and energy ratios.
        {
            e->OOC   += data->E(i)   * (e->total / em);
            et->OOC  += data->ET(i)  * (e->total / etm);
            en->OOC  += data->EN(i)  * (e->total / enm);
            ent->OOC += data->ENT(i) * (e->total / entm);
        }

        Float_t Corrected_e()   {return e->total     + e->OOC;}
        Float_t Corrected_et()  {return et->total    + et->OOC;}
        Float_t Corrected_en()  {return en->total    + en->OOC;}
        Float_t Corrected_ent() {return ent->total   + ent->OOC;}

        void Data_Printout(Data *data)
        {
            std::cout << "Cluster size: "                                << cluster->size()           << endl;
            std::cout << "Cluster total energy: "                        << e->total                  << endl;
            std::cout << "Cluster total transverse energy: "             << et->total                 << endl;
            std::cout << "Cluster total normalized energy: "             << en->total                 << endl;
            std::cout << "Cluster total normalized transverse energy: "  << ent->total                << endl;

            std::cout << "Cluster OOC Energy: "                          << e->OOC                    << endl;
            std::cout << "Cluster transverse OOC Energy: "               << et->OOC                   << endl;
            std::cout << "Cluster normalized OOC Energy: "               << en->OOC                   << endl;
            std::cout << "Cluster normalized transverse OOC Energy: "    << ent->OOC                  << endl;

            std::cout << "Cluster X min: "                               << data->X(x->min)           << endl;
            std::cout << "Cluster X max: "                               << data->X(x->max)           << endl;

            std::cout << "Cluster Y min: "                               << data->Y(y->min)           << endl;
            std::cout << "Cluster Y max: "                               << data->Y(y->max)           << endl;

            std::cout << "Cluster Z min: "                               << data->Z(z->min)           << endl;
            std::cout << "Cluster Z max: "                               << data->Z(z->max)           << endl;

            std::cout << "Cluster Eta min: "                             << data->Eta(eta->min)       << endl;
            std::cout << "Cluster Eta max: "                             << data->Eta(eta->max)       << endl;

            std::cout << "Cluster Phi min: "                             << data->Phi(phi->min)       << endl;
            std::cout << "Cluster Phi max: "                             << data->Phi(phi->max)       << endl;

            std::cout << "Cluster Radius min: "                          << data->Radius(radius->min) << endl;
            std::cout << "Cluster Radius max: "                          << data->Radius(radius->max) << endl;
        }

};

class Filter // Used to filter the cells by pre-set paramaters.
{
    private:
        Data *data; // The Data of the event and detector.
        vector<bool> *Blacklist = new vector<bool>(187650); // True if the cell is already part of a cluster.

    public:
        struct filterTypes // The structure used to save the types of filters used.
        {
            bool        use = false;        // Are we using the variable at all for filtering? Set to false by default.
            bool        use_min = false;    // Are we using the min for filtering?
            bool        use_max = false;    // Are we using the max for filtering?
            bool        use_abs = false;    // Are we taking the absolut value before comparing the values?
            Double_t    min = 0.0;          // The minimum alloed value.
            Double_t    max = 0.0;          // The maximum alloed value.

            Double_t    range = 0.0;        // An additional range we look in around the min/max.

            bool        search = false;     // Are we searching through a set of values? Set to false by default.
            bool        search_min = false; // Are we changing the minimum in the search?
            bool        search_max = false; // Are we changing the maximum in the search?
            Double_t    start = 0.0;        // Where the search starts.
            Double_t    end = 0.0;          // Where the search ends.
            int         resolution;         // How detailed is the search.

            void setupType(Double_t min_v, Double_t max_v){min = min_v; max = max_v;} // Sets up the min and max for the filter type.
            void setupType(bool use_v, bool use_min_v, bool use_max_v, bool use_abs_v, Double_t min_v, Double_t max_v, Double_t range_v) // Sets up the specific passed filter type.
            {
                if(!use_v){throw invalid_argument("False use bool passed to Filter's setupType! This filter will never get used!");}
                if(!use_min_v && !use_max_v){throw invalid_argument("False use_min and use_max bools passed to Filter's setupType! This filter will not do anything!");}
                use      = true;
                use_min  = use_min_v;
                use_max  = use_max_v;
                use_abs  = use_abs_v;
                if(use_min){min = min_v;}
                if(use_max){max = max_v;}
                range = range_v;
            }
            void setupType(bool use_v, bool use_min_v, bool use_max_v, bool use_abs_v, Double_t range_v) // Range only! Sets up the specific passed filter type.
            {
                if(!use_v){throw invalid_argument("False use bool passed to Filter's setupType! This filter will never get used!");}
                if(!use_min_v && !use_max_v){throw invalid_argument("False use_min and use_max bools passed to Filter's setupType! This filter will not do anything!");}
                use      = true;
                use_min  = use_min_v;
                use_max  = use_max_v;
                use_abs  = use_abs_v;
                range    = range_v;
            }

            bool comparer(Float_t b) // Used to compare values from the filterTypes struct to a Float_t
            {
                return (!use || ((!use_min || (!use_abs && (min+range) < b) || (use_abs && (min+range) < abs(b))) && (!use_max || (!use_abs && b < (max+range)) || (use_abs && abs(b) < (max+range)))));
            }
            bool comparer(Float_t b, Float_t e) // Used to compare delta r struct to a Float_t
            {
                return !use || (b < range+((4/3)*atan(pow(M_E, -0.52674*e)))); // Temp!!!
            }

            Double_t mRange() // Returns the range in addition to either the min or max.
            {
                if(search_min){return min+range;}
                return max+range;
            }

            void setupSearch(bool search_v, bool search_min_v, bool search_max_v, Double_t start_v, Double_t end_v, int resolution_v) // Sets up the search for the specific passed filter type.
            {
                if(!search_v){throw invalid_argument("False search bool passed to Filter's setupSearch! This search will never get used!");}
                if(!search_min_v && !search_max_v){throw invalid_argument("False search_min and search_max bools passed to Filter's setupSearch! This filter will not do anything!");}
                search       = true;
                search_min   = search_min_v;
                search_max   = search_max_v;
                start        = start_v;
                end          = end_v;
                resolution   = resolution_v;
            }
            void searchStep(int i) // Sets the range based on the step.
            {
                range = i*(end-start)/(resolution-1);
            }
            void Printout()
            {
                std::cout<<boolalpha;
                std::cout<<"use:        "<<use<<endl;
                std::cout<<"use_min:    "<<use_min<<endl;
                std::cout<<"use_max:    "<<use_max<<endl;
                std::cout<<"min:        "<<min<<endl;
                std::cout<<"max:        "<<max<<endl<<endl;

                std::cout<<"range:      "<<range<<endl<<endl;

                std::cout<<"search:     "<<search<<endl;
                std::cout<<"search_min: "<<search_min<<endl;
                std::cout<<"search_max: "<<search_max<<endl;
                std::cout<<"start:      "<<start<<endl;
                std::cout<<"end:        "<<end<<endl;
                std::cout<<"resolution: "<<resolution<<endl<<endl;
            }
        } 
        *x = new filterTypes(),      *y = new filterTypes(),  *z = new filterTypes(), *radius = new filterTypes(), 
        *e = new filterTypes(),      *et = new filterTypes(), *en = new filterTypes(), *ent = new filterTypes(),
        *eta = new filterTypes(),    *phi = new filterTypes(), *delr = new filterTypes();

        Filter(Data *d) // The Constructor.
        {
            data = d; // The Data object.
        }
        Filter(Filter *f, Data *d) // The Copy Constructor.
        {
            data = d; // The Data object.

            x = new filterTypes(*f->x);
            y = new filterTypes(*f->y);
            z = new filterTypes(*f->z);
            e = new filterTypes(*f->e);
            et = new filterTypes(*f->et);
            en = new filterTypes(*f->en);
            ent = new filterTypes(*f->ent);
            eta = new filterTypes(*f->eta);
            phi = new filterTypes(*f->phi);
            radius = new filterTypes(*f->radius);
            delr = new filterTypes(*f->delr);
        }
        void setupBlacklist(vector<vector<Int_t>> *IDs) // Sets up the Blacklist with the Cluster IDs for each Event.
        {
            if(IDs->empty()){throw invalid_argument("Empty vector passed to Filter's setupBlacklist!");} // Empty Check

            for(Int_t i = 0; i < IDs->size(); i++) // Fix later, turn into a for each.
            {
                for(Int_t j = 0; j < IDs->at(i).size(); j++)
                {
                    Blacklist->at(data->I(IDs->at(i).at(j))) = true;
                }
            }
        }
        void setupCluster(Cluster *cluster) // Sets up the filter with the min and max of a cluster, DOES NOT ENABLE ANY FILTERS!
        {
            x->setupType(     data->X(cluster->x->min),           data->X(cluster->x->max));
            y->setupType(     data->Y(cluster->y->min),           data->Y(cluster->y->max));
            z->setupType(     data->Z(cluster->z->min),           data->Z(cluster->z->max));
            eta->setupType(   data->Eta(cluster->eta->min),       data->Eta(cluster->eta->max));
            phi->setupType(   data->Phi(cluster->phi->min),       data->Phi(cluster->phi->max));
            radius->setupType(data->Radius(cluster->radius->min), data->Radius(cluster->radius->max));
            delr->setupType(  0.0,                                data->DeltaR(cluster->delr->max, cluster->Eta, cluster->Phi));
        }
                
        bool searching(){for(int i = 0; i < size(); i++){if(at(i)->search){return true;}} return false;} // Are we searching at all?

        bool All(Int_t i, Float_t e, Float_t p) // Filters the cell at index i by all filters.
        {
            return Position(i) && Energy(i) && Angle(i, e, p) && BadCell(i) && Blacklisted(i);
        }
        bool Global_fast(Int_t i) // Filters by the 'global' paramaters only using et and en energies.
        {
            return
            (
                en->min+en->range < (data->EN(i)) &&
                et->min+et->range < data->ET(i) &&
                !Blacklist->at(i) &&
                !data->BadCell(i)
            );
        }
        bool Position(Int_t i) // Filters the cell at index i by its position.
        {
            return x->comparer(data->X(i)) && y->comparer(data->Y(i)) && z->comparer(data->Z(i)) && radius->comparer(data->Radius(i));
        }
        bool Energy(Int_t i) // Filters the cell at index i by its energy.
        {
            return e->comparer(data->E(i)) && et->comparer(data->ET(i)) && en->comparer(data->EN(i)) && ent->comparer(data->ENT(i));
        }
        bool Angle(Int_t i, Float_t e, Float_t p) // Filters the cell at index i by its angle.
        {
            return eta->comparer(data->Eta(i)) && phi->comparer(data->Phi(i)) && delr->comparer(data->DeltaR(i, e, p)); // OLD Version!!!
            //return eta->comparer(data->Eta(i)) && phi->comparer(data->Phi(i)) && delr->comparer(data->DeltaR(i, e, p), e); // TEMP!!!
        }
        bool BadCell(Int_t i){return !data->BadCell(i);} // Filters the cell at index i if it's a bad cell.
        bool Blacklisted(Int_t i){return !Blacklist->at(i);} // Filters the cell at index i if it's blacklisted.
        
        int size(){return 11;} // Returns the number of filters.
        filterTypes* at(int i) // Returns the filter at a specific index
        {
            switch(i)
            {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                case 3:
                    return e;
                case 4:
                    return et;
                case 5:
                    return en;
                case 6:
                    return ent;
                case 7:
                    return eta;
                case 8:
                    return phi;
                case 9:
                    return radius;
                case 10:
                    return delr;
                default:
                    throw invalid_argument("Invalid int passed to filterTypes!");
                    return NULL;
            }
        }
        
        void eventCleanup() // Cleans up the Filter for Each Event
        {
            std::fill(Blacklist->begin(), Blacklist->end(), false); // Sets Every Entry in the Blacklist to False.
        }
};

class Jet // Used to find the Jet Guesses and Store the Error of each event for each filter paramater.
{
    private:
        Data *data; // The Data of the event and detector.

        // For the Fast Jet Program. Don't Touch! Gotten from Dr. Heinrich's code.
        double R;           // The Delta R range for the jet program.
        int repetitions;    // 1 for quick jet search.

        struct Jets // Stores the jet info.
        {
            vector<Float_t> *Eta = new vector<Float_t>(); // Stores the eta of the jet(s).
            vector<Float_t> *Phi = new vector<Float_t>(); // Stores the phi of the jet(s).
            vector<Float_t> *Pt  = new vector<Float_t>(); // Stores the pt of the jet(s).
        };
        struct JetEvent // Stores the jet info, filter, and more for each event.
        {
            int eventNumber; // Stores the event number, used for searching and indexing.
            
            Jets          *trueJets = new Jets(); // Stores all the relevant info of the true jet(s).
            Jets          *rawJets  = new Jets(); // Stores all the relevant info of the raw jet(s) guess.
            vector<Jets*> *OOCJets  = new vector<Jets*>(); // Stores all the relevant info of the OOC jet(s) guess.
            
            //vector<fastjet::PseudoJet> *Pjets = new vector<fastjet::PseudoJet>(); // Stores the Pjets info.

            vector<Filter> *filters = new vector<Filter>(); // Stores the filter info.

            Double_t raw_delr_error(int t_i, int r_i) // Returns the delta r distance between the chosen indexes.
            {
                Double_t deta = rawJets->Eta->at(r_i) - trueJets->Eta->at(t_i);
                Double_t dphi = TVector2::Phi_mpi_pi(rawJets->Phi->at(r_i) - trueJets->Phi->at(t_i)); // For phi correction.
                return sqrt(deta*deta + dphi*dphi);
            }
            Double_t raw_pt_error(int t_i, int r_i)
            {
                return abs((trueJets->Pt->at(t_i) - rawJets->Pt->at(r_i))/trueJets->Pt->at(t_i));
            }
            Double_t OOC_delr_error(int t_i, int O_i, int O_j) // Returns the delta r distance between the chosen indexes.
            {
                Double_t deta = OOCJets->at(O_i)->Eta->at(O_j) - trueJets->Eta->at(t_i);
                Double_t dphi = TVector2::Phi_mpi_pi(OOCJets->at(O_i)->Phi->at(O_j) - trueJets->Phi->at(t_i)); // For phi correction.
                return sqrt(deta*deta + dphi*dphi);
            }
            Double_t OOC_pt_error(int t_i, int O_i, int O_j)
            {
                return abs((trueJets->Pt->at(t_i) - OOCJets->at(O_i)->Pt->at(O_j))/trueJets->Pt->at(t_i));
            }
        };

    public:
        vector<JetEvent*> *jetEvent = new vector<JetEvent*>();

        Jet(Data *d) // The Constructor.
        {
            data = d; // The Data object.

            // For the Fast Jet Program. Don't Touch! Gotten from Dr. Heinrich's code.
            R = 0.4;            // The Delta R range for the jet program.
            repetitions = 1;    // A quick jet method is being used here.
        }

        void addJet(vector<Cluster*> *clusters, Filter *filter, int eventN) // Adds an event to the object.
        {
            if(clusters->empty()){throw invalid_argument("No clusters were given to the Jet addCluster!");} // Empty check.

            // For the Fast Jet Program. Don't Touch!
            TLorentzVector temp_p4;                     // A temp TLorentz vector to automate some math. [Unsure]
            std::vector<fastjet::PseudoJet> jet_inputs; // A temp vector to hold each cluster's jet guess. [Unsure]
            fastjet::JetDefinition jet_def;             // Used to set up the jet for pjets. [Unsure]

            // Defining the Fast Jet. Don't Touch! Gotten from Dr. Heinrich's code.
            for(int i = 0; i < clusters->size(); i++) // Adding all the clusters to the jet.
            {
                temp_p4.SetPtEtaPhiM(clusters->at(i)->Corrected_et(), clusters->at(i)->Eta, clusters->at(i)->Phi, 0.0); // Used to get the momentum. [Unsure]
                jet_inputs.push_back(fastjet::PseudoJet(temp_p4.Px(), temp_p4.Py(), temp_p4.Pz(), temp_p4.E()));      // Used to organize the jets. [Unsure]
            }
            jet_def = fastjet::JetDefinition(fastjet::antikt_algorithm, R, fastjet::E_scheme, fastjet::Best); // Defined the jet for the event. [Unsure]
            fastjet::AreaDefinition area_def(fastjet::AreaType::active_area,fastjet::GhostedAreaSpec(5.0, repetitions, 0.01, 1.0, 0.1, 1e-100)); // IDK. [Unsure]
            fastjet::ClusterSequenceArea clust_seq = fastjet::ClusterSequenceArea(jet_inputs, jet_def, area_def); // IDK. [Unsure]
            std::vector<fastjet::PseudoJet> pjets = fastjet::sorted_by_pt(clust_seq.inclusive_jets(0.0));

            // Saving the event.
            if(jetEvent->empty() || jetEvent->back()->eventNumber != eventN)
            {
                jetEvent->push_back(new JetEvent); // Makes a new JetEvent struct to store the new event.

                /*
                Float_t max_eta_TruthJet = *std::max_element
                (
                    data->AntiKt4TruthJets_eta()->begin(), data->AntiKt4TruthJets_eta()->end(),[](Float_t a, Float_t b)
                    {
                        return std::abs(a) < std::abs(b);
                    }
                );
                if(5 < max_eta_TruthJet) // Big Eta check.
                {
                    std::cout<<"Event "<<eventN<<"'s Eta is too big!"<<endl;
                    jetEvent->back()->badEvent = true;
                    badEvents++;
                }
                else if(data->AntiKt4TruthJets_eta()->empty() || data->AntiKt4TruthJets_phi()->empty() || data->AntiKt4TruthJets_pt()->empty()) // Empty Truth Jet Check.
                {
                    std::cout<<"Event "<<eventN<<"'s Truth Jet is empty!"<<endl;
                    //std::cout<<boolalpha;
                    //std::cout<<"Eta empty? "<<data->AntiKt4TruthJets_eta()->empty()<<endl;
                    //std::cout<<"Phi empty? "<<data->AntiKt4TruthJets_phi()->empty()<<endl;
                    //std::cout<<"Pt empty? "<<data->AntiKt4TruthJets_pt()->empty()<<endl;
                    jetEvent->back()->badEvent = true;
                    badEvents++;
                }*/

                jetEvent->back()->eventNumber = eventN; // Saves the event number.

                jetEvent->back()->trueJets->Eta = new vector<Float_t>(*data->AntiKt4TruthJets_eta()); // Saves the eta truth jet(s) for this event.
                jetEvent->back()->trueJets->Phi = new vector<Float_t>(*data->AntiKt4TruthJets_phi()); // Saves the phi truth jet(s) for this event.
                jetEvent->back()->trueJets->Pt  = new vector<Float_t>(*data->AntiKt4TruthJets_pt());  // Saves the pt truth jet(s) for this event.

                for(int i = 0; i < pjets.size(); i++) // Saving the 'raw' unmodified guesses.
                {
                    jetEvent->back()->rawJets->Eta->push_back(pjets.at(i).eta());
                    jetEvent->back()->rawJets->Phi->push_back(pjets.at(i).phi());
                    jetEvent->back()->rawJets->Pt->push_back(pjets.at(i).pt());
                }
            }
            else
            {
                Filter tempFilter(filter, data); // A temp non-pointer variable to unlink the data.
                jetEvent->back()->filters->push_back(tempFilter); // Saves the filter for this event.

                jetEvent->back()->OOCJets->push_back(new Jets);

                for(int i = 0; i < pjets.size(); i++) // Saving the 'raw' unmodified guesses.
                {
                    jetEvent->back()->OOCJets->back()->Eta->push_back(pjets.at(i).eta());
                    jetEvent->back()->OOCJets->back()->Phi->push_back(pjets.at(i).phi());
                    jetEvent->back()->OOCJets->back()->Pt->push_back(pjets.at(i).pt());
                }
            }        

            temp_p4.Clear();
            jet_inputs.clear();
            pjets.clear();
        }

        int size(){return jetEvent->size();}
        JetEvent* at(int i){return jetEvent->at(i);}
        JetEvent* front(){return jetEvent->front();}
        JetEvent* back(){return jetEvent->back();}

        Double_t raw_max_delr()
        {
            Double_t max = -1;
            int index_max = -1;
            for(int i = 0; i < size(); i++)
            {
                if(max < at(i)->raw_delr_error(0, 0))
                {
                    max = at(i)->raw_delr_error(0, 0);
                    index_max = i;
                }
            }
            std::cout<<"The event with the max Delta R is: "<<index_max<<endl;
            return max;
        }
        Double_t OOC_max_delr(int d)
        {
            Double_t max = -1;
            int debth = -1;
            int index_max = -1;
            for(int i = 0; i < size(); i++)
            {
                if(max < at(i)->OOC_delr_error(0, d, 0))
                {
                    max = at(i)->OOC_delr_error(0, d, 0);
                    debth = d;
                    index_max = at(i)->eventNumber;
                }
            }
            std::cout<<"The event with the max Delta R is: "<<index_max<<endl;
            std::cout<<"The debth is: "<<debth<<endl;
            return max;
        }

        Double_t raw_mean_delr()
        {
            Double_t mean = 0.0;
            for(int i = 0; i < size(); i++)
            {
                mean += at(i)->raw_delr_error(0, 0);
            }
            return mean/size();
        }
        Double_t raw_mean_pt()
        {
            Double_t mean = 0.0;
            for(int i = 0; i < size(); i++)
            {
                mean += at(i)->raw_pt_error(0, 0);
            }
            return mean/size();
        }

        Double_t OOC_mean_delr(int d)
        {
            Double_t mean = 0.0;
            for(int i = 0; i < size(); i++)
            {
                mean += at(i)->OOC_delr_error(0, d, 0);
            }
            return mean/size();
        }
        Double_t OOC_SD_delr(int d, Double_t mean)
        {
            Double_t SD = 0.0;
            for(int i = 0; i < size(); i++)
            {
                SD += (at(i)->OOC_delr_error(0, d, 0) - mean) * (at(i)->OOC_delr_error(0, d, 0) - mean);
            }
            return std::sqrt(SD/size());
        }
        Double_t OOC_mean_pt(int d)
        {
            Double_t mean = 0.0;
            for(int i = 0; i < size(); i++)
            {
                mean += at(i)->OOC_pt_error(0, d, 0);
            }
            return mean/size();
        }
        Double_t OOC_SD_pt(int d, Double_t mean)
        {
            Double_t SD = 0.0;
            for(int i = 0; i < size(); i++)
            {
                SD += (at(i)->OOC_pt_error(0, d, 0) - mean) * (at(i)->OOC_pt_error(0, d, 0) - mean);
            }
            return std::sqrt(SD/size());
        }

};

class Toolkit
{
    /* Assumptions made by the program:
        All clusters with a et of less than 0 are ignored, they are not used in the OOC energy correction, or Jet Finding.
    */
    /* ToDo
        Fix all the "Fix Later" parts of the code.
        Get the phi filter and system to work correctly.
    */
    private:
        Data             *data;                               // The Data of the event and detector.
        int               eventNumber;                        // The current event number.
        Filter           *filter;                             // The Object used to Filter OOC Cells.
        //Jet              *raw_jet;                            // The Object that stores the raw cluster Jet info and error for all events.
        Jet              *OOC_jet;                            // The Object that stores the jets info for each event.
        vector<Cluster*> *clusters  = new vector<Cluster*>(); // The set of clusters from the event.
        
        vector<Int_t>        *Whitelist        = new vector<Int_t>();        // Indexes of the cells that pass the most generous global filters.
        vector<Int_t>        *OOC_Cells        = new vector<Int_t>();        // Indexes of the cells that pass the position filters and have associated clusters.
        vector<vector<int>*> *assignedClusters = new vector<vector<int>*>(); // Holds the clusters each OOC cell is assigned to.

    public:
        Toolkit(cluster_Data_Object *d_var, CaloCellsMap *cd_var) // The Constructor.
        {
            data = new Data(d_var, cd_var); // Sets up the data object.

            filter = new Filter(data); // Sets up the filter object.
            
            OOC_jet = new Jet(data); // Sets up the Jet object.
        }

        bool setupEvent(cluster_Data_Object *d_var, vector<vector<Int_t>> *IDs, vector<Float_t> *et, vector<Float_t> *eta, vector<Float_t> *phi, int eventN) // Gives the Toolkit the relevant data of each Event.
        {
            data->updateEvent(d_var); // Updates the Data with the new event's info.
            eventNumber = eventN;

            if(badEvent()){return true;} // Exits early if we have a bad event.

            for(int i = 0; i < IDs->size(); i++) // Sets up the clusters vector. Fix later, turn into a for each.
            {
                if(et->at(i) <= 0){continue;} // Skips any cluster with a total transverse energy of less than 0. Fix later, might be better to put everythin inside the if statement for the compiler.
                vector<Int_t> *indices = new vector<Int_t>(); // A temp vector to save the cluster cells indices.
                for(int j = 0; j < IDs->at(i).size(); j++){indices->push_back(data->I(IDs->at(i).at(j)));} // Fix later, turn into a for each.
                clusters->push_back(new Cluster(indices, et->at(i), eta->at(i), phi->at(i), data)); // Saves the new cluster.
            }
            if(clusters->empty()){throw invalid_argument("No clusters were saved! The program can not run!");} // Empty check.
            
            OOC_jet->addJet(clusters, filter, eventNumber); // Creates the raw jet info for the event.
            return false;
        }
        bool badEvent() // Checks to see if the event is 'bad' if so it skips it.
        {
            if(data->AntiKt4TruthJets_eta()->empty() || data->AntiKt4TruthJets_phi()->empty() || data->AntiKt4TruthJets_pt()->empty()) // Empty Truth Jet Check.
            {
                std::cout<<"Event "<<eventNumber<<"'s Truth Jet is empty!"<<endl;
                return true; // If the truth Jets are empty we have a bad event.
            }
            Float_t max_eta_TruthJet = *std::max_element(data->AntiKt4TruthJets_eta()->begin(), data->AntiKt4TruthJets_eta()->end(),[](Float_t a, Float_t b)
            {
                return std::abs(a) < std::abs(b);
            });
            if(5 < max_eta_TruthJet) // Big Eta check.
            {
                std::cout<<"Event "<<eventNumber<<"'s Eta is too big!"<<endl;
                return true; // If the |Eta| > 5 the jet has left the detector and we have a bad event.
            }
            
            return false;
        }
        void setupBlacklist(vector<vector<Int_t>> *IDs){filter->setupBlacklist(IDs);} // Passes the IDs to the Filter to Setup the Blacklist
        void setupFilter() // Sets up the filter paramaters for the event.
        {
            filter->et->setupType(true, true,  false, false, 0.0, 0.0, 0.0); // Sets up the filters with the most generous paramaters if we are searching.
            filter->en->setupType(true, true,  false, true, 1.0, 0.0, 0.0);
            filter->delr->setupType(true, false, true,  false, 0.3);

            filter->en->setupSearch(true, true, false, 0.0, 3.0, 10); // These are a range in addition to the min/max set up.
            filter->delr->setupSearch(true, false, true, 0.0, 0.3, 10);
        }
        
        void runGlobalFilter_fast() // Creates the vector of cells that pass the most generous global filters.
        {
            for(Int_t i = 0; i < 187650; i++) // Searching through all cells, if it passes all filters we save it.
            {
                if(filter->Global_fast(i)){Whitelist->push_back(i);}
            }
        }
        void runPositionFilter()
        {
            for(int i = 0; i < Whitelist->size(); i++)
            {
                for(int j = 0; j < clusters->size(); j++)
                {
                    filter->setupCluster(clusters->at(j));
                    if(filter->Angle(Whitelist->at(i), clusters->at(j)->Eta, clusters->at(j)->Phi))
                    {
                        OOC_Cells->push_back(Whitelist->at(i));
                        assignedClusters->push_back(new vector<int>());
                        break;
                    }
                }
            }
        }
        void assignOOCCells()
        {
            struct OOCcells
            {
                void reset(){e = 0; et = 0; en = 0; ent = 0;}
                Float_t e = 0, et = 0, en = 0, ent = 0;
            } *OOC_cells_info = new OOCcells();

            for(int i = 0; i < OOC_Cells->size(); i++)
            {
                for(int j = 0; j < clusters->size(); j++)
                {
                    filter->setupCluster(clusters->at(j));
                    if(filter->Angle(OOC_Cells->at(i), clusters->at(j)->Eta, clusters->at(j)->Phi))
                    {
                        assignedClusters->at(i)->push_back(j);
                        
                        OOC_cells_info->e   += clusters->at(j)->e->total;
                        OOC_cells_info->et  += clusters->at(j)->et->total;
                        OOC_cells_info->en  += clusters->at(j)->en->total;
                        OOC_cells_info->ent += clusters->at(j)->ent->total;
                    }
                }

                for(int j = 0; j < assignedClusters->at(i)->size(); j++)
                {
                    clusters->at(assignedClusters->at(i)->at(j))->OOC_Correction(OOC_Cells->at(i), OOC_cells_info->e, OOC_cells_info->et, OOC_cells_info->en, OOC_cells_info->ent);
                }
                OOC_cells_info->reset(); // Resets the energies for the next cell.
            }
        }
        
        void runSearch()
        {
            if(!filter->searching()){return;} // Skips the filter search if we arn't searching with any filter.
            int resolution = 1; // Holds the total number of searches we will be doing. This number can get big quick!
            for(int i = 0; i < filter->size(); i++){if(filter->at(i)->search){resolution *= filter->at(i)->resolution;}}

            int divisor = 1; // Used to sequence all the filters.
            for(int i = 1; i < resolution; i++) // This runs the search, filters should be run in order of efficiency.
            {
                for(int j = 0; j < filter->size(); j++)
                {
                    if(filter->at(j)->search)
                    {
                        filter->at(j)->searchStep((i/divisor)%(filter->at(j)->resolution));
                        divisor *= filter->en->resolution;
                    }
                }
                divisor = 1;

                runSearchFilter(); // Runs the search on the new paramaters.

                createOOCJet(); // Creates the jet and cleans up the energy for the next filter change.
            }
        }
        void runSearchFilter()
        {
            vector<Int_t> *whitelistSearch = new vector<Int_t>();
            vector<Int_t> *OOC_CellsSearch = new vector<Int_t>();

            vector<vector<int>*> *assignedClustersWhitelistSearch = new vector<vector<int>*>(); // Temp for holding cluster assignment.
            vector<vector<int>*> *assignedClustersOOC_CellsSearch = new vector<vector<int>*>(); // Temp for holding cluster assignment.

            vector<vector<int>*> *assignedClustersSearch = new vector<vector<int>*>();

            struct OOCcells
            {
                void reset(){e = 0; et = 0; en = 0; ent = 0;}
                Float_t e = 0, et = 0, en = 0, ent = 0;
            } *OOC_cells_info = new OOCcells();

            for(int i = 0; i < OOC_Cells->size(); i++) // Fix later, turn into a for_each or transform.
            {
                if(filter->Global_fast(OOC_Cells->at(i)))
                {
                    whitelistSearch->push_back(OOC_Cells->at(i));
                    assignedClustersWhitelistSearch->push_back(assignedClusters->at(i));
                }
            }
            if(whitelistSearch->empty()){return;} // Empty check.
            for(int i = 0; i < whitelistSearch->size(); i++) // Fix later, turn into a for_each or transform.
            {
                for(int j = 0; j < assignedClustersWhitelistSearch->at(i)->size(); j++) // Fix later, turn into a for_each or transform.
                {
                    filter->setupCluster(clusters->at(assignedClustersWhitelistSearch->at(i)->at(j)));
                    if(filter->Angle(whitelistSearch->at(i), clusters->at(assignedClustersWhitelistSearch->at(i)->at(j))->Eta, clusters->at(assignedClustersWhitelistSearch->at(i)->at(j))->Phi))
                    {
                        OOC_CellsSearch->push_back(whitelistSearch->at(i));
                        assignedClustersOOC_CellsSearch->push_back(assignedClustersWhitelistSearch->at(i));
                        assignedClustersSearch->push_back(new vector<int>());
                        break;
                    }
                }
            }
            if(OOC_CellsSearch->empty()){return;} // Empty check.
            for(int i = 0; i < OOC_CellsSearch->size(); i++)
            {
                for(int j = 0; j < assignedClustersOOC_CellsSearch->at(i)->size(); j++)
                {
                    filter->setupCluster(clusters->at(assignedClustersOOC_CellsSearch->at(i)->at(j)));
                    if(filter->Angle(OOC_CellsSearch->at(i), clusters->at(assignedClustersOOC_CellsSearch->at(i)->at(j))->Eta, clusters->at(assignedClustersOOC_CellsSearch->at(i)->at(j))->Phi))
                    {
                        assignedClustersSearch->at(i)->push_back(assignedClustersOOC_CellsSearch->at(i)->at(j));

                        OOC_cells_info->e   += clusters->at(assignedClustersOOC_CellsSearch->at(i)->at(j))->e->total;
                        OOC_cells_info->et  += clusters->at(assignedClustersOOC_CellsSearch->at(i)->at(j))->et->total;
                        OOC_cells_info->en  += clusters->at(assignedClustersOOC_CellsSearch->at(i)->at(j))->en->total;
                        OOC_cells_info->ent += clusters->at(assignedClustersOOC_CellsSearch->at(i)->at(j))->ent->total;
                    }
                }

                for(int j = 0; j < assignedClustersSearch->at(i)->size(); j++)
                {
                    clusters->at(assignedClustersSearch->at(i)->at(j))->OOC_Correction(OOC_CellsSearch->at(i), OOC_cells_info->e, OOC_cells_info->et, OOC_cells_info->en, OOC_cells_info->ent);
                }
                OOC_cells_info->reset(); // Resets the energies for the next cell.
            }
        }
        
        void createOOCJet()
        {
            OOC_jet->addJet(clusters, filter, eventNumber); // Creates a jet with the corrected clusters.
            assignOOCCleanup(); // Cleans up the cluster OOC energy between filter searches.
        }

        void Printout()
        {
            std::cout<<endl<<"Jet Vector Size: "<<OOC_jet->size()<<endl;
            std::cout<<"Raw Errors:"<<endl;
            std::cout<<"Delta R: "<<OOC_jet->raw_mean_delr()<<" PT: "<<OOC_jet->raw_mean_pt()<<endl;
        }
        void Display()
        {
            vector<Double_t> *X = new vector<Double_t>();
            vector<Double_t> *Y = new vector<Double_t>();
            vector<Double_t> *Z_delr = new vector<Double_t>();
            vector<Double_t> *Z_SD_delr = new vector<Double_t>();
            vector<Double_t> *Z_pt = new vector<Double_t>();
            vector<Double_t> *Z_SD_pt = new vector<Double_t>();

            for(int i = 0; i < OOC_jet->front()->OOCJets->size(); i++)
            {
                X->push_back(OOC_jet->front()->filters->at(i).delr->range);
                Y->push_back(OOC_jet->front()->filters->at(i).en->mRange());
                Z_delr->push_back(OOC_jet->OOC_mean_delr(i));
                Z_pt->push_back(OOC_jet->OOC_mean_pt(i));
            }
            for(int i = 0; i < OOC_jet->front()->OOCJets->size(); i++)
            {
                Z_SD_delr->push_back(OOC_jet->OOC_SD_delr(i, Z_delr->at(i)));
                Z_SD_pt->push_back(OOC_jet->OOC_SD_pt(i, Z_pt->at(i)));
            }
            Graph_2D(X, Y, Z_delr, "Delta R Distance");
            Graph_2D(X, Y, Z_SD_delr, "Delta R SD");
            Graph_2D(X, Y, Z_pt, "PT Error");
            Graph_2D(X, Y, Z_SD_pt, "PT SD");

            full_Display_3D();
        }
        void double_DeltaR_Histogram_Display()
        {
            TCanvas *canvas = new TCanvas("canvas Delta R","Delta Rs Display",600,400);

            int nBins = 50; // How many bins to have in the histogram.
            Float_t Max = 10; // Holds the max element of the vector.
            
            TH1F *hist_rawDR = new TH1F("Delta R Error", "Delta R Error", nBins, 0, Max); // The raw Delta R Error Display.
            TH1F *hist_OOCDR = new TH1F("Delta R Error 1", "Delta R Error 1", nBins, 0, Max); // The OOC corrected Delta R Error Display.

            for(int i = 0; i < OOC_jet->size(); i++)
            {
                hist_rawDR->Fill(OOC_jet->at(i)->raw_delr_error(0,0));
            }
            for(int i = 0; i < OOC_jet->size(); i++)
            {
                for(int j = 0; j < OOC_jet->at(i)->OOCJets->size(); j++)
                {
                    hist_OOCDR->Fill(OOC_jet->at(i)->OOC_delr_error(0,j,0));
                }
            }

            hist_rawDR->Draw(); // Draws the first histogram.
            canvas->Update();

            Float_t rightmax = 1.1*hist_OOCDR->GetMaximum(); // Sets the right scale to match the corrected delta r values and draws the second histogram.
            Float_t scale    = gPad->GetUymax()/rightmax;
            hist_OOCDR->SetLineColor(kRed);
            hist_OOCDR->Scale(scale);
            hist_OOCDR->Draw("same"); // Draws the second histogram to the same canvas.
            TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(),gPad->GetUymax(),0,rightmax,510,"+L");
            axis->SetLineColor(kRed);
            axis->SetLabelColor(kRed);
            axis->Draw();
        }
        void full_Display_3D()
        {
            // Displays the Origin, Clusters, Filtered Clusters, Whitelist, Jet Guess, and True Jet
            // Add filter cone/range to this later as well. To-Do
            auto canvas = new TCanvas("3D Display", "3D Display", 600, 600);

            // ------------------------------------------------Color: \/
            TPad *pad = new TPad("pad", "pad", 0.05, 0.02, 0.95, 0.82, 1, 3, 1);
            pad->Draw();
            pad->cd();

            // Sets up the min and max of all elements to display.
            Data *d = data;
            Float_t min_x = data->X((*std::min_element(clusters->cbegin(),clusters->cend(),[&d](Cluster*a,Cluster*b){return d->X(a->x->min)<d->X(b->x->min);}))->x->min);
            Float_t max_x = data->X((*std::max_element(clusters->cbegin(),clusters->cend(),[&d](Cluster*a,Cluster*b){return d->X(a->x->max)<d->X(b->x->max);}))->x->max);
            Float_t min_y = data->Y((*std::min_element(clusters->cbegin(),clusters->cend(),[&d](Cluster*a,Cluster*b){return d->Y(a->y->min)<d->Y(b->y->min);}))->y->min);
            Float_t max_y = data->Y((*std::max_element(clusters->cbegin(),clusters->cend(),[&d](Cluster*a,Cluster*b){return d->Y(a->y->max)<d->Y(b->y->max);}))->y->max);
            Float_t min_z = data->Z((*std::min_element(clusters->cbegin(),clusters->cend(),[&d](Cluster*a,Cluster*b){return d->Z(a->z->min)<d->Z(b->z->min);}))->z->min);
            Float_t max_z = data->Z((*std::max_element(clusters->cbegin(),clusters->cend(),[&d](Cluster*a,Cluster*b){return d->Z(a->z->max)<d->Z(b->z->max);}))->z->max);

            Float_t max_radius = data->Radius((*std::max_element(clusters->cbegin(),clusters->cend(),[&d](Cluster*a,Cluster*b){return d->Radius(a->radius->max)<d->Radius(b->radius->max);}))->radius->max);

            TView *view = TView::CreateView(1);
            view->SetRange(min_x, min_y, min_z, max_x, max_y, max_z);

            // Sets up the clusters to be displayed
            TPolyMarker3D *origin_3D_Poly = new TPolyMarker3D(1);
            origin_3D_Poly->SetPoint(0, 0, 0, 0);
            origin_3D_Poly->SetMarkerSize(4);
            origin_3D_Poly->SetMarkerColor(0);
            origin_3D_Poly->SetMarkerStyle(1);

            TPolyMarker3D *cluster_3D_Poly = Poly_3d_Maker(clusters);
            cluster_3D_Poly->SetMarkerSize(1);
            cluster_3D_Poly->SetMarkerColor(2);
            cluster_3D_Poly->SetMarkerStyle(2);

            TPolyMarker3D *whitelist_3D_Poly = Poly_3d_Maker(Whitelist);
            whitelist_3D_Poly->SetMarkerSize(1);
            whitelist_3D_Poly->SetMarkerColor(5);
            whitelist_3D_Poly->SetMarkerStyle(5);

            TPolyMarker3D *OOC_Cells_3D_Poly = Poly_3d_Maker(OOC_Cells);
            OOC_Cells_3D_Poly->SetMarkerSize(1);
            OOC_Cells_3D_Poly->SetMarkerColor(4);
            OOC_Cells_3D_Poly->SetMarkerStyle(3);

            TPolyMarker3D *cluster_guess_3D_Poly = Poly_3d_Maker(clusters->at(0)->Eta, clusters->at(0)->Phi, max_radius);
            cluster_guess_3D_Poly->SetMarkerSize(1);
            cluster_guess_3D_Poly->SetMarkerColor(4);
            cluster_guess_3D_Poly->SetMarkerStyle(4);

            TPolyMarker3D *raw_guess_3D_Poly = Poly_3d_Maker(OOC_jet->back()->rawJets->Eta->front() , OOC_jet->back()->rawJets->Phi->front(), max_radius);
            raw_guess_3D_Poly->SetMarkerSize(1);
            raw_guess_3D_Poly->SetMarkerColor(2);
            raw_guess_3D_Poly->SetMarkerStyle(2);

            TPolyMarker3D *OOC_guess_3D_Poly = Poly_3d_Maker(OOC_jet->back()->OOCJets->at(0)->Eta->front() , OOC_jet->back()->OOCJets->at(0)->Phi->front(), max_radius);
            OOC_guess_3D_Poly->SetMarkerSize(1);
            OOC_guess_3D_Poly->SetMarkerColor(4);
            OOC_guess_3D_Poly->SetMarkerStyle(3);

            TPolyMarker3D *trueJet_3D_Poly = Poly_3d_Maker(data->AntiKt4TruthJets_eta()->at(0), data->AntiKt4TruthJets_phi()->at(0), max_radius);
            trueJet_3D_Poly->SetMarkerSize(1);
            trueJet_3D_Poly->SetMarkerColor(6);
            trueJet_3D_Poly->SetMarkerStyle(6);

            // Drawing it to the Screen.
            origin_3D_Poly->Draw();
            cluster_3D_Poly->Draw();
            //whitelist_3D_Poly->Draw();
            OOC_Cells_3D_Poly->Draw();

            OOC_guess_3D_Poly->Draw();
            trueJet_3D_Poly->Draw();
            trueJet_3D_Poly->Draw();
            
            canvas->cd();

            TPaveText *title = new TPaveText(0.1, 0.85, 0.9, 0.97);
            title->SetFillColor(24);
            title->AddText("Cluster 3D Display");
            title->Draw();
        }
        void Graph_2D(vector<Double_t> *X, vector<Double_t> *Y, vector<Double_t> *Z, const char *name )
        {
            TCanvas *canvas = new TCanvas(name, name, 0, 0, 700, 600);

            TGraph2D *graph = new TGraph2D();
            graph->SetTitle("Display;Delta R Range;Minimum EN;Error");

            for(int i = 0; i < X->size(); i++)
            {
                graph->SetPoint( i, X->at(i), Y->at(i), Z->at(i) );
            }
            graph->Draw("tril p0");
        }
        TPolyMarker3D *Poly_3d_Maker(Float_t eta, Float_t phi, Float_t radius)
        {
            Float_t theta = 2 * atan( exp( eta ) );
            Float_t x = sin(theta) * cos(phi);
            Float_t y = sin(theta) * sin(phi);
            Float_t z = -cos(theta);

            TPolyMarker3D *temp_Poly = new TPolyMarker3D;
            for(Int_t i = 0; i < 100; i++)
            {
                temp_Poly->SetPoint(i, (radius*i/100)*x, (radius*i/100)*y, (radius*i/100)*z);
            }
            return temp_Poly;
        }
        TPolyMarker3D *Poly_3d_Maker(vector<Cluster*> *clust)
        {
            Int_t counter = 0;
            TPolyMarker3D *temp_Poly = new TPolyMarker3D;
            for(Int_t i = 0; i < clust->size(); i++)
            {
                for(Int_t j = 0; j < clust->at(i)->size(); j++)
                {
                    temp_Poly->SetPoint(counter, data->X(clust->at(i)->at(j)), data->Y(clust->at(i)->at(j)), data->Z(clust->at(i)->at(j)));
                    counter++;
                }
            }
            return temp_Poly;
        }
        TPolyMarker3D *Poly_3d_Maker(vector<Int_t> *cells)
        {
            TPolyMarker3D *temp_Poly = new TPolyMarker3D;
            for(Int_t i = 0; i < cells->size(); i++)
            {
                temp_Poly->SetPoint(i, data->X(cells->at(i)), data->Y(cells->at(i)), data->Z(cells->at(i)));
            }
            return temp_Poly;
        }

        void assignOOCCleanup() // Cleans up the cluster OOC energy between filter searches.
        {
            for(int i = 0; i < clusters->size(); i++) // Fix later. Change to a for_each or transform?
            {
                clusters->at(i)->e->OOC   = 0;
                clusters->at(i)->et->OOC  = 0;
                clusters->at(i)->en->OOC  = 0;
                clusters->at(i)->ent->OOC = 0;
            }
        }
        void eventCleanup() // Deletes and Cleans the Memory After Every Event.
        {
            filter->eventCleanup(); // Cleans up the Filter object after every event.
            clusters->clear();      // Cleans up the clusters vector.
            Whitelist->clear();     // Cleans up the whitelist.
            OOC_Cells->clear();     // Cleans up the OOC cells.
            assignedClusters->clear();
        }

};

#endif