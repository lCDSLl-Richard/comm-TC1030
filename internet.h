// =========================================================
// File: intenet.h
// Author: Ricardo Fernandez
// Date: 31/05/2022
// Description: Implementation of Internet sub-class
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
  const double LIMITGB = 10.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

InternetOperator::InternetOperator(int nId, double minCost, double messCost, double gbCost, int discount, OperatorType INTERNET):Operator(nId, minCost, messCost, gbCost, discount, INTERNET){}

InternetOperator::InternetOperator(const InternetOperator &other):Operator(other){}

double InternetOperator::calculateTalkingCost(int minute, int age){
  if(minute <= 0 || age <= 0){return 0;}
  double cost = minute*talkingCharge;
  if(minute < 2){
    cost = cost*(1-(double(discountRate)/100));
  }
  return cost;
}

double InternetOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId){
  if(quantity <= 0){return 0;}
  double cost = quantity*messageCost;
  if(quantity < 3){
    cost = cost*(1-(double(discountRate)/100));
  }
  return cost;
}

double InternetOperator::calculateNetworkCost(double amount){
  if(amount <= 0){return 0;}
  double cost = 0;
  if(amount+totalInternetUsage > LIMITGB){
    cost = (amount+totalInternetUsage-LIMITGB)*networkCharge;
  }
  return cost;
}

#endif
