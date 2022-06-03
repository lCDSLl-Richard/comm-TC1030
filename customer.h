// =========================================================
// File: customer.h
// Author: Ricardo Fernandez
// Date: 31/05/2022
// Description: Implementation of class costumer
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

using namespace std;

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  string name;
  Operator *op;
  Bill *bill;

public:
  Customer(int, string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
  void pay(double);
};

Customer::Customer(int nId, string nName, int nAge, Operator *nOp, double creditLimit){
  bill = new Bill(creditLimit);
  op = nOp;
  id = nId;
  age = nAge;
  totalSpentTalkingTime = 0;
  totalMessageSent = 0;
  totalInternetUsage = 0;
  name = nName;
}

Customer::Customer(const Customer &other){
  id = other.id;
  age = other.age;
  totalSpentTalkingTime = other.totalSpentTalkingTime;
  totalMessageSent = other.totalMessageSent;
  totalInternetUsage = other.totalInternetUsage;
  name = other.name;
  op = other.op;
  bill = other.bill;
}

Customer::~Customer(){
  delete bill, op;
}

int Customer::getId() const{
  return id;
}

int Customer::getAge() const{
  return age;
}

int Customer::getTotalSpentTalkingTime() const{
  return totalSpentTalkingTime;
}

int Customer::getTotalMessageSent() const{
  return totalMessageSent;
}

double Customer::getTotalInternetUsage() const{
  return totalInternetUsage;
}

string Customer::getName() const{
  return name;
}

Operator* Customer::getOperator() const{
  return op;
}

Bill* Customer::getBill() const{
  return bill;
}

void Customer::setOperator(Operator* nOp){
  op = nOp;
}

string Customer::toString() const{
  stringstream info;

  info << fixed << setprecision(2);
  info << "Customer " << id << ": " << bill->getTotalMoneySpent() << " " << bill->getCurrentDebt();

  return info.str();
}
void Customer::talk(int minutes, Customer &other){
  if(minutes > 0 && id != other.id){
    double cost = op->calculateTalkingCost(minutes, age);
    if(bill->check(cost)){
      bill->add(cost);
      totalSpentTalkingTime += minutes;
      op->addTalkingTime(minutes);
      other.totalSpentTalkingTime += minutes;
      if(other.op->getId() != op->getId()){
        other.op->addTalkingTime(minutes);
      }
    }
  }
}

void Customer::message(int quantity, const Customer &other){
  if(quantity > 0 && id != other.id){
    double cost = op->calculateMessageCost(quantity, op->getId(), other.op->getId());
    if(bill->check(cost)){
      bill->add(cost);
      totalMessageSent += quantity;
      op->addTotalMessageSent(quantity);
    }
  }
}

void Customer::connection(double amount){
  if(amount > 0){
    double cost = op->calculateNetworkCost(amount);
    if(bill->check(cost)){
      bill->add(cost);
      totalInternetUsage += amount;
      op->addTotalInternetUsage(amount);
    }
  }
}

void Customer::pay(double amount){
  if(amount > 0){
    bill->pay(amount);
  }
}


#endif
