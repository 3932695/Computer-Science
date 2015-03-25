//procedures for firms >= v2.4.1 
//broken out of driver.cpp 5-15-07

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm> //8/13/08
#include "hedonics-firm-v1.8.h"
#include "hedonics-utilities-v1.8.h"

//Function Definitions

//initialize firms
void initializeFirms(firm firms[], const int firmNum, int round, std::ofstream &testoutput, bool anotation, double probComplements, double probInnovate, double probIntegerConstrained, double intPriceDiscount) { //moved from main 10-4-10
    int i,j,k;
    for(i = 0; i < firmNum; i++) {
         firm newFirm;
         //newFirm.setTechEff(1 + (randNumUni()-0.5)*1.0); //for het initial distribution
         //expected nominal demand for final goods
         newFirm.setExptdFinalDemand(2.32558); //equilibrium is 2.32558 if h = 1.22558 if mu=2.0, gamma=0.1, and delta=0.7 -- which makes Ystar/n=1.0
         newFirm.setFinalDemand(2.32558); //7/30/08
		 //expected real demand for intermediate goods
         newFirm.setExptdIntermedDemand(1.0); //is irrelevant under new timing
         newFirm.setPrice((newFirm.getMarkup()/(1-newFirm.getMarkup()*newFirm.getInputFactor()*intPriceDiscount))*(newFirm.getWage()/newFirm.getTechEff())); //9/9/10
		 newFirm.setPrice0(newFirm.getPrice()); //added 6/8/09 
     	 for (j=0; j<numHedonicElements; j++) { //numHedonicElements is declared in firm.h
             if(randNumUni() > 1 - 0.1) {newFirm.setHedonicQualityElementJ(j,rand() % 2);} // random integer in {0,1}
             else {newFirm.setHedonicQualityElementJ(j,0);}
         }
		newFirm.setFinalDemandShare(1/((double) firmNum)); //start with equal nominal demand shares
		//set up integer constraints
		if(randNumUni() > 1 - probIntegerConstrained) {newFirm.setIntegerConstrained(true);}
		for(k=0;k<maxNumComplements;k++) {newFirm.setComplementaryProductK(k,0);} //7/3/09 //maxNumComplements defined in firm.h
		for(k=0;k<maxNumComplements;k++) {
				for(j=0;j<numHedonicElements;j++) {newFirm.setComplementaryHedonicElementKJ(k,j,0);}
		}
		//set up complementarities
		//if(newFirm.getIntegerConstrained()) { //7/19/09 separate incidence of complements from incidence of int constrained
		if(randNumUni() > 1 - probComplements) {
			newFirm.setHasComplements(true);
			newFirm.setNumComplements(rand() % maxNumComplements);
			for(k=0;k<maxNumComplements;k++) {newFirm.setComplementaryProductK(k,rand() % firmNum);}
			for(k=0;k<maxNumComplements;k++) {
				for(j=0;j<numHedonicElements;j++) {
					if(randNumUni() > 1 - 0.1) {newFirm.setComplementaryHedonicElementKJ(k,j,rand() % 2);} // random integer in {0,1}
					else {newFirm.setComplementaryHedonicElementKJ(k,j,0);}
				}
			}
		}
		if(randNumUni() > 1 - probInnovate){newFirm.setRandDInvestment(true);} //3/22/10
		//} /7/19/09
		//count[i] = 0;
		firms[i] = newFirm;
		//printf("at start of simulation, firm %d has innovation status %d \n",i+1,firms[i].getRandDInvestment());//3/24/10 testing
    }
}
    
//Update firm price by markup over full MC
void updatePrice(firm firms[], const int firmNum, /*double inputFactor,*/ std::ofstream &testoutput, bool anotation, double intPriceDiscount) { //added inputFactor
    int i;
    double lastprice, markup;
    firm current, prev;
    
    lastprice = (firms[firmNum-1]).getPrice(); 
    
    for(i = firmNum - 1 ; i >= 0;  i--) { 
         double price;
         current = firms[i];  
         
         if(i == 0) //5-8-07
                price = (1+0.0)*current.getMarkup()*(current.getWage()/current.getTechEff() + current.getInputFactor()*lastprice*intPriceDiscount);
         else   {
                prev = firms[i - 1];
                price = (1+0.0)*current.getMarkup()*(current.getWage()/current.getTechEff() + current.getInputFactor()*prev.getPrice()*intPriceDiscount);
         }
         
         current.setPrice(price);
         if(anotation && i==5) { testoutput << "price of firm " << i+1 << " = " << current.getPrice() << "\n"; }
         firms[i] = current;
    }
}

//production and sale of intermediate goods
void doIntermediateGoods(firm firms[], double &wageBill, const int firmNum, 
         double overHeadG, std::ofstream &testoutput, int round, bool anotation, 
         double intPriceDiscount, bool intermediateGoods) {
  
  double maxIntGoodProduction;
  int i;
  firm current, next, prev;
  //totDeficit = defMax = 0.0; 
  
  if(intermediateGoods) { //10-6-10    //bypasses entire routine if intermediateGoods = false         
                       
    //Firms [i] place orders for  I goods from neighbor firms [i-1] 
    for(i = 0; i < firmNum; i++) {
         
         double exptdMaxFinalProduction;
         current = firms[i];
         if(i == 0)
                prev = firms[firmNum - 1];
         else
                prev = firms[i - 1];
                
         if(anotation && i==5){
             testoutput << "firm " << i+ 1 << " has capital of " << current.getCapital() << "\n";        
             testoutput << "firm " << i+ 1 << " expects nominal final goods demand of $" << current.getExptdFinalDemand() << " and thus real final demand of " << current.getExptdFinalDemand()/current.getPrice() << " units "  << "\n"; 
         }      
         //determine expected constraint on production of C goods (by own capital and own purchase of I goods from neighbor) (plus net revs from sale to other neighbor should be included here
         exptdMaxFinalProduction = ((current.getCapital()-current.getIntGoodOrder()*prev.getPrice()*intPriceDiscount)/(current.getWage()/current.getTechEff())); //5-08-07
         if(exptdMaxFinalProduction < 0.0) exptdMaxFinalProduction = 0;

         //place order for I goods from next neighbor based on expected production of C goods (which is last period's actual demand)
         if(exptdMaxFinalProduction >= (current.getExptdFinalDemand()/current.getPrice()))
                current.setIntGoodOrder(overHeadG + current.getInputFactor()*(current.getExptdFinalDemand()/current.getPrice())); 
         else   {
                current.setIntGoodOrder(overHeadG + current.getInputFactor()*exptdMaxFinalProduction); 
                if(anotation && i==5) { testoutput << "capacity less than exp final demand, so restrict int demand" << "\n"; }
         }
         if(anotation && i==5) { testoutput << "firm " << i + 1 << " orders " << current.getIntGoodOrder() << " units from firm " << i <<  "\n"; }
         firms[i] = current;           
    }
    
    //Firms [i] produce I goods for sale to neighbor firms [i+1].
    for(i = 0; i < firmNum; i++) {
                 
         current = firms[i];
         next = firms[(i + 1)%firmNum];
                
         current.setExptdIntermedDemand(next.getIntGoodOrder()); //can set this here or in next loop for alt timing
         
         //capacity to produce I goods for neighbor is limited by own capital
         maxIntGoodProduction = current.getCapital()/(current.getWage()/current.getTechEff());
         if(maxIntGoodProduction < 0) maxIntGoodProduction = 0;

         //produce I goods for next neighbor, decrement capital by cost, increment ag wage bill
         if(maxIntGoodProduction > current.getExptdIntermedDemand()) { 
                current.setIntGoodProduction(current.getExptdIntermedDemand()); 
                current.setCapital(current.getCapital()-((current.getWage()/current.getTechEff())* current.getExptdIntermedDemand()));
				current.setProfit(current.getProfit() - ((current.getWage()/current.getTechEff())* current.getExptdIntermedDemand())); //3/22/10
				wageBill +=(current.getWage()/current.getTechEff())* current.getExptdIntermedDemand();
         }
         else {
                current.setIntGoodProduction(maxIntGoodProduction);
                wageBill += (current.getWage()/current.getTechEff())*maxIntGoodProduction ;
                current.setCapital(current.getCapital()-(current.getWage()/current.getTechEff())*maxIntGoodProduction );
				current.setProfit(current.getProfit() - (current.getWage()/current.getTechEff())*maxIntGoodProduction ); //3/22/10
				if(anotation && i==5) { testoutput << "capacity less than exp intermediate demand, so limit intermed production" << "\n"; }
         }
         if(anotation && i==5){
                testoutput << "firm " << i + 1 << " produces " << current.getIntGoodProduction() << " units for firm " << i + 2 <<  "\n"; 
                testoutput << "cost of production is " << current.getIntGoodProduction()*(current.getWage()/current.getTechEff()) << "\n"; 
                testoutput << "firm " << i+ 1 << " now has capital of " << current.getCapital() << "\n";  
         }
         firms[i] = current;
    }
  
    //neighbors [i+1] buy I goods 
    for(i = 0; i < firmNum; i++) {
         /*double afdUnits;*/
         current = firms[i];
         next = firms[(i + 1)%firmNum];

         //setIntGoodOrder was updtated for current period in last loop
         //current.setExptdIntermedDemand(next.getIntGoodOrder());

         //sell I goods to neighbor, update both firms capitals by sale,
         //this sale (and thus neighbor's capacity to produce C goods) can be constrained by my supply of I goods
         if(current.getIntGoodProduction() < next.getIntGoodOrder()) {
                next.setMaxFinalProduction((current.getIntGoodProduction() - overHeadG)/next.getInputFactor()); //take out OH // input factor now tied to firm 9/9/10
                next.setCapital(next.getCapital()-(current.getIntGoodProduction()*current.getPrice()*intPriceDiscount)); //5-08-07
				next.setProfit(next.getProfit() - (current.getIntGoodProduction()*current.getPrice()*intPriceDiscount)); //3/22/10
				current.setCapital(current.getCapital() + (current.getIntGoodProduction()*current.getPrice()*intPriceDiscount)); //5-08-07
				current.setProfit(current.getProfit() + (current.getIntGoodProduction()*current.getPrice()*intPriceDiscount)); //3/22/10
				if(anotation) {
                    if(i==4) { 
                         testoutput << "firm " << i + 2 << " buys " << current.getIntGoodProduction() << " units from firm " << i+1 << "\n"; 
                         testoutput << "cost is " << (current.getIntGoodProduction()*current.getPrice()*intPriceDiscount) << "\n"; 
                    }     
                    if(i==5) { 
                         testoutput << "can't meet neighbor intermed demand" << "\n"; 
                         testoutput << "firm " << i + 1 << " sells " << current.getIntGoodProduction() << " units to firm " << i + 2 << "\n"; 
                         testoutput << "revenues are " << (current.getIntGoodProduction()*current.getPrice()*intPriceDiscount) << "\n"; 
                    }
                }
         }
         else {
                next.setMaxFinalProduction((next.getIntGoodOrder() - overHeadG)/next.getInputFactor()); //take out OH 
                next.setCapital(next.getCapital() - (next.getIntGoodOrder()*current.getPrice()*intPriceDiscount)); //5-07-08
				next.setProfit(next.getProfit() - (next.getIntGoodOrder()*current.getPrice()*intPriceDiscount)); //3/22/10
				current.setCapital(current.getCapital() + (next.getIntGoodOrder()*current.getPrice()*intPriceDiscount)); //5-08-07
				current.setProfit(current.getProfit() + (next.getIntGoodOrder()*current.getPrice()*intPriceDiscount)); //3/22/10
                if(anotation) {
                    if(i==4) { 
                         testoutput << "firm " << i + 2 << " buys " << next.getIntGoodOrder() << " units from firm " << i+1 << "\n"; 
                         testoutput << "cost is " << (next.getIntGoodOrder()*current.getPrice()*intPriceDiscount) << "\n"; 
                    }
                    if(i==5) { 
                         testoutput << "firm " << i + 1 << " sells " << next.getIntGoodOrder() << " units to firm " << i + 2 << "\n"; 
                         testoutput << "revenues are " << (next.getIntGoodOrder()*current.getPrice()*intPriceDiscount) << "\n"; 
                    }
                }
         }
         firms[i] = current;
         firms[(i + 1)%firmNum] = next;
         if(anotation && i==5) {testoutput << "firm " << i+ 1 << " now has capital of " << current.getCapital() << "\n"; }     
    }                 //end for
  }                   //end if (bypass)
}                     //end doInermediateGoods

//production of final (consumption) goods
void doProduction(firm firms[], double &wageBill, const int firmNum, 
         double overHeadG, std::ofstream &testoutput, int round, bool anotation, 
         double intPriceDiscount, bool intermediateGoods) {
                
    double maxFinalGoodProduction, unitPrice ;
    int i;
    firm current, next, prev;
    //totDeficit = defMax = 0.0; //these were referenced by &totDeficit and &defMax in doProduction() // removed 10-6-10

    //firm i produce C goods (for public demand); no sale of C goods yet
    for(i = 0; i < firmNum; i++ ) {

         current = firms[i];
         //capital constraint for purchasing labor after intermediate goods production, purchases, and sales
         maxFinalGoodProduction = current.getCapital()/(current.getWage()/current.getTechEff()); //changed maxIntGoodProduction to maxFinalGoodProduction from here down 4-17-07
         if(maxFinalGoodProduction < 0) maxFinalGoodProduction = 0.0;
         unitPrice = current.getWage()/current.getTechEff();
         //PPD = (current.getPrice()/unitPrice) - 1.0; //not used ?

         //constraint by more restrictive of (1) financial capacity to hire labor and (2) intermediate goods on hand
         if(maxFinalGoodProduction > current.getMaxFinalProduction() && intermediateGoods) 
                maxFinalGoodProduction = current.getMaxFinalProduction();
         if (maxFinalGoodProduction < 0) maxFinalGoodProduction = 0.0; 
                  
         //produce C goods, decrement capital by labor cost, increment ag wage bill  
         if(maxFinalGoodProduction < current.getExptdFinalDemand()/current.getPrice()) { 
                current.setFinalProduction(maxFinalGoodProduction);
                wageBill += maxFinalGoodProduction*unitPrice;
                current.setCapital(current.getCapital()-(maxFinalGoodProduction*unitPrice));
				current.setProfit(current.getProfit() - (maxFinalGoodProduction*unitPrice)); //3/22/10
                //current.setCapDeficit((current.getExptdFinalDemand()/current.getPrice() - maxFinalGoodProduction)*unitPrice); 
                //totDeficit += (current.getExptdFinalDemand()/current.getPrice() - maxFinalGoodProduction)*unitPrice;  //pulled 10-6-10
                //if((current.getExptdFinalDemand()/current.getPrice() - maxFinalGoodProduction)*unitPrice > defMax)    //pulled 10-6-10
                //    defMax = (current.getExptdFinalDemand()/current.getPrice() -  maxFinalGoodProduction)*unitPrice;  //pulled 10-6-10
                if(anotation && i==3 && current.getExptdFinalDemand()/current.getPrice() - maxFinalGoodProduction > 0.00001) { testoutput << "produce less than exp final demand due to constraint" << "\n"; } 
         }
         else {
                current.setFinalProduction(current.getExptdFinalDemand()/current.getPrice()); 
                current.setCapital(current.getCapital() - ((current.getExptdFinalDemand()/current.getPrice())*unitPrice)); 
				current.setProfit(current.getProfit() - ((current.getExptdFinalDemand()/current.getPrice())*unitPrice)); //3/22/10
                wageBill += (current.getExptdFinalDemand()/current.getPrice())*unitPrice; 
                //current.setCapDeficit(0.0);
         }
         if(anotation && i==5){
                testoutput << "firm " << i + 1 << " produces " << current.getFinalProduction() << " units of final good" << "\n"; 
                testoutput << "additional labor cost is " << current.getFinalProduction()*unitPrice << "\n"; 
         }  
         firms[i] = current;
    }
}

// replaced by doIntermediateGoods() and doProduction() above 10-6-10
// production and sale of intermediate goods, production of final (consumption) goods
//    void doProduction(firm firms[], double &wageBill, const int firmNum, double &totDeficit, double &defMax, 
//         double overHeadG, std::ofstream &testoutput, int round, bool anotation, double intPriceDiscount) {
  
//calculate Utility of the rep consumer given firm shares and total income  //6/7/09
double calcUtility(firm firms[], double wageBill, const int firmNum,  
			double shares[], std::ofstream &testoutput, int round, bool anotation, bool cesHedonics, 
            double cesHedonicsElastGoods, double cesHedonicsElastChars, double complementIntConstraintFactor) {

	//shares[] will be a vector of firm shares // this is new
	
	int ii,jj,kk; //changed all from i,j,k 8/2/09
	double *repConsumption; //8/2/09 //real consumption bundle for the representative consumer //need pointer to put in heap
	repConsumption = new double[firmNum]; //8/2/09
	double *repHedonicConsumption; //8/2/09 //corersponding hedonic bundle
	repHedonicConsumption = new double[numHedonicElements]; //8/2/09
	//double repUtility = 1.0;
	double repUtility = 0.0; //3/26/10 //changed to 0 for CES utility
	double rhoOneInverse = 0.0; //6/30/11
	double rhoTwoInverse = 0.0; //7/7/11
	
	rhoOneInverse = 1.0/cesHedonicsElastGoods; // 6-30-11 //moved here 7/7/11
	rhoTwoInverse = 1.0/cesHedonicsElastChars; // 7/7/11
			
	//we will establish the utility of the consumption bundle in three steps: 
    //note this is all ag consumption, not per worker
	//a. calc real consumption bundle based on inputted firm shares 
	for(ii=0;ii<firmNum;ii++) {
		repConsumption[ii] = (wageBill * shares[ii])/firms[ii].getPrice();
		//if(round == 99 && ii == 9){printf("firm 10 in round 100 has repConsumption %f \n",repConsumption[ii]);} //testing
	} 

	//b. calc hedonic consumption bundle corresponding to that goods bundle //use ces aggregator if cesHedonics
	//c. calc utility for that hedonic bundle //use ces aggregator
	for(jj=0; jj<numHedonicElements; jj++){ //for each characteristic
		double repHedCons = 0.0;
		for(ii=0; ii<firmNum; ii++) {       //for each firm
            if (cesHedonics) { //added 6/24/09
               //first do direct characteristics
               double zz = 0; //added 11/15/10 to combine base and compelements before applying ces
               //repHedCons += (pow((((double) firms[ii].getHedonicQualityElementJ(jj)) * repConsumption[ii]), cesHedonicsElastGoods)); //replaced 11/15/10
               zz += ((double) firms[ii].getHedonicQualityElementJ(jj)) * repConsumption[ii]; //1/15/10
               //then add complementarities
               if(firms[ii].getHasComplements()) {
                  for(kk=0;kk<firms[ii].getNumComplements();kk++) {
                     double overlap = 0;
                     if(repConsumption[ii] < repConsumption[firms[ii].getComplementaryProductK(kk)])
                         //overlap = floor(repConsumption[ii]);
                         overlap = floor((1/complementIntConstraintFactor)*repConsumption[ii])*complementIntConstraintFactor; //added fractional indteger constraint 11/15/10
                     else
                         //overlap = floor(repConsumption[firms[ii].getComplementaryProductK(kk)]); 
                         overlap = floor((1/complementIntConstraintFactor)*repConsumption[firms[ii].getComplementaryProductK(kk)])*complementIntConstraintFactor; //added fractional indteger constraint 11/15/10
                     //overlap = min(floor(repConsumption[i]),floor(repConsumption[firms[i].getComplementaryProductK(k)]));
                     //if(round == 54 && j == 0) {printf("complementary product k is %d \n", firms[i].getComplementaryProductK(k));}
                     //overlap = floor(repConsumption[i]);
                     //repHedCons += (pow((((double) firms[ii].getComplementaryHedonicElementKJ(kk,jj)) * overlap), cesHedonicsElastGoods)); //replaced 11/15/10
                     zz += ((double) firms[ii].getComplementaryHedonicElementKJ(kk,jj)) * overlap; //11/15/10
                  } //end for
               }    //end if hasComplements 
			   repHedCons += (pow(((double) zz), cesHedonicsElastGoods));
				
			   // 6/30/11 need to raise this to 1/rho2 -- probably need to rearrange loops above ********** //done below 7/7/11
               
               //if(firms[i].getHasComplements()) {
               //   for(k=0;k<firms[i].getNumComplements();k++) {
		       //	if(round == 54 && j == 0) {printf("firm %d has %d complementary products\n", i, firms[i].getNumComplements());}
			   //		if(round == 54 && j == 0) {printf("complementary product k for firm %d is %d \n", i, firms[i].getComplementaryProductK(k));}
			   //		if(round == 54 && j == 0) {printf("first complementary hedonic element is %d\n", firms[i].getComplementaryHedonicElementKJ(k,j));}                 
			   //		}
               //}
              
            }       //end if cesHedonics
            else {
               //first do direct characteristics  
               repHedCons += (((double) firms[ii].getHedonicQualityElementJ(jj)) * repConsumption[ii]);
               //then add complementarities
               
			   if(firms[ii].getHasComplements()) { //7/6/09
                  for(kk=0;kk<firms[ii].getNumComplements();kk++) {
                     double overlap = 0;
                     if(repConsumption[ii] < repConsumption[firms[ii].getComplementaryProductK(kk)])
                         overlap = floor(repConsumption[ii]);
                     else
                         overlap = floor(repConsumption[firms[ii].getComplementaryProductK(kk)]);
                     //overlap = min(floor(repConsumption[i]),floor(repConsumption[firms[i].getComplementaryProductK(k)]));
                     //if(round == 54 && j == 0) {printf("complementary product k is %d \n", firms[i].getComplementaryProductK(k));}
                     //overlap = floor(repConsumption[i]);
                     repHedCons += (((double) firms[ii].getComplementaryHedonicElementKJ(kk,jj)) * overlap);
                  }  //end for
               }     //end if hasComplements
            }        //end else
		}            //end for each firm
		if(cesHedonics) {repHedonicConsumption[jj] = (1/((double) firmNum))*pow(repHedCons, rhoOneInverse);} //7/7/11 added if(cesHedonics)
		else {repHedonicConsumption[jj] = repHedCons;} //original code
		//repHedonicConsumption[jj] = repHedCons; //use this in place of the last two lines for simpler v with dim returns //7/7/11
		
		//repUtility *= pow(repHedonicConsumption[jj],1/((double) numHedonicElements)); //this was causing 0 values if any element was 0 for all firms
		repUtility += pow(repHedonicConsumption[jj], cesHedonicsElastChars); //3/26/10 //make this CES to avoid prob of 0 values
		//if(round == 99 && jj == 9){printf("in round 100, repHedonicConsumption for hedonic element 10 is %f \n", repHedonicConsumption[jj]);} //testing
	}                //end for each characteristic
	//rhoOneInverse = 1.0/cesHedonicsElastChars; // 6-30-11
	repUtility = (1/((double) numHedonicElements))*pow(repUtility, rhoTwoInverse); // 7-9-11 //can simply comment this line out to keep simpler version w/dim returns //7/7/11
	//repUtility = 1.0; 
	
	/* //below is routine with compements aggregated by ces separately from base //replaced 11/15/10
	for(jj=0; jj<numHedonicElements; jj++){ //for each characteristic
		double repHedCons = 0.0;
		for(ii=0; ii<firmNum; ii++) {       //for each firm
            if (cesHedonics) { //added 6/24/09
               //first do direct characteristics
               repHedCons += (pow((((double) firms[ii].getHedonicQualityElementJ(jj)) * repConsumption[ii]), cesHedonicsElastGoods));
               //then add complementarities
               if(firms[ii].getHasComplements()) {
                  for(kk=0;kk<firms[ii].getNumComplements();kk++) {
                     double overlap = 0;
                     if(repConsumption[ii] < repConsumption[firms[ii].getComplementaryProductK(kk)])
                         overlap = floor(repConsumption[ii]);
                     else
                         overlap = floor(repConsumption[firms[ii].getComplementaryProductK(kk)]);
                     //overlap = min(floor(repConsumption[i]),floor(repConsumption[firms[i].getComplementaryProductK(k)]));
                     //if(round == 54 && j == 0) {printf("complementary product k is %d \n", firms[i].getComplementaryProductK(k));}
                     //overlap = floor(repConsumption[i]);
                     repHedCons += (pow((((double) firms[ii].getComplementaryHedonicElementKJ(kk,jj)) * overlap), cesHedonicsElastGoods));
                  } //end for
               }    //end if hasComplements 
               //if(firms[i].getHasComplements()) {
               //   for(k=0;k<firms[i].getNumComplements();k++) {
		       //	if(round == 54 && j == 0) {printf("firm %d has %d complementary products\n", i, firms[i].getNumComplements());}
			   //		if(round == 54 && j == 0) {printf("complementary product k for firm %d is %d \n", i, firms[i].getComplementaryProductK(k));}
			   //		if(round == 54 && j == 0) {printf("first complementary hedonic element is %d\n", firms[i].getComplementaryHedonicElementKJ(k,j));}                 
			   //		}
               //}
            }       //end if cesHedonics
            else {
               //first do direct characteristics  
               repHedCons += (((double) firms[ii].getHedonicQualityElementJ(jj)) * repConsumption[ii]);
               //then add complementarities
               
			   if(firms[ii].getHasComplements()) { //7/6/09
                  for(kk=0;kk<firms[ii].getNumComplements();kk++) {
                     double overlap = 0;
                     if(repConsumption[ii] < repConsumption[firms[ii].getComplementaryProductK(kk)])
                         overlap = floor(repConsumption[ii]);
                     else
                         overlap = floor(repConsumption[firms[ii].getComplementaryProductK(kk)]);
                     //overlap = min(floor(repConsumption[i]),floor(repConsumption[firms[i].getComplementaryProductK(k)]));
                     //if(round == 54 && j == 0) {printf("complementary product k is %d \n", firms[i].getComplementaryProductK(k));}
                     //overlap = floor(repConsumption[i]);
                     repHedCons += (((double) firms[ii].getComplementaryHedonicElementKJ(kk,jj)) * overlap);
                  }  //end for
               }     //end if hasComplements
            }        //end else
		}            //end for each firm
		repHedonicConsumption[jj] = repHedCons;
		//repUtility *= pow(repHedonicConsumption[jj],1/((double) numHedonicElements)); //this was causing 0 values if any element was 0 for all firms
		repUtility += pow(repHedonicConsumption[jj], cesHedonicsElastChars); //3/26/10 //make this CES to avoid prob of 0 values
		//if(round == 99 && jj == 9){printf("in round 100, repHedonicConsumption for hedonic element 10 is %f \n", repHedonicConsumption[jj]);} //testing
	}                //end for each characteristic
	*/
	
	//if(round == 99){printf("repUtility in round 100 is %f \n", repUtility);} //testing
	
    delete[] repConsumption; //8/2/09
    repConsumption = NULL; //8/2/09
    delete[] repHedonicConsumption; //8/2/09
    repHedonicConsumption = NULL; //8/2/09
	
    return repUtility;

}

//set final goods demand shares by pseudo consumer search  //7/30/08 
	//return changed to double 6/02/09
	//upgraded to use calcUtility procedure 6/7/09
double doConsumerSearch(firm firms[], double wageBill, const int firmNum, /*const int numHedonicElelments,*/
			std::ofstream &testoutput, int round, int numMutationPairs, int numSearchTrials, double mutScale, bool anotation, bool cesHedonics, 
            double cesHedonicsElastGoods, double cesHedonicsElastChars, double complementIntConstraintFactor) {
	
	//shares are initialized to equal shares in main()
	
	double utility = 1.0; //moved here from top of search loop 6/02/09 so that can return utility from the procedure
	double *shares; //8/2/09
	shares = new double[firmNum]; //8/2/09
	double *altShares; //8/2/09
	altShares = new double[firmNum]; //8/2/09
	double altUtility = 1.0;
	//int i,j; //5/27/09 redundant with below -- may want to check which is better
	int firm1 = 0;
	int firm2 = 0;
	//int firm3 = 0;
	
	//do consumer search
	if (round >= 1) {		
		
        int i,j;
				
		//start with shares and altShares at current shares
		for(i=0;i<firmNum;i++) {
			shares[i] = firms[i].getFinalDemandShare();
			altShares[i] = firms[i].getFinalDemandShare();
		}

		//now use calcUtility routine to get baseline utility
		utility = calcUtility(firms, wageBill, firmNum, shares, testoutput, round, anotation, cesHedonics, cesHedonicsElastGoods, cesHedonicsElastChars, complementIntConstraintFactor);		
		/*
        if(round == 9999 ) {
			printf("finalDemandShare of good 6 is %f \n", altShares[5] );
			printf("hedonic quality element 2 for good 6 is %d \n", firms[5].getHedonicQualityElementJ(1) );
			//printf("repConsumption of good 6 is %f \n", repConsumption[5] );
			//printf("repHedonicConsumption of element 3 is %f \n", repHedonicConsumption[1] );
			printf("current utility is %f \n", utility );
		}
		*/
		
		//now update the shares via a mutation loop: test mutation for each of numMutationPairs pairs of goods
		int s=0;
		int ss=0;
		//int searchTrials = 20; //added 11/15/10 //will move to main
		//for(s=0;s<numMutationPairs;s++) { //moved below
        for(ss=0;ss<numSearchTrials;ss++) { //11/15/10 //add here to have multiple tests as before
            int negCount = 0; //11/15/10
            for(s=0;s<numMutationPairs;s++) { //11/15/10 this is now nested below searchTrials - allows multiple mutation pairs before each test
               double mutFactor=0.0;
               int sss = 0; //7-15-11
			   int integerCase = 0;
			   //int negCount = 0; //moved above 11/15/10
			   int firm3 = 0;
			   //pick two firms to consider changing shares
			   firm1 = rand() % firmNum;
			   firm2 = rand() % firmNum;
			   //make sure they are different 
 		       //while(firm2 == firm1) {firm2 = rand() % firmNum;}
			   //and try for firm2 with positive share 7/11/11 //7-15-11
			   while(firm2 == firm1 || altShares[firm2] == 0 && sss < 20) { //sss < 20 in case one firm has the entire market
                           firm2 = rand() % firmNum;
                           sss++; //7-15-11
               }
 		       //check on integer constraints //added 6/25/09
               if(!firms[firm1].getIntegerConstrained() && !firms[firm2].getIntegerConstrained()) {integerCase = 1;}
               if(firms[firm1].getIntegerConstrained() && !firms[firm2].getIntegerConstrained()) {integerCase = 2;}
               if(!firms[firm1].getIntegerConstrained() && firms[firm2].getIntegerConstrained()) {integerCase = 3;} 
               if(firms[firm1].getIntegerConstrained() && firms[firm2].getIntegerConstrained()) {integerCase = 4;} 
                 
         
               //pick a mutation factor m betwen 0 and mutScale for shares (mutScale < 1.0, should be scaled with numFirms)
			   if(integerCase == 1) { //neither firm is integer constrained
			      mutFactor = randNumUni()*mutScale; //rand number between 0 and mutscale 
                  /* 		
     		      if(round == 54) {
            		printf("from round 54, shares are %f for firm %d and %f for firm %d \n" , altShares[firm1] , firm1 + 1 , altShares[firm2], firm2 + 1);
             		printf("initial mutFactor in round 55 is %f \n" ,  mutFactor); 
             	  }
                  */
                  //determine altShares by adding m to one firm's share and subtracting from another
                  //printf("in round %d , firm1 is %d and firm2 is %d\n" , round , firm1 , firm2);
			      //bound mutFactor so that shares are bounded by 0 and 1. but allow shares to be pushed to bound.
			      if(mutFactor > 1- altShares[firm1]) {mutFactor = 1 - altShares[firm1];}
			      if(mutFactor > altShares[firm2]) {mutFactor = altShares[firm2];} 
			      altShares[firm1] = altShares[firm1] + mutFactor;
			      altShares[firm2] = altShares[firm2] - mutFactor;
      		      /*
                  if(round == 54) {
            		printf("final mutFactor for round 55 is %f \n" , mutFactor);
            		printf("new altShares in round 55 are %f for firm %d and %f for firm %d \n" , altShares[firm1] , firm1 + 1, altShares[firm2] , firm2 + 1); 
                  }
                  */
               }    //end if integerCase 1  
            
               //6/26/09 note that we are making decision to change SHARES lumpy but not so for
               //        changing q_i when p's change. really should have this for all changes in q_i's.
               //        Further, we are allowing violation of 0 sheres bound in cases 2 and 3 -- and then
               //        throwing out any changes for which there is a violation
           
               //this version will add one unit to firm1 and iteratively searches for a set of other firms to deduct shares from
               //currently just picks 10 other firms at random -- currently violates 0 lower bound and integer constraints
               //though no shares actually go negative as neg altShares cause neg utility ??? not true 
               //should set up a proppper search
            
               if(integerCase == 2) { //firm1 is integer constrained // consider adding 1 unit to firm1 and taking shares from all others
                    //if(round == 54){printf("firm 1 is integer constrained \n");}
                    mutFactor = firms[firm1].getPrice() / wageBill;
                    //if(round == 54){printf("firm 1 price is %f \n", firms[firm1].getPrice());}
                    //if(round == 54){printf("firm 1 mutFactor is %f \n", mutFactor);}  
                    //if(round == 54){printf("firm 1 initial share is %f \n", firms[firm1].getFinalDemandShare());} 
                    if(mutFactor < 1- altShares[firm1]) {
                         //if(round == 54){printf("firm 1 mutFactor is less than 1 - current altShares \n");}
                         altShares[firm1] = altShares[firm1] + mutFactor;
                         //if(round == 54){printf("firm 1 new altShare is %f \n", altShares[firm1]);}
                         for(j=0;j<10;j++) { //**** need to keep altShares from going negative here ***  
                              firm3 = rand() % firmNum;
                              //if(round == 54){printf("firm %d initial share is %f \n", firm3 , firms[firm3].getFinalDemandShare());}
                              altShares[firm3] = altShares[firm3] - mutFactor/((double) 10);
                              //if(round == 54){printf("firm %d alt share is %f \n", firm3, altShares[firm3]);}
                              if (altShares[firm3] < 0) {++negCount;}
                              //if(round == 54) {printf("negCount is %d \n" , negCount);}
                         }  //end for
                         //for(j=0;j<firm1;j++){altShares[j] = altShares[j] - mutFactor/((double) firmNum -  1.0);} //alt case take from all other firms
                         //for(j=firm1+1;j<firmNum;j++){altShares[j] = altShares[j] - mutFactor/((double) firmNum -  1.0);} //alt case take from all other firms           
                    }       //end if mutFactor
               }            //end if integerCase 2
                  
               if(integerCase == 3) { //firm2 is integer constrained // consider taking 1 unit from firm2 and adding shares from 10 others
                    mutFactor = firms[firm2].getPrice() / wageBill;  
                    //if(mutFactor > altShares[firm2]) {mutFactor = 0.0;}
                    if(mutFactor < altShares[firm2]) {  
                         altShares[firm2] = altShares[firm2] - mutFactor;
                         //for(j=0;j<firm2;j++){altShares[j] = altShares[j] + mutFactor/((double) firmNum -1.0);}
                         //for(j=firm2+1;j<firmNum;j++){altShares[j] = altShares[j] + mutFactor/((double) firmNum -1.0);}
                         for(j=0;j<10;j++) { //**** need to keep altShares from going negative here ***  
                              firm3 = rand() % firmNum;
                              //if(round == 54){printf("firm %d initial share is %f \n", firm3 , firms[firm3].getFinalDemandShare());}
                              altShares[firm3] = altShares[firm3] + mutFactor/((double) 10);
                              //if(round == 54){printf("firm %d alt share is %f \n", firm3, altShares[firm3]);}
                              if (altShares[firm3] < 0) {++negCount;}
                              //if(round == 54) {printf("negCount is %d \m" , negCount);}
                         }    //end for 
                         //if(round == 54){printf("firm 2 is integer constrained \n");}
                    }         //end if mutFactor
               }              //end if integerCase 3
            
               if(integerCase == 4) { //both firm1 and firm2 are integer constrained
                    //bag this for now //add it later  ******
               }
            }  //end for loop over mutationPairs 
			
            //determine altUtility
            //double altUtility = 1.0;
            //if statement kills comparrison if any altShares went negative
            if (negCount == 0) {          
               altUtility = calcUtility(firms, wageBill, firmNum, altShares, testoutput, round, anotation, cesHedonics, cesHedonicsElastGoods, cesHedonicsElastChars,complementIntConstraintFactor);
               //if(round == 9999) {printf("in round 10000 negCount = 0 \n");}
               //if(round == 9999) {printf("in round 10000 alt utility is %f \n", altUtility );}
            }
            else {altUtility = utility;}
            //if(round == 9999) {printf("in round 10000 alt utility is %f \n", altUtility );}
						
            //switch to altShares (and update utility) if altUtility > utility
            if(altUtility >= utility) { //11/15/10 switched from > to <= for drift (see Miller)
            //firms[firm1].setFinalDemandShare(altShares[firm1]); //should do this indirectly via current? no
		    //firms[firm2].setFinalDemandShare(altShares[firm2]); //should do this indirectly via current? no
               for(j=0;j<firmNum;j++) {firms[j].setFinalDemandShare(altShares[j]);} //6/26/09 do for all, not just firm1 and firm2
		       utility = altUtility;
		       //printf("Share %f transfered from firm %d to firm %d in round %d\n", mutFactor, firm2 + 1, firm1 + 1 , round + 1);	
		       /*
		       if(firm1 == 5 || firm2 == 5) {
			      printf("Share updated for firms %d and %d in round %d \n", firm1 + 1, firm2 + 1 , round );
		          printf("New share for firm %d is %f \n", 5, firms[5].getFinalDemandShare());
		       }
		       */
		       //if(round == 9999) {printf("in round 10000 utility switched to %f \n", altUtility );}
            }  //end if altUtility > utility          
            //reset altShares -- matters for firms who are tested and not updated 
            //altShares[firm1] = firms[firm1].getFinalDemandShare();
            //altShares[firm2] = firms[firm2].getFinalDemandShare();
            for(j=0;j<firmNum;j++) {altShares[j] = firms[j].getFinalDemandShare();} //6/26/09 do for all, not just firm1 and firm2
         
		
        }		//end mutation loop over search trials	     	
    }			//end search 
	
	delete[] shares; //8/2/09
    shares = NULL;  //8/2/09
    delete[] altShares; //8/2/09
    altShares = NULL; //8/2/09   
	return utility;    //added 6/02/09

}				//end doConsumerSearch

				
//sell C goods and do GDP accounting //8/2/08 take out reference in &wageBill //6/8/09 add nomGDP, realGDP, gdpDeflator
    double doFinalSales(firm firms[], double wageBill, const int firmNum, double rpGain, 
             /*double &totDeficit, double &less, double &more, double fixedNominalTransfer,*/ 
             std::ofstream &testoutput, int round, bool anotation, bool altPriceIndex,
             double &nomGDP, double &realGDP, double &gdpDeflator) {
    int i;
    double priceSum, share, totQuant, totNomSales, totRealSales, priceIndex;
    priceSum = 0.0;
    totQuant = 0.0;
    totNomSales = 0.0; //added 6/8/09
    totRealSales = 0.0; //added 6/8/09
    priceIndex = 0.0; //added 6/8/09
    //less = more = 0.0;
        
	for(i = 0; i < firmNum; i++) {
         double revenue, unitCost;
         firm current;
         current = firms[i];
         revenue = 0.0;
         
         unitCost = current.getWage()/current.getTechEff();
         share = current.getFinalDemandShare(); //7/30/08
		 
         current.setFinalDemand(share * wageBill); //actual final demand //7/30/08 explicitly created actual final demand rather than using updated expectedFinalDemand
		 //current.setExptdFinalDemand(share * wageBill);  //update expected to actual nominal demand //7/30/08      
         if(anotation && i==5) { testoutput << "firm " << i + 1 << " has actual nominal final demand of $" <<  current.getExptdFinalDemand() << " and thus real final demand of " <<  current.getExptdFinalDemand()/current.getPrice() << " units" << "\n"; } 

         if(current.getFinalDemand()/current.getPrice() >= current.getFinalProduction()) { //7/30/08
                revenue += current.getFinalProduction()*current.getPrice();
                if(anotation && i==5){
                     //testoutput << "supply is less than actual final demand " << "\n"; 
                     testoutput << "firm " << i + 1 << " sells " << current.getFinalProduction() << " units of final good" << "\n"; 
                 }
         }
         else {
                revenue +=current.getFinalDemand(); //7/30/08
                //if(i==3) { testoutput << "supply is greater than actual final demand " << "\n"; }
                if(anotation && i==5) { testoutput << "firm " << i + 1 << " sells " << current.getFinalDemand()/current.getPrice() << " units of final good" << "\n"; } //7/30/08
         }
         if(anotation && i==5){testoutput << "revenues are " <<  revenue << "\n"; }
         
         current.setCapital(current.getCapital() + revenue);
		 current.setProfit(current.getProfit() + revenue); //3/22/10
         if(anotation && i==5){testoutput << "firm " << i+ 1 << " now has capital of " << current.getCapital() << "\n"; }  
    
         if(current.getFinalProduction() > current.getFinalDemand()/current.getPrice()) {  //7/30/08
                totQuant += current.getFinalDemand()/current.getPrice();    //unadjusted for quality //7/30/08
                totNomSales += current.getFinalDemand(); //added 6/8/09 for nom gdp
                totRealSales += current.getFinalDemand() * (current.getPrice0()/current.getPrice()); //added 6/8/09 for real gdp
         }
         else {
                totQuant += current.getFinalProduction();     //unadjusted for quality 
                totNomSales += current.getFinalProduction()*current.getPrice(); //added 6/8/09 for nom gdp
                totRealSales += current.getFinalProduction()* current.getPrice0(); //added 6/8/09 for real gdp
         }         
         priceIndex += (current.getPrice()/current.getPrice0())* current.getFinalDemandShare(); //added 6/8/09 could consider using actual sales or production // oops -- this is using nom share not real share
		 current.setExptdFinalDemand(current.getFinalDemand());  //update expected to actual nominal demand //7/30/08         
		 firms[i] = current;
         /*
         if(i == 0) printf("%lf", current.getExptdDem());
         if(round == 5 && i==5) printf("current price is %f \n", current.getPrice());
         if(round == 5 && i==5) printf("initial price is %f \n", current.getPrice0());
         if(round == 5 && i==5) printf("current demand share is %f \n", current.getFinalDemandShare());
         if(round == 5 && i==5) printf("price index is %f \n", priceIndex);
         if(round == 5 && i==10) printf("price index is %f \n", priceIndex);
         */
		 double rp = 0.0; //3/22/10
		 rp = (1-rpGain) * firms[i].getRecentProfits() + rpGain * firms[i].getProfit(); //3/22/10
		 firms[i].setRecentProfits(rp); //3/22/10
    }
    if(altPriceIndex){
         //this is for alt measure using current nominal shares as weights in price index
         nomGDP = totNomSales; //added 6/8/09
         gdpDeflator = priceIndex; //added 6/8/09
         realGDP = nomGDP/gdpDeflator; //added 6/8/09
    }
    else {
         //this is for std real gdp and gdp deflator measures
         nomGDP = totNomSales; //added 6/8/09
         realGDP = totRealSales; //added 6/8/09
         gdpDeflator = nomGDP/realGDP; //added 6/8/09
    }
    
    return totQuant;
}

//Returns a random number between 0-1 according to a uniform dist
double randNumUni() {
    return (1 - (double) rand() / ((double) RAND_MAX + 1)); 
}

//Returns a random number according to N(0,1) dist
double randNumNorm() {
    double x, y, ans;
    x = randNumUni();
    y = randNumUni();
    ans = (pow(((-2.0)*log(x)) , 0.5)*cos((2.0*3.14159)*y));   //M_PI
    return ans;
}

//Alters labor efficiency of firms stochastically
double updateTechEff(firm firms[], const int firmNum, std::ofstream &testoutput, 
       int &round, double &avTechEff, double &strtTech, bool anotation, double probEffShock) {
    int i;
    double totTech,  minTechEff,  strtTechEff; 
    totTech = minTechEff = 0.0;
    strtTechEff = 0;
              
    for(i = 0; i < firmNum; i++) {
         firm current;
         double change, temp;
         current = firms[i];
         change = 1.0;
         if(randNumUni() >= 1 - probEffShock && round >=3) { //default is 0.1
		 //if(randNumUni() >= 0.5 && round == 3) { //for shocks isolated in one period 
		 //if(randNumUni() >= 0.5 && round % 10 == 0 && round > 0) { //for shocks every 10 periods
		 //if(randNumUni() >= 0.1 && round == 3 && i == 5) { //for shocks isolated in one period and one firm
		 //if(randNumUni() >= 2.0 && round >=3) { //suppress shocks
		       change = 1.00 + (randNumNorm()*current.getEffStdDev()); //default
		       //change = 1.5; //for large isolated positive shock // remove this and restore the deafult after testing 7/2/08
               if (change <= 0.1) { //keep techEff positive
                   change = 0.1;
                   testoutput << " change less than 0.1 " << "\n";
               }
               current.setTechEff((current.getTechEff())*change);
			   firms[i] = current;
			   //testoutput << "For agent " << i+1 << " ";
               //testoutput << "A inovation is " << change << " ";
               //testoutput << "techEff is " << current.getTechEff() << "\n";
               
   		 }
         if (round == 3 && i == 5 && anotation) { printf( "A shock is  %f\n", change );}
         if(i == 5 && anotation) {testoutput << "A shock factor for firm " << i+1 << " is " << change << "\n"; }
         
         temp = current.getTechEff();
         totTech += temp;
         if(minTechEff == 0)
                minTechEff = temp;
         else if(minTechEff > temp)
                minTechEff = temp; 
    }
     
    avTechEff = totTech/((double)firmNum);
    //strtTech set to avg for now for record -- should remove as all done in distFund
    strtTech = avTechEff;
    strtTechEff = strtTech;
    return strtTechEff;     
}

//Alters labor efficiency of firms stochastically for representative agent/common shock case
double updateTechEffCommonShock(firm firms[], const int firmNum, std::ofstream &testoutput, 
       int &round, double &avTechEff, double &strtTech, bool anotation) {
    int i;
    double totTech,  minTechEff,  strtTechEff, change; //moved change here for common shock
    totTech = minTechEff = 0.0;
    strtTechEff = 0;
    change = 1.0;
    
    //if(randNumUni() >= 0.1)  // moved this here for common shock
    //if(round >= 3) { 
    if(round == 5) {
    change = 1.00 + (randNumNorm()*(firms[0]).getEffStdDev()); 
    if (change <= 0.1)  
         change = 0.1;
    }        
    if(anotation) {testoutput << "common A shock factor is " << change << "\n"; }
                   
    for(i = 0; i < firmNum; i++) {
         firm current;
         double temp;
         current = firms[i];
         current.setTechEff((current.getTechEff())* change);
         firms[i] = current;
         //testoutput << change << "\n";
         //testoutput << current.getTechEff() << "\n";
         temp = current.getTechEff();
         totTech += temp;
         if(minTechEff == 0)
                minTechEff = temp;
         else if(minTechEff > temp)
                minTechEff = temp; 
    }
     
    avTechEff = totTech/((double)firmNum);
    //strtTech set to avg for now for record -- should remove as all done in distFund
    strtTech = avTechEff;
    strtTechEff = strtTech;
    //strtTechEff = avTechEff - ((avTechEff-minTechEff)/2);
    return strtTechEff;     
}

//removed legacy updateQual and updateQualCommonShock 8/31/10

//exogenous product innovation -- update hedonic qualities of firms' products
void updateHedonicQual(firm firms[], const int firmNum, std::ofstream &testoutput, int round, double probInnovate, double probUpTick, double probDownTick, bool anotation) {
    int i,j,k;
            
    for(i = 0; i < firmNum; i++) {
         //firm current;
         int value; 
         if(randNumUni() >= 1 - probInnovate  && round >= 3) { 
	     //if(randNumUni() >= 1 - probInnovate && round == 3) { //for shocks isolated in one round
	     //if(randNumUni() >= 0.0 && round == 3 && i == 5) { //for shocks isolated in one round and one firm
         //if(randNumUni() >= 2 && round >= 3) { //suppress shocks
			for(j=0;j<numHedonicElements;j++) {
				value = firms[i].getHedonicQualityElementJ(j);
				if(value > 0 || randNumUni() > 1- 10.0 * probUpTick) {
					if(randNumUni() >= 1 - probUpTick) {
					firms[i].setHedonicQualityElementJ(j,value + 1);
					}
                }
				if(randNumUni() >= 1 - probDownTick && value > 0) {
					firms[i].setHedonicQualityElementJ(j,value - 1);
				 }                                          //end if
			}                                               //end for
			
			//now do for complements //7/19/09 not working correctly //must have fixed aug 2, as now tests correctly 3/19/10
			for(k=0;k<maxNumComplements;k++) {
				for(j=0;j<numHedonicElements;j++) {
					value = firms[i].getComplementaryHedonicElementKJ(k,j);
					if(value > 0 || randNumUni() > 1- 10.0 * probUpTick) {
						if(randNumUni() >= 1 - probUpTick) {
						firms[i].setComplementaryHedonicElementKJ(k,j,value + 1);
						//if(i==1) printf("firm %d updates complementary element ( %d , %d ) to %d \n", i,k,j, firms[i].getComplementaryHedonicElementKJ(k,j)); //3/19/10
						}
					}
					if(randNumUni() >= 1 - probDownTick && value > 0) {
						firms[i].setComplementaryHedonicElementKJ(k,j,value - 1);
						//if(i==1) printf("firm %d updates complementary element ( %d , %d ) to %d \n", i,k,j, firms[i].getComplementaryHedonicElementKJ(k,j)); //3/19/10
						}                                      //end if
				}                                              //end for
			}												   //end for
			
         }                                                     //end if
         //if(i==5) current.setHedonicQuality0(7); //7/15/08 test
		 //if(i==5) {printf("hedonic quality 1 of firm 6 is %d \n", current.getHedonicQuality0());} //7/15/08 test  
    }                                                          //end for
    
    //removed return strtQual 8/31/10
}

//endogenous product innovation -- update hedonic qualities of firms' products for firms that are elibible to innovate conditional on recent RandD investment status
void doEndogProductInnovation(firm firms[], const int firmNum, std::ofstream &testoutput, int round, double probInnovate, double probUpTick, double probDownTick, bool multiplicativeMutation, double incrementRate, bool anotation) { //added incrementRate 7-11-11
    int i,j,k;        
    for(i = 0; i < firmNum; i++) {
         //firm current;
         int value; 
	 //new increment terms to allow additive or multiplicative mutation 6-9-11
	 double inc1, inc2, inc3; //incrementRate //increment rate is now declared in main
	 inc1 = 0.0; inc2 = 0.0; inc3 = 0.0;
	 int increment = 1;
	 //incrementRate=0.1;	//0.5 for testing in June/July 2011, somewhat extreem // but note that this won't kick in until char value > 1/incrementRate
		
	 if(randNumUni() >= 1 - probInnovate && randNumUni() <= firms[i].getRecentRandDInvestment()  && round >= 3) { //8/31/10 tied (stochastically) to recent rather than (deterministically to) current R&D investment
	 //if(randNumUni() >= 1 - probInnovate && firms[i].getRandDInvestment() && round == 3) { //for shocks isolated in one round
	 //if(randNumUni() >= 0.0 && round == 3 && firms[i].getRandDInvestment() && i == 5) { //for shocks isolated in one round and one firm
         //if(randNumUni() >= 2 && firms[i].getRandDInvestment() && round >= 3) { //suppress shocks

	//first do for base characteristics	
	for(j=0;j<numHedonicElements;j++) {
		value = firms[i].getHedonicQualityElementJ(j);
		// additive or multiple increment new 6-9-11
		inc1 = incrementRate * ((double) firms[i].getHedonicQualityElementJ(j)); //multiplicative increment
	 	inc2 = floor(inc1); // still integer constrianed mutation
	 	if(inc2 > 1.0) {inc3 = inc2;}
	 	else {inc3 = 1.0;} // but now use increment of 1 if mult increment below 2, else use mult increment
	 	//inc3 = max(inc2, 1.0);
	 	if (multiplicativeMutation) {increment = (int) inc3;} // if multiplicativeMutation turned on, then use this
	 	else {increment = 1;} // else use additive increment 
		// end setting up increment 6-9-11
		if(value > 0 || randNumUni() > 1- 10.0 * probUpTick) { // this looks like the weak preferential attachment ??? question 6-9-11 ***
			if(randNumUni() >= 1 - probUpTick) {
				firms[i].setHedonicQualityElementJ(j,value + increment); //6-9-11 
				//firms[i].setHedonicQualityElementJ(j,value + 1);
			}
                }
		if(randNumUni() >= 1 - probDownTick && value > 0) {
			//firms[i].setHedonicQualityElementJ(j,value - 1);
			firms[i].setHedonicQualityElementJ(j,value - increment); //6-9-11
		}                                          //end if
	 }                                                   //end for
			
	//now do for complements //7/19/09 fixed aug 2, tests correctly 3/19/10
	for(k=0;k<maxNumComplements;k++) {
		for(j=0;j<numHedonicElements;j++) {
			value = firms[i].getComplementaryHedonicElementKJ(k,j);
			// increment setup added 6-9-11
			inc1 = incrementRate * ((double) firms[i].getComplementaryHedonicElementKJ(k,j));
	 		inc2 = floor(inc1);
	 		if(inc2 > 1.0) {inc3 = inc2;}
	 		else {inc3 = 1.0;}
	 		//inc3 = max(inc2, 1.0);
	 		if (multiplicativeMutation) {increment = (int) inc3;}
	 		else {increment = 1;}
			// end increment setup 6-9-11
			if(value > 0 || randNumUni() > 1- 10.0 * probUpTick) {
				if(randNumUni() >= 1 - probUpTick) {
					//firms[i].setComplementaryHedonicElementKJ(k,j,value + 1); //just additive
					firms[i].setComplementaryHedonicElementKJ(k,j,value + increment); //increment is additive or multiplicative 6-9-11
					//if(i==1) printf("firm %d updates complementary element ( %d , %d ) to %d \n", i,k,j, firms[i].getComplementaryHedonicElementKJ(k,j)); //3/19/10
				}
			}
			if(randNumUni() >= 1 - probDownTick && value > 0) {
				//firms[i].setComplementaryHedonicElementKJ(k,j,value - 1);
				firms[i].setComplementaryHedonicElementKJ(k,j,value - increment); //6-9-11
				//if(i==1) printf("firm %d updates complementary element ( %d , %d ) to %d \n", i,k,j, firms[i].getComplementaryHedonicElementKJ(k,j)); //3/19/10
			}                                      //end if
		}                                              //end for
	}												   //end for	
        }                                                     //end if
	//if(i==5) current.setHedonicQuality0(7); //7/15/08 test
	//if(i==5) {printf("hedonic quality 1 of firm 6 is %d \n", current.getHedonicQuality0());} //7/15/08 test  
		 
    }                                                          //end for    
}

//Update R&d investment status -- firms choose whether or not to invest in R&D via social learning with individual sampling of other firms, plus random mutation plus conditional on working capital  
void updateRandDInvestmentStatus(firm firms[], const int firmNum, double intensityOfChoice, double probRandDInvestMutation, bool intermediateGoods, double overHeadL, double overHeadRandD, double intPriceDiscount, std::ofstream &testoutput, int round, bool anotation) { //3/21/10
    int i,j;
	int firm1 = 0;
	int firm2 = 0;
		
	//firm i searches for two other firms, one with more and one will less recent RandD investment than i. Switches own behavior depending on relative profits of these two.
	for(i = 0; i<firmNum; i++) {
		int maxCompInnov = 5; //max number of comparison firms to search over // should put this in main // 1
		//firms[i].setProfit(0.0);
		//double cp = 0.0; //current profit
		//search for a firm1 with greater recent RandD investment than firm i
		firm1 = rand() % firmNum;
		j = 0;
		while(firms[firm1].getRecentRandDInvestment() <= firms[i].getRecentRandDInvestment() && j<maxCompInnov) {
			firm1 = rand() % firmNum;
			j++;
		}
		//if can't find such a firm, set firm1 to firm i
		if(j == maxCompInnov) {firm1 = i;}
		
		//search for a firm2 with less innovation than firm i
		firm2 = rand() % firmNum;
		j = 0;
		while(firms[firm2].getRecentRandDInvestment() >= firms[i].getRecentRandDInvestment() && j<maxCompInnov) {
			firm2 = rand() % firmNum;
			j++;
		}
		//if can't find such a firm, set firm2 to firm i
		if(j == maxCompInnov) {firm2 = i;}
		
		//imitate the firm with the higher recent profit -- if that recent profit is greater than own
		if(firms[i].getRecentProfits() < firms[firm1].getRecentProfits() || firms[i].getRecentProfits() < firms[firm2].getRecentProfits()) {
			if(firms[firm1].getRecentProfits() > firms[firm2].getRecentProfits()) {
				firms[i].setRandDInvestment(firms[firm1].getRandDInvestment());
			}
			if(firms[firm2].getRecentProfits() > firms[firm1].getRecentProfits()) {
				firms[i].setRandDInvestment(firms[firm2].getRandDInvestment());
			}	
			if(i==4){
				//printf("firm %d has immitated innovation of another firm in round %d \n",i,round); 
				//printf("new innovation status is %f \n", firms[i].getRandDInvestment()); 
			} //3/24/10 testing
		}		//end if
		
		//add some randomness //3/22/10
		//double probRandInnovFlip = 0.01; //0.01 //should put this in main
		bool bb = firms[i].getRandDInvestment();
		if(randNumUni() > 1 - probRandDInvestMutation) { //0.01
			firms[i].setRandDInvestment(!bb);
			//if(i==4){printf("firm %d has random innovation switch in round %d to %d \n",i,round,firms[i].getRandDInvestment());} //3/24/10 testing	
		} 
		
        //  updating of recentRandDInvestment, count of firms investing, and investment cost accounting moved to separate routine 8/31/10 
		
		//turn off RandD invesetment if working capital too low
	   double expectedCost, ep, mlc, igc;
       firm current, prev; //just account for input demand not supply
       current = firms[i];
       if(i == 0) prev = firms[firmNum - 1];
       else prev = firms[i - 1];
       ep = current.getExptdFinalDemand()/current.getPrice(); //expected production
       mlc = current.getWage()/current.getTechEff();          //marginal labor cost
       igc = current.getIntGoodOrder()*prev.getPrice()*intPriceDiscount;  //expected intermediate good purchase 
       if(intermediateGoods) expectedCost = ep * mlc + igc + overHeadL + overHeadRandD; //expected costs this period with RandD
       else expectedCost = ep * mlc + overHeadL + overHeadRandD;                  //expected costs this period with RandD
       if(current.getCapital() < 2*expectedCost)  current.setRandDInvestment(false);
       firms[i] = current;    
    		
	}			//end for
}				//end updateEndogenousInnovation

//Update R&D investment status -- firms choose whether or not to invest in R&D via social learning by quasi global discrete choice, plus random mutation plus conditional on working capital //7/10
//firms who are using strategy with lower average profits switch with probability from logistic discrete choics
void updateRandDInvestmentStatusDC(firm firms[], const int firmNum, double intensityOfChoice, double probRandDInvestMutation, bool intermediateGoods, double overHeadL, double overHeadRandD, double intPriceDiscount, std::ofstream &testoutput, int round, bool anotation) { //3/21/10

    int i,j;
	double medRecentRandDInvestment = 0.0;
	double avgRecentProfitAboveMed = 0.0;
	double avgRecentProfitBelowMed = 0; 
	double discChoiceProb = 0.0; //this is the logistic prob for above med 
	//double intensityOfChoice = 0.2; // should be in main **  //0.2 //moved to main 8/31/10
	int numAboveMed = 0;
	int numBelowMed = 0;
	
	//calc median (or average) recentInnoation (should be median -- but for now using average **)
	for(i = 0; i<firmNum; i++) {medRecentRandDInvestment += firms[i].getRecentRandDInvestment();}
	medRecentRandDInvestment = medRecentRandDInvestment/((double) firmNum);	
	
	//calc average recentProfits for firms above medRecentRandDInvestment
	for(i = 0; i<firmNum; i++) {
		if (firms[i].getRecentRandDInvestment() > medRecentRandDInvestment) {
			avgRecentProfitAboveMed += firms[i].getRecentProfits();
			numAboveMed++;
		}
	}
	if(numAboveMed > 0) {avgRecentProfitAboveMed = avgRecentProfitAboveMed/((double) numAboveMed);}
	
	//calc average recentProfits for firms below medRecentRandDInvestment
	for(i = 0; i<firmNum; i++) {
		if (firms[i].getRecentRandDInvestment() < medRecentRandDInvestment) {
			avgRecentProfitBelowMed += firms[i].getRecentProfits();
			numBelowMed++;
		}
	}
	if (numBelowMed > 0) {avgRecentProfitBelowMed = avgRecentProfitBelowMed/((double) numBelowMed);}
	
	//calc discChoiceProbInnovate here -- disc choice prob with above med recent profit on top	
	if (numAboveMed > 0 && numBelowMed > 0) {
        discChoiceProb = exp(intensityOfChoice * avgRecentProfitAboveMed) / ( 
                      exp(intensityOfChoice * avgRecentProfitAboveMed) + exp(intensityOfChoice * avgRecentProfitBelowMed));
    }
		
	//now switch those on lower profit end with probability discChoiceProbInnovate or 1-discChoicProbInnovate
	if (numAboveMed > 0 && numBelowMed > 0) {
        if(avgRecentProfitAboveMed > avgRecentProfitBelowMed) {
		     for(i = 0; i<firmNum; i++) {
                   bool bb = firms[i].getRandDInvestment();
                   if(firms[i].getRecentRandDInvestment() < medRecentRandDInvestment) {
                        if(randNumUni() > (2 - 2 * discChoiceProb)) {
                        firms[i].setRandDInvestment(true);
              			//if(i==4){printf("firm %d has random innovation switch in round %d to %d \n",i,round,firms[i].getRandDInvestment());} //3/24/10 testing	
		                }
                   }
              } 
        }
        if(avgRecentProfitAboveMed < avgRecentProfitBelowMed) {
		     for(i = 0; i<firmNum; i++) {
                   bool bb = firms[i].getRandDInvestment();
                   if(firms[i].getRecentRandDInvestment() > medRecentRandDInvestment) {
                        if(randNumUni() > (2 * discChoiceProb)) {
                        firms[i].setRandDInvestment(false);
              			//if(i==4){printf("firm %d has random innovation switch in round %d to %d \n",i,round,firms[i].getRandDInvestment());} //3/24/10 testing	
		                }
                   }
              } 
        }            
	}
	
	//add some random choice turn off RandD invesetment if working capital too low
    for(i = 0; i<firmNum; i++) {
		
	   //add some randomness //3/22/10
	   bool bb = firms[i].getRandDInvestment();
	   if(randNumUni() > 1 - probRandDInvestMutation) { 
			firms[i].setRandDInvestment(!bb);
			//if(i==4){printf("firm %d has random innovation switch in round %d to %d \n",i,round,firms[i].getRandDInvestment());} //3/24/10 testing	
	   } 
		
       //turn off RandD invesetment if working capital too low	//10-6-10
	   double expectedCost, ep, mlc, igc;
       firm current, prev; //just account for input demand not supply
       current = firms[i];
       if(i == 0) prev = firms[firmNum - 1];
       else prev = firms[i - 1];
       ep = current.getExptdFinalDemand()/current.getPrice(); //expected production
       mlc = current.getWage()/current.getTechEff();          //marginal labor cost
       igc = current.getIntGoodOrder()*prev.getPrice()*intPriceDiscount;  //expected intermediate good purchase 
       if(intermediateGoods) expectedCost = ep * mlc + igc + overHeadL + overHeadRandD; //expected costs this period with RandD
       else expectedCost = ep * mlc + overHeadL + overHeadRandD;                  //expected costs this period with RandD
       if(current.getCapital() < 2*expectedCost)  current.setRandDInvestment(false);
       firms[i] = current;    
		
	}			//end for
	
    //  updating of recentRandDInvestment, count of firms investing, and investment cost accounting moved to separate routine 8/31/10 

}				//end updateEndogenousInnovation

//increment wageBill and firm profits for fixed overhead labor and current RandD overhead labor and increment recentRandDInvestment //10-7-10
void doOHandRandDAccounting(firm firms[], const int firmNum, double riGain, double overHeadRandD, double overHeadL, double &wageBill, int &numRandD, std::ofstream &testoutput, int round, bool anotation) { //3/21/10  
        int i;
        for(i = 0; i<firmNum; i++) {
            //firms[i].setProfit(0.0);
		    //double cp = 0.0; //current profit
		    
            //all firms incur fixed overHead labor cost // 10/4/10
		    firms[i].setProfit(firms[i].getProfit() - overHeadL); //10-6-10
		    firms[i].setCapital(firms[i].getCapital() - overHeadL); //6-1-11
		    wageBill += overHeadL;
            
            //firms with innovation status true incur labor cost and update count of firms innovating
		    if(firms[i].getRandDInvestment()) { //3/23/10
			    firms[i].setProfit(firms[i].getProfit() - overHeadRandD); //10-6-10
			    firms[i].setCapital(firms[i].getCapital() - overHeadRandD); //6-1-11
			    wageBill += overHeadRandD;
		   	    numRandD++; //7/9/10
           }  
           
           //update recentRandDInvestment with constant gain riGain
		    double ri = (1 - riGain) * firms[i].getRecentRandDInvestment() + riGain * firms[i].getRandDInvestment();
		    firms[i].setRecentRandDInvestment(ri); 
		    
        }   //end for
}           //end doRandDAccounting



//restart when capital becomes negative and also randomly -- for representative agent/common shocks case // need to redo this for hedonics ****
int doRestartsCommonShock(firm firms[], const int firmNum, double strtTech, 
        double &wageBill, double elasDem, /*double fixedNominalTransfer,*/ 
        /*double inputFactor,*/ double overHeadG, double intPriceDiscount, bool imitation, double probRandomRestart) {
    
    firm current, prev, comparison; 
    int i, j, rndrestrt; 
    rndrestrt = 0;
    
    /* // need to redo this for hedonics ****
    
    for(i = 0; i < firmNum; i++) {
         double price;
         current = firms[i];
         if(i == 0)
                prev = firms[firmNum - 1];
         else
                prev = firms[i - 1];
         
         j = rand() % firmNum;   
         comparison = firms[j];  
         
         //if(current.getCapital() < 0.0  ) {  //without random failure
         if(current.getCapital() < 0.0  || randNumUni() < probRandomRestart) { //with random failure
                firm newFirm;
                if(imitation){
                     newFirm.setTechEff(comparison.getTechEff()); //restart gets TechEff of a ranomly chosen other firm
				     newFirm.setQual(comparison.getQual()); //restart gets Quality of the ranomly chosen other firm
                }
                else {
                     newFirm.setQual(1.0);
                     newFirm.setTechEff(1.0);
                }
                //price = (elasDem/(elasDem - 1.0))*(newFirm.getWage()/newFirm.getTechEff() + inputFactor*prev.getPrice()*intPriceDiscount); //for v2.3
                price = newFirm.getMarkup()*(newFirm.getWage()/newFirm.getTechEff() + inputFactor*prev.getPrice()*intPriceDiscount); //9/9/10
                //price = (elasDem/(elasDem - 1.0))* (newFirm.getWage()/newFirm.getTechEff());
                newFirm.setPrice(price);
                newFirm.setExptdFinalDemand(wageBill/ ((double)firmNum));
                prev.setExptdIntermedDemand(overHeadG + inputFactor*(wageBill/ (((double)firmNum)*newFirm.getPrice())));//added overHeadG
                newFirm.setExptdIntermedDemand(current.getExptdIntermedDemand());
                
         
                current = newFirm;
                //count[i]++;
                rndrestrt++;
         }
         if(i == 0)
                firms[firmNum - 1] = prev;
         else
                firms[i - 1] = prev;

         firms[i] = current;
    }
    
    */
    
    return rndrestrt;
}

/*
//replaced this with more parsimonious coding 6-27-11
//restart firms when capital becomes negative and also randomly -- here for hedonic case //8/12/08
int doRestartsHedonics(firm firms[], const int firmNum, double strtTech, 
        double &wageBill, double elasDem, double overHeadG, double intPriceDiscount, bool imitation, double probRandomRestart,
		double probIntegerConstrained, double probComplements) {
    firm current, prev, comparison; 
    int i, j, k, rndrestrt; 
    rndrestrt = 0;
    
    for(i = 0; i < firmNum; i++) {
         double price, share;
         current = firms[i];
         if(i == 0)
                prev = firms[firmNum - 1];
         else
                prev = firms[i - 1];
         
         j = rand() % firmNum;   
         comparison = firms[j]; 
         
         //printf("%lf \n", current.getExptdFinalDemand());
                        
         //if(current.getCapital() < 0.0 ) { //without random failure 
         if(current.getCapital() < 0.0  || randNumUni() < probRandomRestart) { //with random failure 0.0005
                firm newFirm;
				int value;
                
				if(i==5) {
					printf("firm 6 has restarted \n" );
				}
    
                if(imitation  && comparison.getTechEff() >= 0.5) { //combined 7/29/09
                     
					newFirm.setTechEff(comparison.getTechEff()); //restart gets TechEff of a ranomly chosen other firm
					for(j=0;j<numHedonicElements;j++) {
						value = comparison.getHedonicQualityElementJ(j);
						newFirm.setHedonicQualityElementJ(j, value);
					}
					newFirm.setIntegerConstrained(comparison.getIntegerConstrained());
					newFirm.setHasComplements(comparison.getHasComplements());
					newFirm.setNumComplements(comparison.getNumComplements());
					for(k=0;k<maxNumComplements;k++) {newFirm.setComplementaryProductK(k,comparison.getComplementaryProductK(k));} //7/3/09
					for(k=0;k<maxNumComplements;k++) {
						for(j=0;j<numHedonicElements;j++) {newFirm.setComplementaryHedonicElementKJ(k,j,comparison.getComplementaryHedonicElementKJ(k,j));}
					}
                     
				}	 
                else {
					//newFirm.setTechEff(strtTech);
					newFirm.setTechEff(1.0); //1.0
					//newFirm.setQual(strtTech);
					//newFirm.setQual(1.0); //1.0
					for (j=0; j<numHedonicElements; j++) {
                         if (randNumUni() > 1 - 0.1) {newFirm.setHedonicQualityElementJ(j,rand() % 2);}
                         else {newFirm.setHedonicQualityElementJ(j,0);}
					}
					if(randNumUni() > 1 - probIntegerConstrained) {newFirm.setIntegerConstrained(true);}
					for(k=0;k<maxNumComplements;k++) {newFirm.setComplementaryProductK(k,0);} //7/3/09
					for(k=0;k<maxNumComplements;k++) {
						for(j=0;j<numHedonicElements;j++) {newFirm.setComplementaryHedonicElementKJ(k,j,0);}
					}
					if(randNumUni() > 1 - probComplements) {
						newFirm.setHasComplements(true);
						newFirm.setNumComplements(rand() % maxNumComplements);
						for(k=0;k<maxNumComplements;k++) {newFirm.setComplementaryProductK(k,rand() % firmNum);}
						for(k=0;k<maxNumComplements;k++) {
							for(j=0;j<numHedonicElements;j++) {
								if(randNumUni() > 1 - 0.1) {newFirm.setComplementaryHedonicElementKJ(k,j,rand() % 2);} // random integer in {0,1}
								else {newFirm.setComplementaryHedonicElementKJ(k,j,0);}
							}
						}
					}
					
					   
                }
                
                price = newFirm.getMarkup()*(newFirm.getWage()/newFirm.getTechEff() + newFirm.getInputFactor()*prev.getPrice()*intPriceDiscount); //9/9/10
                newFirm.setPrice(price);
                newFirm.setPrice0(current.getPrice0()); //added   6/9/09
                //newFirm.setExptdFinalDemand(wageBill/ ((double)firmNum));
                //newFirm.setExptdFinalDemand(current.getExptdFinalDemand()); //4-20-07
                //newFirm.setExptdFinalDemand(comparison.getExptdFinalDemand()); //4-20-07
				share = current.getFinalDemandShare(); //8/12/08
				newFirm.setFinalDemandShare(share); //8/12/08
                newFirm.setExptdFinalDemand(share * wageBill); //4-20-07
                prev.setExptdIntermedDemand(overHeadG + newFirm.getInputFactor()*(wageBill/ (((double)firmNum)*newFirm.getPrice())));//added overHead // input factor now tied to firms
                newFirm.setExptdIntermedDemand(current.getExptdIntermedDemand());
				newFirm.setIntegerConstrained(current.getIntegerConstrained());
				
				current = newFirm;
                rndrestrt++;
                //printf(" firm replaced \n");
                //printf("%1f \n", share);
                //printf("%1f \n", current.getExptdFinalDemand());  
         }
         //printf("%1f \n", current.getExptdFinalDemand()); 
         //printf("%lf \n", current.getExptdFinalDemand());
         //printf("%1f \n", share);
         
         if(i == 0)
                firms[firmNum - 1] = prev;
         else
                firms[i - 1] = prev;
    
         firms[i] = current;
    }
    return rndrestrt;
}

*/

//restart firms when capital becomes negative and also randomly -- here for hedonic case //8/12/08  -- //dramatically simplified 6-27-11
int doRestartsHedonics(firm firms[], const int firmNum, double strtTech, 
        double &wageBill, double elasDem, /*double fixedNominalTransfer,*/ 
        /*double inputFactor,*/ double overHeadG, double intPriceDiscount, bool imitation, double probRandomRestart,
		double probIntegerConstrained, double probComplements) {
    firm current, prev, comparison; 
    int i, j, k, rndrestrt; 
    rndrestrt = 0;
    
    for(i = 0; i < firmNum; i++) {
         double price, share;
         current = firms[i];
         if(i == 0)
                prev = firms[firmNum - 1];
         else
                prev = firms[i - 1];
         
         j = rand() % firmNum;   
         comparison = firms[j]; 
         
         //printf("%lf \n", current.getExptdFinalDemand());
                        
         //if(current.getCapital() < 0.0 ) { //without random failure 
         if(current.getCapital() < 0.0  || randNumUni() < probRandomRestart) { //with random failure 0.0005
                firm newFirm;
				//int value;
                
				if(i==5) {
					printf("firm 6 has restarted \n" );
				}
    
                if(imitation  && comparison.getTechEff() >= 0.5) { //combined 7/29/09
					newFirm = comparison;
				}		//this is new 6-27-11 //cut out all of the specific copying
                     
					 
                else {
					//newFirm.setTechEff(strtTech);
					newFirm.setTechEff(1.0); //1.0
					//newFirm.setQual(strtTech);
					//newFirm.setQual(1.0); //1.0
					for (j=0; j<numHedonicElements; j++) {
                         if (randNumUni() > 1 - 0.1) {newFirm.setHedonicQualityElementJ(j,rand() % 2);}
                         else {newFirm.setHedonicQualityElementJ(j,0);}
					}
					if(randNumUni() > 1 - probIntegerConstrained) {newFirm.setIntegerConstrained(true);}
					for(k=0;k<maxNumComplements;k++) {newFirm.setComplementaryProductK(k,0);} //7/3/09
					for(k=0;k<maxNumComplements;k++) {
						for(j=0;j<numHedonicElements;j++) {newFirm.setComplementaryHedonicElementKJ(k,j,0);}
					}
					if(randNumUni() > 1 - probComplements) {
						newFirm.setHasComplements(true);
						newFirm.setNumComplements(rand() % maxNumComplements);
						for(k=0;k<maxNumComplements;k++) {newFirm.setComplementaryProductK(k,rand() % firmNum);}
						for(k=0;k<maxNumComplements;k++) {
							for(j=0;j<numHedonicElements;j++) {
								if(randNumUni() > 1 - 0.1) {newFirm.setComplementaryHedonicElementKJ(k,j,rand() % 2);} // random integer in {0,1}
								else {newFirm.setComplementaryHedonicElementKJ(k,j,0);}
							}
						}
					}
					
					   
                }
                
                price = newFirm.getMarkup()*(newFirm.getWage()/newFirm.getTechEff() + newFirm.getInputFactor()*prev.getPrice()*intPriceDiscount); //9/9/10
                newFirm.setPrice(price);
                newFirm.setPrice0(current.getPrice0()); //added   6/9/09
                //newFirm.setExptdFinalDemand(wageBill/ ((double)firmNum));
                //newFirm.setExptdFinalDemand(current.getExptdFinalDemand()); //4-20-07
                //newFirm.setExptdFinalDemand(comparison.getExptdFinalDemand()); //4-20-07
				share = current.getFinalDemandShare(); //8/12/08
				newFirm.setFinalDemandShare(share); //8/12/08
                newFirm.setExptdFinalDemand(share * wageBill); //4-20-07
                prev.setExptdIntermedDemand(overHeadG + newFirm.getInputFactor()*(wageBill/ (((double)firmNum)*newFirm.getPrice())));//added overHead // input factor now tied to firms
                newFirm.setExptdIntermedDemand(current.getExptdIntermedDemand());
				newFirm.setIntegerConstrained(current.getIntegerConstrained());
				newFirm.setCapital(100.0); //7-12-11
				newFirm.setRandDInvestment(current.getRandDInvestment()); //7-15-11
				newFirm.setRecentRandDInvestment(current.getRecentRandDInvestment());  //7-15-11
	            newFirm.setProfit(current.getProfit()); //7-15-11
                newFirm.setRecentProfits(current.getRecentProfits());  //7-15-11
				
				current = newFirm;
                rndrestrt++;
                //printf(" firm replaced \n");
                //printf("%1f \n", share);
                //printf("%1f \n", current.getExptdFinalDemand());  
         }
         //printf("%1f \n", current.getExptdFinalDemand()); 
         //printf("%lf \n", current.getExptdFinalDemand());
         //printf("%1f \n", share);
         
         if(i == 0)
                firms[firmNum - 1] = prev;
         else
                firms[i - 1] = prev;
    
         firms[i] = current;
    }
    return rndrestrt;
}


