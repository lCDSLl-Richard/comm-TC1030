// =========================================================
// File: customer.h
// Author:
// Date:
// Description:
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  std::string name;
  Operator* op;
  Bill *bill;

public:
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);  
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  std::string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
  void pay(double);
};

Customer::Customer(int nId, std::string nName, int nAge, Operator *nOp, double creditLimit){
  Bill nBill(creditLimit);
  bill = &nBill;
  op = nOp;
  id = nId;
  age = nAge;
  totalSpentTalkingTime = op.getTotalSpentTalkingTime();
  totalMessageSent = op.getTotalMessageSent();
  totalInternetUsage = op.getTotalInternetUsage();
  name = nName;
}

Costumer::Costumer(const Costumer &other){
  id = other.id;
  age = other.age;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
  name = other.name;
  op = other.op;
  bill = other.bill;
}

Costumer::~Costumer(){}

int Costumer::getId() const{
  return id;
}

int Costumer::getAge() const{
  return age;
}

int Costumer::getTotalSpentTalkingTime() const{
  return totalSpentTalkingTime;
}

int Costumer::getTotalMessageSent() const{
  return totalMessageSent;
}

double Costumer::getTotalInternetUsage() const{
  return totalInternetUsage;
}

std::string Costumer::getName() const{
  return name;
}

Operator* Costumer::getOperator() const{
  return op;
}

Bill* Costumer::getBill() const{
  return bill;
}

void Costumer::setOperator(Operator* nOp){
  op = nOp;
}



#endif
