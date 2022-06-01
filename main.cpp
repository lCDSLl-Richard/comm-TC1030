// =========================================================
// File: main.cpp
// Author:
// Date:
// Description:
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char* argv[]) {

  ifstream inputFile;
  ofstream outputFile;

  if (argc != 3) {
    cout << "usage: " << argv[0] << " input_file output_file\n";
    return -1;
  }

  inputFile.open(argv[1]);
  if (!inputFile.is_open()) {
    cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
    return -1;
  }

  outputFile.open(argv[2]);

  int c, o, n;
  inputFile >> c >> o >> n;

  vector<Customer*> customers(c);
  vector<Operator*> operators(o);

  int operation, opId, age, discountRate, type, idC1, idC2, time, quantity;
  double limitingAmount, talkingCharge, messageCost, networkCharge, amount;
  string name;
  int j = 0, k = 0;

  for(int i = 0; i < n; i++){
    inputFile >> operation;
    switch(operation){
      case 1:
        inputFile >> name >> age >> opId >> limitingAmount;
        customers[j] = new Customer(j, name, age, operators[opId], limitingAmount);
        j++;
        break;
      case 2:
        inputFile >> type >> talkingCharge >> messageCost >> networkCharge >> discountRate;
        if(type == 1){
          operators[k] = new VoxOperator(k, talkingCharge, messageCost,  networkCharge, discountRate, VOX);
        }else{
          operators[k] = new InternetOperator(k, talkingCharge, messageCost,  networkCharge, discountRate, INTERNET);
        }
        k++;
        break;
      case 3:
        inputFile >> idC1 >> idC2 >> time;
        customers[idC1]->talk(time, *customers[idC2]);
        break;
      case 4:
        inputFile >> idC1 >> idC2 >> quantity;
        customers[idC1]->message(quantity, *customers[idC2]);
        break;
      case 5:
        inputFile >> idC1 >> amount;
        customers[idC1]->connection(amount);
        break;
      case 6:
        inputFile >> idC1 >> amount;
        customers[idC1]->pay(amount);
        break;
      case 7:
        inputFile >> idC1 >> opId;
        customers[idC1]->setOperator(operators[opId]);
        break;
      case 8:
        inputFile >> idC1 >> amount;
        customers[idC1]->getBill()->changeTheLimit(amount);
    }
  }

  vector<Operator*>::iterator itr;
  for(itr = operators.begin(); itr != operators.end(); itr++){
    outputFile << (*itr)->toString() << "\n";
  }

  Customer  *mostTalk = *(customers.begin()), *mostMess = *(customers.begin()), *mostGb = *(customers.begin());
  vector<Customer*>::iterator itrC;

  for(itrC = customers.begin(); itrC != customers.end(); itrC++){
    outputFile << (*itrC)->toString() << "\n";

    if(mostTalk->getTotalSpentTalkingTime() < (*itrC)->getTotalSpentTalkingTime()){
      mostTalk = (*itrC);
    }
    if(mostMess->getTotalMessageSent() < (*itrC)->getTotalMessageSent()){
      mostMess = (*itrC);
    }
    if(mostGb->getTotalInternetUsage() < (*itrC)->getTotalInternetUsage()){
      mostGb = (*itrC);
    }
  }
  outputFile << (mostTalk)->getName() << ": " << (mostTalk)->getTotalSpentTalkingTime() << "\n";
  outputFile << (mostMess)->getName() << ": " << (mostMess)->getTotalMessageSent() << "\n";
  outputFile << (mostGb)->getName() << ": " << fixed << setprecision(2) << (mostGb)->getTotalInternetUsage() << "\n";




  return 0;
}
