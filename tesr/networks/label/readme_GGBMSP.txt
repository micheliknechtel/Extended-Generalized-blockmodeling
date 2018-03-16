Main class -> GGBMCG.cpp

The main class allocate:

	Parameters * parameters = new Parameters();
	
	/*I'm calling this method because I start always development process in my machine 
	using a IDE, later on I move to the cluster so where parameters should load itself from command line...*/
	
	
    parameters->predefinedParameters();
    
    
    /*This class is going to build set of all possible cluster*/
    ClusterSetBuilder *clusterSet = new ClusterSetBuilder();
    clusterSet->generateSet();
    
    
    /*PrintManager speak for itself :) */
    PrintManager().printAllClusterSet();
    PrintManager().printEpsilon();
    
    /*The error between clusters is a predefined paramater for the model, as I'm generating clusters myself, 
    I need to pre-calculate it  */
    
    DesviationMesuare *desviationMesuare = new  DesviationMesuare();
    desviationMesuare->calculate();
    
    
    /*Here we do the mathematical programming task, that is to chose a partition such that will have the smallest error*/
    SetPartitioning * setPartitioning = new SetPartitioning();
    setPartitioning->solveCplexModel();