READ ME

## Purpose
<p>This program's purpose is to use Out Of Cluster (OOC) corrections to create better Jet Guesses when compared to a standard clustering algorithm.</p>

## How To Run
<p>The program is run through the Object_Handler.C file.<br>
Simply run the following in the terminal.</p>

> <p>root -l Object_Handler.C</p>

## Requirements

<p>You must have FastJet installed.<br>
 - https://fastjet.fr/

This program uses Dr. Heinrich's topo_cluster.h and jet_finder.h files. Please contact him for more information.</p>

---

## Other Info

The program takes abundant use of pointers and stores very little data locally.
 - All cells are stored as their index number in the 187650-element long list of cells.

## Runtime Steps
<p>The Object Handler is the master program and instructs the Toolkit on what to do. For more detailed information on any of the below functions, please read the code's comments.</p>
<ol>
	<li>Reads the files and sets up the objects.</li>
	<li>The 'i' for loop runs over all files set up in the fileNames vector.</li>
	<ol>
		<li>As a note, if the program runs over too many files, it crashes. See -WARNINGS!- below for more information.</li>
	</ol>
	<li>The 'j' for loop runs through all the events in each file.</li>
	<ol>
		<li>For every entry, it first updates the data with that entry's data.</li>
		<li>Next, it sets up the event and checks if it is a 'bad' event. All 'bad' events are skipped.</li>
		<ol>
			<li>'Bad' events are those that:</li>
			<ol>
				<li>Have no truth jet.</li>
				<li>Have no cluster with a total transverse energy of greater than 0.</li>
				<li>Have an eta with an absolute value greater than 5.</li>
			</ol>
			<li>The 'raw' jet guess is created here as well, with the standard clusters.</li>
		</ol>
		<li>The blacklist containing all the cells already in a cluster is created for this event.</li>
		<li>The filter for the event is set up.</li>
		<ol>
			<li>To edit the filter, you must manually edit it in the Toolkit.h file.</li>
		</ol>
		<li>The Filter system is run in three steps on all cells.</li>
		<ol>
			<li>This is to play nice with the C++ compiler as doing it all in one loop causes the program to become incredibly slow.</li>
			<li>The First filter is the 'global filter' that filters by the energy of the cell and if the cell is blacklisted or a bad cell.</li>
			<li>The Second filter checks if the cell is within the range of any cluster.</li>
			<li>The Third filter assigns the cells to their cluster(s) and then updates the clusters with their OOC energies.</li>
		</ol>
		<li>If any filter parameters are set with search = true, the cells are filtered again with all combinations of each filter parameter.</li>
		<ol>
			<li>The filters run from most generous to least generous. If you are starting a search from 0 to 4 EN, your first filter must be 0. This is because all searches are run on the cells that passed the first set of filters to save time and make the program run faster.</li>
		</ol>
		<li>The data from all this is saved in the Jet object.</li>
		<li>The remaining data of the event is cleaned in preparation for the next event.</li>
	</ol>
	<li>Once it has reached the end of all events and files, a 3D display of the Delta R distance and Transverse Momentum Error is displayed for all filter parameters.</li>
</ol>

## WARNINGS!
<p>Running this with a very low or 0 minimum energy will cause the program to be very slow. It is suggested that if you want to test a filter range from 0 min en and up, you do it in chunks. As an example, if you wanted to do 0-4 min en, you should do 1-4 min en and then 0-1 min en.<br>
Sometimes the program just stops. I have no idea why; there are no errors; ROOT just quits and returns to the default command line. This typically only happens if the program is running several data sets at once. As such, I recommend running them in small batches or one by one.</p>

## To Do
<ol>
	<li>Much of the code needs to be migrated over to a for_each and transform to take advantage of vectorization.</li>
	<li>The filter searching code should be turned into a 'recursive' loop so that searches can run faster and more efficiently.</li>
	<ol>
		<li>Right now, the code runs on the first OOC_Cells vector over and over, no matter its filter. Implementing a way to either trim the vector of cells that can no longer pass will speed up the process and allow for larger search ranges.</li>
		<li>On this note, if trimming the vector is the best solution, then it may be wise to move away from vectors as they are slow when it comes to deleting elements.</li>
	</ol>
</ol>
