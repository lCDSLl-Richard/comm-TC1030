// =========================================================
// File: operator.h
// Author: Ricardo Fernandez
// Date: 23/05/2022
// Description: Implementation of parent class operator.
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <sstream>
#include <iomanip>

typedef enum{VOX, INTERNET} OperatorType;

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingCharge() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  std::string toString() const;

  virtual double calculateTalkingCost(int, int) = 0;
  virtual double calculateMessageCost(int, int, int) = 0;
  virtual double calculateNetworkCost(double) = 0;
};

Operator::Operator(int nId, double talkCost, double messCost, double gbCost, int discount, OperatorType opType){
  id = nId;
  discountRate = discount;
  talkingCharge = talkCost;
  messageCost = messCost;
  networkCharge = gbCost;
  totalInternetUsage = 0;
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
  type = opType;
}

Operator::Operator(const Operator &other){
  id = other.id;
  discountRate = other.discountRate;
  talkingCharge = other.talkingCharge;
  messageCost = other.messCost;
  networkCharge = other.networkCharge;
  totalInternetUsage = other.totalInternetUsage;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  type = other.type;
}

int Operator::getId() const{
  return id;
}

int Operator::getDiscountRate() const{
  return discountRate;
}

double Operator::getTalkingCharge() const{
  return talkingCharge;
}

double Operator::getMessageCost() const{
  return messageCost;
}

double Operator::getNetworkCharge() const{
  return networkCharge;
}

int Operator::getTotalSpentTalkingTime() const{
  return totalSpentTalkingTime;
}

int Operator::getTotalMessageSent() const{
  return totalMessageSent;
}

double Operator::getTotalInternetUsage() const{
  return totalInternetUsage;
}

OperatorType Operator::getType() const{
  return type;
}

void Operator::addTalkingTime(int min){
  if (min < 0){return;}
  totalSpentTalkingTime =+ min;
}

void Operator::addTotalMessageSent(int quant){
  if (quant < 0){return;}
  totalMessageSent += quant;
}

void Operator::addTotalInternetUsage(double gbs){
  if (gbs < 0){return;}
  totalInternetUsage += gbs;
}

std::string Operator::toString() const{
  string info = printf("Operator #%d: %d %d %.2f", id, totalSpentTalkingTime, totalMessageSent, totalInternetUsage);

  return info;
}

#endif
