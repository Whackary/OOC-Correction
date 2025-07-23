READ ME

~Purpose~
This program's purpose is to use Out Of Cluster (OOC) corrections to create better Jet Guesses when compared to a standard clustering algorithm.

~How To Run~
The program is run through the Object_Handler.C file.
Simply run `root -l Object_Handler.C` in the terminal.

~Requirements~
You must have FastJet installed.
 - https://fastjet.fr/
This program uses Dr. Heinrich's topo_cluster.h and jet_finder.h files. Please contact him for more information.

~Other Info~
The program takes abundant use of pointers and stores very little data locally.
 - All cells are stored as their index number in the 187650-element long list of cells.

~Runtime Steps~
The Object Handler is the master program and instructs the Toolkit on what to do. For more detailed information on any of the below functions, please read the code's comments.
 1. Reads the files and sets up the objects.
 2. The 'i' for loop runs over all files set up in the fileNames vector.
	 - As a note, if the program runs over too many files, it crashes. See ~WARNINGS!~ below for more information.
 3. The 'j' for loop runs through all the events in each file.

The Object Handler loads the data from the cluster_Data_Object.h and CaloCellsMap.h files at the addresses set in the fileNames vector.

The main code is run within the j for loop located in the Object Handler.

It first updates the entry with the new event data.
	It saves all the clusters with a total transverse energy greater than 0 to local memory
	It sets up the event and checks if it is a 'bad' event.
		Bad events are ones that have an empty truth jet, a truth jet with an eta value greater than 5 or less than -5, or no clusters with a total transverse energy greater than 0.
		The program will alert you if one of these occurs.
		These will be skipped, and not included in the final data. If all events were bad events then the program won't have any data to display and nothing will happen at the end.
	
Next, it sets up the blacklist of all cells that are already in a cluster to avoid double counting.

Next, the program sets up the filter.
	To modify this filter, you will need to open the toolkit file for now and manually edit it.
	
The filter runs in 3 parts to play nice with the c++ compiler.
All cells are run through the 'global filter' first.
	This filter checks the energy of the cell, if the cell is blacklisted, and if the cell is a bad cell.
	Any cells that pass all these filters are saved to the whitelist vector
Next is the position filter.
	This filter checks the cell to see if it is within the range of at least one cluster.
	Any cells that pass this list are saved to the OOC_Cells vector.
Lastly, it assigns all the cells that passed to their clusters and gives the appropriate energies.

Next, with the new OOC energies applied to the clusters, a new jet is made.

If you are searching through multiple filter parameters, then it will take the OOC_Cells vector of cells and run the different filter parameters on them.
	As such, it is very important that your first set of filters is the most generous!
	
Lastly, the results are displayed in the form of a 3d graph for both the Delta R distance and standard deviation from the truth jet to the OOC guess jet and the Transverse Momentum error and standard deviation between the OOC guess jet and the truth jet.


~WARNINGS!~
Running this with a very low or 0 minimum energy will cause the program to be very slow. It is suggested that if you want to test a filter range from 0 min en and up, you do it in chunks. As an example, if you wanted to do 0-4 min en, you should do 1-4 min en and then 0-1 min en.

Sometimes the program just stops. I have no idea why, there are no errors, ROOT just quits and returns to the default command line. This typically only happens if the program is running several data sets at once. As such I recommend running them one by one.

~To Do~
 - Much of the code needs to be migrated over to a for_each and transform to take advantage of vectorization.
 - The filter searching code should be turned into a 'recursive' loop so that searches can run faster and more efficiently.
	 - Right now, the code runs on the first OOC_Cells vector over and over, no matter its filter. Implementing a way to either trim the vector of cells that can no longer pass will speed up the process and allow for larger search ranges.
 	 - On this note, if trimming the vector is the best solution, then it may be wise to move away from vectors as they are slow when it comes to deleting elements.
