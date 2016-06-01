
##Data Modelling for the Evaluation of Virtualized Network Functions Resource Allocation Algorithms

Network Function Virtualization (NFV) proposes to move packet processing from dedicated hardware middle-boxes to software running on commodity servers: virtualized Network Function (NFs) (i.e, Firewall, Proxy, Intrusion Detection System etc.). We have been developing an experimental platform called Network Function Center (NFC) to study issues related to NFV and NFs, assuming that the NFC will deliver virtualized NFs as a service to clients on a subscription basis. Our studies specially focus on dynamic resource allocation for NFs and we have proposed two new resource allocation algorithms based on Genetic Programming (GP) [1] and currently working on another algorithm based on Iterative Local Search. For a more realistic evaluation of these algorithms, testing data is a fundamental component, but unfortunately, public traffic data specifically referring to virtualized NFs chains is not readily available. Therefore, we developed a model to generate the specific data we needed, based on the available general traffic data [2].
This repository contains all the details about how we modelled general data into the specific data we wanted, with along the software we used and the assumptions we made during the data modelling process. Using this data and programs, the evaluation results presented in our publications can be easily reproduced.

[1] W. Rankothge, J. Ma, F. Le, A. Russo, and J. Lobo, [“Towards making network function virtualization a cloud computing service,”] (http://repositori.upf.edu/handle/10230/26035) in IM 2015

[2] W. Rankothge, F. Le, A. Russo, and J. Lobo, [“Experimental results on the use of genetic algorithms for scaling virtualized network functions,”] (http://repositori.upf.edu/handle/10230/26036) in IEEE SDN/NFV 2015

##Project Structure:
1.	GeneratePolicies
2.	DistributeTrafficOverPolicies
3.	PoliciesToChange
4.	TopologyCreator
5.	ExampleDataSet

##Guidelines to use the data and programs in the repository

There are two ways that this repository can be useful for anyone that needs data about VNFs and their traffic on the cloud.
1) Directly use the already generated data set
2) Generate your own data set using the given programs

##How to use the already generated data set: ExampleDataSet

We have generated data for
1) Possible policy requests with initial traffic passing through them defined
2) Scaling requirements for each 15 minutes for 2 days
3) Topology data (nodes, links, paths) for K-Fat Tree, BCube and VL2 architectures with 64 servers

You can use these data directly as inputs for your experiments.

##How to use the programs and generate the required data sets

If you want to generate your own data sets according to your requirements, you can use the given programs.

1) First step is to generate the policy requests data set using the policy requests generation program: GeneratePolicies.
Inputs to the program: number of large scaled enterprise networks 
Output of the program: a set of policies for each enterprise with 100 NFs

2) After we have created the policy requets data set, the seconds step is to create the traffic data set for the policies using the initial traffic distribution program: DistributeTrafficOverPolicies.
Inputs to the program: the set of policies, initial traffic load 
Output of the program: distribution of the traffic load over policies

3) The third step is to create the scaling requirements data set to reflect the traffic changes over the time using the scaling requirements over the time program: PoliciesToChange.

4) The last step is to generate the required topology data for different network architectures (K-Fat tree, BCube, VL2) using the topology generation program: TopologyCreator
Inputs to the program: network architecture and number of servers 
Output of the program: the topology: nodes, links and paths

##License

All the software programs are distributed under the terms of the [GNU General Public License v3](http://www.gnu.org/licenses/gpl-3.0-standalone.html).

##When using this archive, please cite the above papers:

@INPROCEEDINGS{IM,
	AUTHOR = "W. Rankothge and J. Ma and Frank Le and A. Russo and J. Lobo",
	TITLE = "Towards Making Network Function Virtualization a Cloud Computing Service",
	BOOKTITLE = "IEEE IM 2015"}
	
@INPROCEEDINGS{IEEESDN,
	AUTHOR = "W. Rankothge and Frank Le and A. Russo and J. Lobo",
	TITLE = "Experimental Results on the use of Genetic Algorithms for Scaling Virtualized Network Functions",
	BOOKTITLE = "IEEE SDN/NFV 2015"}


