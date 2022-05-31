// =========================================================
// File: vox.h
// Author:
// Date:
// Description:
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

VoxOperator::VoxOperator(int nId, double minCost, double messCost, double gbCost, int per, OperatorType VOX):Operator(nId, minCost, messCost, gbCost, per, VOX){
}

VoxOperator::VoxOperator(const VoxOperator &other):Operator(other){
}

double VoxOperator::calculateTalkingCost(int minute, int age){
  if(minute <= 0 || age <= 0){return 0;}
  double cost = minute*talkingCharge;
  if(age < 18 || age > 65){
    cost = cost * (1-(double(discountRate)/100));
  }
  return cost;
}

double VoxOperator::calculateMessageCost(int quantity, int thisOpId, int otherOpId){
  if(quantity <= 0){return 0;}
  double cost = quantity * messageCost;
  if(thisOpId == otherOpId){
    cost = cost * (1-(double(discountRate)/100));
  }
  return cost;
}

double VoxOperator::calculateNetworkCost(double amount){
  if(amount > 0){
    return amount*networkCharge;
  }
  return 0;
}

#endif
