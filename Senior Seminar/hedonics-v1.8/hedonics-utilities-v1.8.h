#ifndef UTILITIES_H
#define UTILITIES_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>

//Function Declarations

//initialize firms // moved from main 10-4-10
void initializeFirms(firm firms[], const int firmNum, int round, std::ofstream &testoutput, bool anotation, double probComplements, double probInnovate, double probIntegerConstrained, double intPriceDiscount);

//random number, uniform distribution on [0,1]
double randNumUni();

//N(0,1) random number
double randNumNorm();

//exogenous product innovation
void updateHedonicQual(firm firms[], const int firmNum, std::ofstream &testoutput, int round, double probInnovate, double probUpTick, double probDownTick, bool anotation);

//endogenous product innovation -- update firm's hedonic qualities conditional on recent R&D investment 
void doEndogProductInnovation(firm firms[], const int firmNum, std::ofstream &testoutput, int round, double probInnovate, double probUpTick, double probDownTick, bool multiplicativeMutation, double incrementRate, bool anotation); //added incrementRate 7-11-11

//R&D investment -- endogenous product innovation -- firms update current status by social learning with individual sampling of other firms
void updateRandDInvestmentStatus(firm firms[], const int firmNum, double intensityOfChoice, double probRandDInvestMutation, bool intermediateGoods, double overHeadL, double overHeadRandD, double intPriceDiscount, std::ofstream &testoutput, int round, bool anotation);

//R&D investment -- endogenous product innovation -- firms update current status by social learning with quasi global discrete choice
void updateRandDInvestmentStatusDC(firm firms[], const int firmNum, double intensityOfChoice, double probRandDInvestMutation, bool intermediateGoods, double overHeadL, double overHeadRandD, double intPriceDiscount, std::ofstream &testoutput, int round, bool anotation);

//OH and R&D accounting -- //increment wageBill and firm profits for fixed overhead labor and current RandD overhead labor and increment recentRandDInvestment //10-7-10
void doOHandRandDAccounting(firm firms[], const int firmNum, double riGain, double overHeadRandD, double overHeadL, double &wageBill, int &numRandD, std::ofstream &testoutput, int round, bool anotation);

//labor productivity
double updateTechEff(firm firms[], const int firmNum, std::ofstream &testoutput, int &round, double &avTechEff, double &strtTech, bool anotation, double probEffShock);

//labor productivity -- common shock case
double updateTechEffCommonShock(firm firms[], const int firmNum, std::ofstream &testoutput, int &round, double &avTechEff, double &strtTech, bool anotation);

//markup pricing (from CES demands)
void updatePrice(firm firms[], const int firmNum, /*double inputFactor,*/ std::ofstream &testoutput, bool anotation, double intPriceDiscount);

//production and intermediate sales //split up 10-6-10
//void doProduction(firm firms[], double &wageBill, const int firmNum, double &totDeficit, double &defMax, double overHeadG, std::ofstream &testoutput, int round, bool anotation, double intPriceDiscount);

//production and sale of intermediate goods
void doIntermediateGoods(firm firms[], double &wageBill, const int firmNum, double overHeadG, std::ofstream &testoutput, int round, bool anotation, double intPriceDiscount, bool intermediateGoods); 

//production of final (consumption) goods
void doProduction(firm firms[], double &wageBill, const int firmNum, double overHeadG, std::ofstream &testoutput, int round, bool anotation, double intPriceDiscount, bool intermediateGoods);

//utility -- calculate utility of representative consumer given a set of nominal firm shares in consumer spending //new 6/7/09
double calcUtility(firm firms[], double wageBill, const int firmNum, double shares[], std::ofstream &testoutput, int round, bool anotation, bool cesHedonics, double cesHedonicsElastGoods, double cesHedonicsElastChars, double complementIntConstraintFactor);

//consumer search -- set final goods demand shares //7/30/08 // return type changed to double 6/02/09
double doConsumerSearch(firm firms[], double wageBill, const int firmNum, std::ofstream &testoutput, int round, int numMutationPairs, int numSearchTrials, double mutScale, bool anotation, bool cesHedonics, double cesHedonicsElastGoods, double cesHedonicsElastChars, double complementIntConstraintFactor);

//final sales  //8/2/08 take out reference in &wageBill //6/8/09  add nomGDP realGDP gdpDeflator	       
double doFinalSales(firm firms[], double wageBill, const int firmNum, double rpGain, /*double &totDeficit, double &less, double &more, 
double fixedNominalTransfer,*/ std::ofstream &testoutput, int round, bool anotation, bool altPriceIndex, double &nomGDP, double &realGDP, double &gdpDeflator); 

//restarts -- for hedonics 
int doRestartsHedonics(firm firms[], const int firmNum, double strtTech, double &wageBill, double elasDem, /*double fixedNominalTransfer,*/ /*double inputFactor,*/ double overHeadG, double intPriceDiscount, bool imitation, double probRandomRestart, double probIntegerConstrained, double probComplements);

//restarts -- common shock case -- needs to be redone if used ***
int doRestartsCommonShock(firm firms[], const int firmNum, double strtTech, double &wageBill, double elasDem, /*double fixedNominalTransfer,*/ /*double inputFactor,*/ double overHeadG, double intPriceDiscount, bool imitation, double probRandomRestart); 

#endif
