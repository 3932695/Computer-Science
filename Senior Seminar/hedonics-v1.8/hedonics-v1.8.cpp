
//	Hedonics 
//  v1.8 Chris Georges  June 2011   multiplicative quality increments 
//  v1.7 Chris Georges  Oct 2010    adds labor overhead, can suppress intermed goods
//                                  restart accounting fixed 6-3-11
//  v1.6 Chris Georges  July 2010   adds quasi discrete choice option for R&D choice 
//  v1.6 Chris Georges  March 2010  adds endogenous innovation -- adoption of R&D with labor cost
//	v1.5 Chris Georges  July 2009	adds loop over random seed and calculates means and variances of output
//                                  and corrects memory leak in consumer search aug 2 2009
//	v1.4 Chris Georges  June 2009 	adds complementarities
//	v1.3 Chris Georges  June 2009 	adds indivisibilities
//  v1.2 Chris Georges  June 2009   add quality and inflation adjusted output to v1.1    
//  v1.1 Chris Georges  Dec 2008    fixes product shares in v1.0
//	v1.0 Chris Georges  July 2008	alters CES Firm Dynamics model: firms1 devc++ v2.6 (see history below)
//										purpose is to add hedonic product characterization and explicit 
//										model of product innovation

//  Firm Dynamics
//  v2.6 Chris Georges Jan 2008 
//  v2.0 Chris Georges March 2007
//  v1.0 Dane Johnson  Dec 2006
	
   

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "hedonics-firm-v1.8.h"
#include "hedonics-utilities-v1.8.h"
#include "time.h"
#include  <cassert> //7/4/09

// Global Variables

// Main Function
int main() {

	//output files
    std::ofstream output1("data1.txt");		//output timm series of aggregate data
    std::ofstream output2("data2.txt");		//output last round firm distributions of size, productivity, etc.
    std::ofstream output3("data3.txt");		//output time series for six representative firms
	std::ofstream output4("data4.txt");		//output last round firm dist of hedonic quality vectors and final demand shares
	std::ofstream output5("data5.txt");		//output mean and volatility of Yc for each randSeed //7/6/09	
	std::ofstream testoutput("test.txt");	//track firm 6 if anotation switch is on
	
	//for looping over random seeds
    int randSeed; //7/5/09
	int randSeedStart = 12; //12
	int randSeedEnd = 12; //12
	double mean[randSeedEnd - randSeedStart + 1]; //7/6/09
	double vol[randSeedEnd - randSeedStart + 1]; //7/6/09
	
	//for recording mean and volatility of output each run
    for(int i=0;i<randSeedEnd-randSeedStart+1;i++) {mean[i]=0;}
	for(int i=0;i<randSeedEnd-randSeedStart+1;i++) {vol[i]=0;}
		
	//top loop: loop over random seeds for multiple runs
	for(randSeed = randSeedStart; randSeed <= randSeedEnd; randSeed ++) { //7/5/09
	
    //set random seed for the current run
    srand(randSeed); 
	
    //declarations
    int i,j;//k; //k unused, removed 7-7-11
    int round, numRandD, restarts;
    int numMutationPairs, numSearchTrials;
    double elasDem, totOutput, totUtility;
    double overHeadG, overHeadL; 
    double avTechEff, strtTech; 
    double wageBill, gdpDeflator, nomGDP, realGDP;
    bool commonShocks, imitation, anotation, altPriceIndex, cesHedonics, debugging;
    bool endogInnovation, discChoice, intermediateGoods, multiplicativeMutation;
    time_t startTime, endTime;
    double secs, intPriceDiscount, probRandomRestart, mutScale, probInnovate, probUpTick, probDownTick;
    double cesHedonicsElastGoods, cesHedonicsElastChars;
    double probIntegerConstrained, probComplements, probEffShock;
    double riGain, overHeadRandD, lastOutput, rpGain, probRandDInvestMutation, intensityOfChoice;
    double complementIntConstraintFactor, incrementRate; 
	
    //settings for all runs
    const int firmNum = 100;   
    const int rounds = 2000;
    int startOutput1 = 1000; // start recording output
    int outputFrequency = 1; // record each xth round, 10 is every 10th round, 1 is every round
    int printRoundsFrequency = 10; // during simulation on std output 
    int startTechShocks = rounds + 1; // start shocks to labor efficiency
    int endTechShocks = rounds; // rounds, 100
    int startRandDInvest = 1; // updating choice of investment status
    int endRandDInvest = rounds; // rounds
    int startProductInnovation = 1; // actual updating of hedonic product qualities
    int endProductInnovation = rounds; // rounds
    int startConsumerSearch = 1; // rep consumer searches for new product mix
    int endConsumerSearch = rounds; // rounds
	int startVolatilityMeasure = 5000; // for mean and volatility stats -- volatility as average absolute percent change from previous round
	int volatilityMeasureFrequency = 10; // this is freqency for sampling between startVolatilityMeasure and rounds
	probEffShock = 0.001; // 
    probIntegerConstrained = 0.0; // 0.2
    probComplements = 0.0; // prob firm has complements //.2 // .5 
    complementIntConstraintFactor = 0.1; // 1 // fractional "integer" constraint for complements // in (0,1] for less granularity , > 1 for more granularity // 11/12/10
    numSearchTrials = 100;  //for individual consumer search -- number of search trials to test share changes //20 //changed 11/15/10
    numMutationPairs = 10; //for individual consumer search -- number of product pairs to alter per search trial //20 //changed 11/15/10
    mutScale= (double) 1.0 / (double) firmNum; //1.0 //for consumer search -- upper limit of share mutations -- should be <1 and on order of 1/firmNum
    probInnovate = 0.02; //0.2 or 0.01 for slower // prob firm has product innovation (per period) if eligible //0.02 changed to .2 for endog innovation
    probUpTick = 0.05; //prob of uptick (per hedonic element) if product innovation //0.01
    probDownTick = 0.05; //prob of downtick (per hedonic element) if product innovation -- should be < probUpTick //0.01
    elasDem = 2.0;  // removed except for legacy use in doRestarts* and writeMarketShares // 
    overHeadG = 0.0; // fixed overhead component of input needed from neighbor firm in units of neighbor's good -- 1.22558 if mu=2.0, gamma=0.1, and delta=0.7
    overHeadL = 1.0; // fixed overhead labor cost (in dollars) // added 10/4/10
    overHeadRandD = 0.1; //fixed labor cost per period (in dollars) of having RandD investment status == 1 //0.1
    intPriceDiscount = 0.7; //0.7
    probRandomRestart = 0.00; // default 0.00005
    commonShocks = false; // heterogeneous vs. common shocks version
    anotation = false; // blow by blow description of activity of firm 4 to file test.txt 
    debugging = false; // prints sequence of procedures //8/2/09
    imitation = true; // for restarts -- if false, reset A_i and theta_i to 1.0 at restart
    multiplicativeMutation = true; // for hedonic innovation, if false then mutation is additive (characteristics incremented by +-1), if true increments are nearest integer proportional //6-9-11
    incrementRate = 0.4; // for multiplicative mutation, mutations are max{1, incrementRate*char}
    altPriceIndex = false; //if false, real GDP and gdpDeflators are standard (w/based year period 0). if true then use alt index that uses nom shares as weights in gdp deflator -- this removes hysteresis in y from idiosyncratic productivity shocks
    cesHedonics = true; //added 6/24/09 if false, no diminishing utility to characteristics by product // if true, dim u gives taste for variety
    cesHedonicsElastGoods = 0.8; // elasticity for utility ag over goods <=1 // 1 is no dim utility to characteristics by product// orig 6/24/09 // broken out 8/30/10 // technically is not elast // 0.8
    cesHedonicsElastChars = 0.8; // elasticity for utility ag over characteristics // orig 6/24/09 // broken out 8/30/10 //  0.8
    endogInnovation = true; //3/21/10 // product innovation depends on the firm's recent investments in r&D
    discChoice = true; //8/30/10 //quasi discrete choice version for R&D investment choice
    intermediateGoods = false; //10/6/10 //if this is false will bypass doIntermediateGoods, should also set overHeadG=0 above and set inputFactor=0 in firm.h manually -- though not necessary
	riGain = 0.1; //recentRandDInvestment updating gain
	rpGain = 0.2; //recentProfit updating gain
	intensityOfChoice = 0.5; //for quasi discrete choice selection of RandD investment status 0.2
	probRandDInvestMutation = 0.01; //random flipping of R&D investment status
    avTechEff = 1.0; // 1.0
    strtTech = 1.0; //7-12-11
    gdpDeflator = 1.0; // 1.0
    nomGDP = 1.0;// 1.0
    realGDP = 1.0; // 1.0
	wageBill = 0.0; // total wage bill (plus nominal transfer) which is spent on consumption goods //0.0
	numRandD = 0; // number of firms engaging in R&D // 0
	
	time(&startTime);
    
	//establish the array of firms -- allocate memory in heap  
    firm *firms;
    firms = new firm[firmNum];
    //firm firms[firmNum];  //this would place array in the stack 
			
	//set random seed for the current run //moved above 10-6-10
    //srand(randSeed); 
    
	//print some basic info
	printf("randSeed = %d \n", randSeed); //7/5/09
    printf("number of firms is %d \n", firmNum);  
    printf("size of firm is %d B; size of population is %f MB \n", sizeof(firm), (double) firmNum * (double) sizeof(firm) /1000000 );
    //testoutput << "number of rounds is " << rounds << "\n";
    //testoutput << "number of firms is " << firmNum << "\n";
    //testoutput << "size of firm is " << sizeof(firm) << " B; size of population is " << sizeof(firm)/1000000 << "\n";  
    
    //inititalize firms //moved to utilities 10-4-10
    initializeFirms(firms, firmNum, round, testoutput, anotation, probComplements, probInnovate, probIntegerConstrained, intPriceDiscount); 
     
    //output data on number of products with int constraints and complements
    //printf("number of products is %d \n", firmNum);
    int numWithIntConstraints = 0;
    for(i=0;i<firmNum;i++) {if(firms[i].getIntegerConstrained()) {++numWithIntConstraints;}}
    printf("number of products with integer constraints is %d \n", numWithIntConstraints);
    int numWithComplements = 0;
    for(i=0;i<firmNum;i++) {
     	if(firms[i].getHasComplements()) {
    		++numWithComplements;
			//printf("does firm %d have complementary products? %d\n",i,firms[i].getHasComplements());
			//printf("firm %d has %d complementary products\n", i, firms[i].getNumComplements());	
			//printf("firm %d 's first complementary product is %d \n", i, firms[i].getComplementaryProductK(0)); //7/3/09
			//printf("complementary hedonic element 1 for firm %d is %d \n", i, firms[i].getComplementaryHedonicElementKJ(0,0));
		}
    }
    printf("number of products with complements at start of simulation is %d \n", numWithComplements);
        	 
	//output data on first firm with complements
	i=0;
	while(! firms[i].getHasComplements() && i < firmNum) {i++;} 
	if(i<firmNum){
       printf("firm %d is the first firm with complements \n",i);
	   printf("firm %d has %d complements \n",i,firms[i].getNumComplements());
	   printf("firm %d 's first complementary product is %d \n", i, firms[i].getComplementaryProductK(0));
	   //printf("at start of simulation firm %d's first complementary hedonic quality vector is (",i);
	   //for(j=0;j<numHedonicElements -1;j++) {printf("%d,", firms[i].getComplementaryHedonicElementKJ(0,j));}
	   printf("at start of simulation, firm %d's final demand share is %f \n", i,firms[i].getFinalDemandShare());  
    }
	int qqq = i; //3/19/10
	    
    restarts = 0;
    round = 0;
	
	//activity loop: loop over rounds in a run
    for(i = 0; i < rounds; i++) {
		round = i;
		if(anotation) {testoutput << "round " << round + 1 << ":" << "\n";}
		wageBill = 0.0;
		numRandD=0; //7/9/10
		
		//reset current profits to 0
		for(j = 0; j<firmNum; j++) {firms[j].setProfit(0.0);}
		
		//R and D investment choice and accounting
        if(debugging){printf("update RandD investment decisions for round %d \n", round + 1);} //3/20/10
		if(endogInnovation && round >= startRandDInvest && round <= endRandDInvest) { 
            if(discChoice){updateRandDInvestmentStatusDC(firms, firmNum, intensityOfChoice, probRandDInvestMutation, intermediateGoods, overHeadL, overHeadRandD, intPriceDiscount, testoutput, round, anotation);} //7/20/10 quasi discrete choice
            else {updateRandDInvestmentStatus(firms, firmNum, intensityOfChoice, probRandDInvestMutation, intermediateGoods, overHeadL, overHeadRandD, intPriceDiscount, testoutput, round, anotation);} //3/22/10 individual social learning
        } //modified 8/30/10
        doOHandRandDAccounting(firms, firmNum, riGain, overHeadRandD, overHeadL, wageBill, numRandD, testoutput, round, anotation); //8/31/10 //moved out of updateR&DInvestmentStatus utility
        
        //innovation
        if(debugging){printf("do product and process innovation for round %d \n", round + 1);} //8/2/09 
		if(commonShocks) {updateTechEffCommonShock(firms, firmNum, testoutput, round, avTechEff, strtTech, anotation);} //needs to be fleshed out
		else {
      		if(round >= startTechShocks && round <= endTechShocks) { //6/02/09
				updateTechEff(firms, firmNum, testoutput, round, avTechEff, strtTech, anotation, probEffShock);
			}  //6/02/09
	      	if(!endogInnovation && round >= startProductInnovation && round <= endProductInnovation) { //6/02/09
				updateHedonicQual(firms, firmNum, testoutput, round, probInnovate, probUpTick, probDownTick, anotation);
			} //6/02/09
			if(endogInnovation && round >= startProductInnovation && round <= endProductInnovation) { //3/20/10
			    doEndogProductInnovation(firms, firmNum, testoutput, round, probInnovate, probUpTick, probDownTick, multiplicativeMutation, incrementRate, anotation); //3/22/10
			} //3/20/10 // multiplicativeMutation added 6-9-11
		}
		
		//prices, intermediate goods, and production
		if(debugging){printf("set prices for round %d \n", round + 1);} //8/2/09 
		updatePrice(firms, firmNum, /*inputFactor,*/ testoutput, anotation, intPriceDiscount); 
		if(debugging){printf("order produce and sell intermediate goods for round %d \n", round + 1);} //8/2/09 
		//doProduction(firms, wageBill, firmNum, totDeficit, defMax,  overHeadG, testoutput, round, anotation, intPriceDiscount); //split up 10-6-10
		doIntermediateGoods(firms, wageBill, firmNum, overHeadG, testoutput, round, anotation, intPriceDiscount, intermediateGoods); //10-6-10
        if(debugging){printf("produce consumption goods for round %d \n", round + 1);} //8/2/09 
        doProduction(firms, wageBill, firmNum, overHeadG, testoutput, round, anotation, intPriceDiscount, intermediateGoods); //10-6-10
        
        //consumer search and sales
		if(round >= startConsumerSearch && round <= endConsumerSearch) { //6/02/09  
           if(debugging){printf("do consumer search for round %d \n", round + 1);} //8/2/09
           totUtility = doConsumerSearch(firms, wageBill, firmNum, testoutput, round, numMutationPairs, numSearchTrials, mutScale, anotation, cesHedonics, cesHedonicsElastGoods, cesHedonicsElastChars, complementIntConstraintFactor);
		} //6/02/09 also return totUtility is new     
		if(debugging){printf("do final sales for round %d \n", round + 1);} //8/2/09
        totOutput = doFinalSales(firms, wageBill, firmNum, rpGain, testoutput, round, 
            anotation, altPriceIndex, nomGDP, realGDP, gdpDeflator); //6/8/09 add nomGDP, realGDP, gdpDeflator 
		
		//calc mean and volatility of output
		if(debugging){printf("calc volatility for round %d \n", round + 1);} //8/2/09
		if(round == startVolatilityMeasure - volatilityMeasureFrequency) {lastOutput = totOutput;}			
		if(round>=startVolatilityMeasure && round % volatilityMeasureFrequency == 0){	//7/6/09
			mean[randSeed - randSeedStart] += totOutput;
			vol[randSeed - randSeedStart] += fabs(log(totOutput) - log(lastOutput))*100;
			//if(round % 100 == 0 ) printf("abs percent change Yc in round %d is %f \n", round, /*fabs(log(totOutput) - log(lastOutput))*100*/ totOutput - lastOutput);
			lastOutput = totOutput; //7/6/09
		} 
		if(round==rounds-1){ //7/6/09
			mean[randSeed - randSeedStart] = (mean[randSeed - randSeedStart]/((double)rounds - (double) startVolatilityMeasure))*((double) volatilityMeasureFrequency);
			vol[randSeed - randSeedStart] = (vol[randSeed - randSeedStart]/((double)rounds - (double) startVolatilityMeasure))*((double) volatilityMeasureFrequency);
			//printf("volatility of Tc is %f \n", vol[randSeed-randSeedStart] );
            //printf("mean of Yc is %f \n", mean[randSeed-randSeedStart]);
			} 
					
		//output main time series to output1 (for first randSeed only)
		if(round >= startOutput1 && round % outputFrequency == 0 && randSeed == randSeedStart){  //6/02/09 added totUtility, removed avQual 6/8/09 add nomGDP realGDP gdpdeflator
			if(debugging){printf("output1 for round %d \n", round + 1);} //8/2/09 
            output1 << round << " " << totOutput << " " << nomGDP << " " 
			<< realGDP << " " << gdpDeflator << " " << totUtility << " " 
			<< avTechEff << " " << strtTech << " " << wageBill << " " 
			<< restarts << " " << numRandD << "\n";
		}
		//output sixfirm time series to output3 (for first randSeed only)
		if(round >= startOutput1 && round % outputFrequency == 0 && randSeed == randSeedStart){	
            if(debugging){printf("output3 for round %d \n", round + 1);} //8/2/09
			output3 << round << " " << (firms[3]).getFinalProduction() << " " << (firms[3]).getExptdFinalDemand()/(firms[3]).getPrice() << " " << (firms[3]).getCapital() << " ";
			output3 << (firms[4]).getFinalProduction() << " " << (firms[4]).getExptdFinalDemand()/(firms[4]).getPrice() << " " << (firms[4]).getCapital() << " ";
			output3 << (firms[5]).getFinalProduction() << " " << (firms[5]).getExptdFinalDemand()/(firms[5]).getPrice() << " " << (firms[5]).getCapital() << " ";
			output3 << (firms[6]).getFinalProduction() << " " << (firms[6]).getExptdFinalDemand()/(firms[6]).getPrice() << " " << (firms[6]).getCapital() << " ";
			output3 << (firms[7]).getFinalProduction() << " " << (firms[7]).getExptdFinalDemand()/(firms[7]).getPrice() << " " << (firms[7]).getCapital() << " ";
			output3 << (firms[8]).getFinalProduction() << " " << (firms[8]).getExptdFinalDemand()/(firms[8]).getPrice() << " " << (firms[8]).getCapital() << "\n";
		}
		//testoutput (for first randSeed only)
		if(round == 3 && randSeed == randSeedStart) {
            if(debugging){printf("testoutput for round %d \n", round + 1);} //8/2/09 
			testoutput <<  "  final production: " << (firms[0]).getFinalProduction() << " " << (firms[1]).getFinalProduction() << " " 
				<< (firms[2]).getFinalProduction() << " " <<  (firms[3]).getFinalProduction() << " " 
				<< (firms[4]).getFinalProduction() << " " <<  (firms[5]).getFinalProduction() << " " 
				<< (firms[6]).getFinalProduction() << " " <<  (firms[7]).getFinalProduction() << " " 
				<< (firms[8]).getFinalProduction() << " "  << (firms[9]).getFinalProduction() << "\n" ;
		}
        
        //restarts 
        if(debugging){printf("do restarts for round %d \n", round + 1);} //8/2/09 
		if(commonShocks) 
			restarts = doRestartsCommonShock(firms, firmNum, strtTech, wageBill, elasDem, /*fixedNominalTransfer,*/ /*inputFactor,*/ overHeadG, intPriceDiscount, imitation, probRandomRestart);
		else
			restarts = doRestartsHedonics(firms, firmNum, strtTech, wageBill, elasDem, /*fixedNominalTransfer,*/ /*inputFactor,*/ overHeadG, intPriceDiscount, imitation, probRandomRestart, probIntegerConstrained, probComplements);
                
		wageBill = 0.0; //fixed from == 8/2/09
		
		if ((i+1) % printRoundsFrequency == 0) printf("Completed round %d\n", i + 1); 

    }//end of activity loop

    //output last round firm distributions to output2 (for first randSeed only)
	if(randSeed == randSeedStart){
        if(debugging){printf("output2 for final round \n");} //8/2/09
		for(i = 0; i < firmNum; i++) {
          output2 << (firms[i]).getCapital() << " ";
          if((firms[i]).getExptdFinalDemand()/(firms[i]).getPrice() >= (firms[i]).getFinalProduction() ) { //output quantity sold 
                output2 << (firms[i]).getFinalProduction() << " ";
				output2 << (firms[i]).getFinalProduction() * (firms[i]).getPrice() << " "; //add nominal sales //7/8/09
          }
          else {
			output2 << (firms[i]).getExptdFinalDemand()/(firms[i]).getPrice() << " ";
			output2 << (firms[i]).getExptdFinalDemand() << " "; //add nominal sales //7/8/09
		  }
          output2 << (firms[i]).getFinalProduction() << " "; //ouput quantity produced
          output2 << (firms[i]).getExptdFinalDemand()/(firms[i]).getPrice() << " "; //output quantity demanded 
          output2 <<  (firms[i]).getTechEff() << " " <<  /*(firms[i]).getQual() <<*/ "\n";
		} 
	}
	
	//output last round firm dist of hedonic quality vectors and final demand shares (for first randSeed only)
	if(randSeed == randSeedStart){
        if(debugging){printf("output4 for last round \n");} //8/2/09
		for(i = 0; i < firmNum; i++) {
			for(j = 0; j < numHedonicElements; j++) {output4 << (firms[i]).getHedonicQualityElementJ(j) << " ";}
			output4 << "  " << (firms[i]).getFinalDemandShare() << "\n";
			//printf("at end of simulation, firm %d has innovation status %d \n",i+1,firms[i].getRandDInvestment());//3/24/10 testing
		}
	}
         
    //print end of simulation Yc stats, and demand share for first firm with complements
    if(qqq < firmNum) {printf("at end of simulation, firm %d's final demand share is %f \n", qqq,firms[qqq].getFinalDemandShare());}
    printf("mean of Yc is %f \n", mean[randSeed-randSeedStart]); //7/6/09
	printf("volatility of Yc is %f \n", vol[randSeed-randSeedStart]); //7/6/09	
	
	//for all randSeeds, output mean and volatility of Yc to output5 -- volatility is average absolute % change from volatilityMeasureFrequency periods ago
	output5 << randSeed << " " << mean[randSeed-randSeedStart] << " " << vol[randSeed-randSeedStart] << "\n"; //7/6/09
			
    time(&endTime);
    secs = difftime(endTime, startTime);
    printf("Done Running Simulation. \n" ); 
    printf("Simulation took %f minutes. \n", secs/60);
	
	//testoutput (for first randSeed only)
	if(randSeed == randSeedStart){testoutput << "simulation took " << secs/60 << " minutes " << "\n";}
	
    delete[] firms; //7/6/09 
	firms = NULL; //7/6/09
	
    } //end for randSeed loop

    //close output files at end of all runs
    output1.close();
    output2.close();
    output3.close();
	output4.close(); //7/5/09
	output5.close(); //7/6/09
    testoutput.close();
    
	system("PAUSE"); //only for windows
	
	return 0;
	
	} //end main

