// =========================================================
// File: bill.h
// Author: Ricardo Fernandez
// Date: 21/05/2022
// Description: Declaration and implementation of bill class
// =========================================================

#ifndef BILL_H
#define BILL_H

class Bill {
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill&);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};

Bill::Bill(){
  limitAmount = 0;
  currentDebt = 0;
  totalMoneySpent = 0;
}

Bill::Bill(double limit){

  limitAmount = limit >= 0 ? limit : 0;
  currentDebt = 0;
  totalMoneySpent = 0;
}

Bill::Bill(const Bill &other){
  limitAmount = other.limitAmount;
  currentDebt = other.currentDebt;
  totalMoneySpent = other.totalMoneySpent;
}

double Bill::getLimitAmount() const{
  return limitAmount;
}

double Bill::getCurrentDebt() const{
  return currentDebt;
}

double Bill::getTotalMoneySpent() const{
  return totalMoneySpent;
}

void Bill::add(double amount){
  currentDebt += amount > 0 ? amount : 0;
}

void Bill::pay(double amount){
  if (amount > 0) {
    if (amount > currentDebt){
      totalMoneySpent += currentDebt;
      currentDebt = 0;
    }
    else{
      currentDebt -= amount;
      totalMoneySpent += amount;
    }
  }
}

void Bill::changeTheLimit(double limit){
  if (limit > 0 && limit >= currentDebt){
    limitAmount = limit;
  }
}

bool Bill::check(double amount) const{
  return amount+currentDebt <= limitAmount ? true : false;
}

#endif
