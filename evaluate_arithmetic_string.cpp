// write a function that takes a string of arithmetic equation below and returns a scalar as the evaluation of the equation
// arithmetic supports 4 operators: +, *, &, |, where + and * are defined as usual, & and | are defined as pairwise max, min, respectively. 
// your algorithm should handle space and decimal
// priority: &, | > * > +
// e.g. 1 & 2 | 3 * 4 * 5 + 6
//    = 2 | 3 * 4 * 5 + 6
//    = 2 * 4 * 5 + 6
//    = 46

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <iterator>

using namespace std;

// return: ops are 0 to 3, and non-op is -1
int operatorType(const string& str)
{
  if (str.compare("&")==0)
    return 0;
  else if (str.compare("|")==0)
    return 1;
  else if (str.compare("*")==0)
    return 2;
  else if (str.compare("+")==0)
    return 3;
  else
    return -1;
}


int evaluate(const int operand1, const int operand2, const int op)
{
  if (op == 0)
    return max(operand1, operand2);
  else if (op == 1)
    return min(operand1, operand2);
  else if (op == 2)
    return operand1 * operand2;
  else 
    return operand1 + operand2;
}


// I am assuming the string evaluates to int. expecting no over-flow; otherwise need long everywhere
int evaluateStringList(auto& words)
{
  
  // base case 
  if (words.size()==0)
    return 0;
  
  // base case
  if (words.size()==1)
  {
    const auto opType = operatorType(*(words.begin()));
    assert(opType==-1);
    return stoi(*(words.begin()));
  }
  
  // need to have atleast one valid operator
  assert(words.size()>=3);
  
  stack<int> operands;
  stack<int> ops;
  
  for (auto& x: words)
  {
    const auto opType = operatorType(x);
    if (opType == -1) // operand
    {
      int operand = stoi(x);
      operands.push(operand);
    }
    else             // operator
    {
      while ( !ops.empty() && (opType >= ops.top()))
      {        
        // get operands and ops from stack
        assert(operands.size() >= 2);
        const auto operand2 = operands.top();
        operands.pop();
        const auto operand1 = operands.top();
        operands.pop();
        const auto op = ops.top();
        ops.pop();
        
        const auto evaledOperand = evaluate(operand1, operand2, op);
        
        operands.push(evaledOperand);  
      }
      ops.push(opType);
    }    
  }

  while(!ops.empty())
  {
    const auto operand2 = operands.top();
    operands.pop();
    const auto operand1 = operands.top();
    operands.pop();
    const auto op = ops.top();
    ops.pop();
    
    operands.push(evaluate(operand1, operand2, op));
  }
  
  assert(operands.size() == 1);  
  return operands.top();

}

void printInput(auto& words)
{
  for (const string& word : words) {
    cout << word;
  }
  cout << "\n";
}


//https://stackoverflow.com/questions/236129/split-a-string-in-c
template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


int evaluateStringSentence(const string& sentence)
{
  auto words = split(sentence, ' ');
  return evaluateStringList(words);
}


// To execute C++, please define "int main()"
int main() {
 
  vector<string> words_1 = { "1", "&",  "2",  "|",  "3",  "*",  "4",  "*",  "5", "+", "6" };
  printInput(words_1);  
  cout << evaluateStringList(words_1) << endl;
  
  vector<string> words_2 = {"1"};
  printInput(words_2);
  cout << evaluateStringList(words_2) << endl;

  vector<string> words_3 = {};
  printInput(words_3);
  cout << evaluateStringList(words_3) << endl;

  vector<string> words_4 = {"100", "*", "5", "&", "100", "+", "500", "|", "500", "+", "50"};
  printInput(words_4);
  cout << evaluateStringList(words_4) << endl;
  
  string sentence_5 = "1 & 2 | 3 * 4 * 5 + 6";
  cout << evaluateStringSentence(sentence_5) << endl;

  string sentence_6 = "100 * 5 & 100 + 500 | 500 + 50";
  cout << evaluateStringSentence(sentence_6) << endl;  
  
  string sentence_7 = "";
  cout << evaluateStringSentence(sentence_7) << endl; 
  
  string sentence_8 = "9090";
  cout << evaluateStringSentence(sentence_8) << endl; 
  
  vector<string> words_9 = {"100", "&", "5", "&", "100", "|", "500", "|", "500", "&", "50"};
  printInput(words_9);
  cout << evaluateStringList(words_9) << endl;

  string sentence_10 = "100 & 5 & 100 | 500 | 500 & 50";
  cout << evaluateStringSentence(sentence_10) << endl;
  
  
  return 0;
}

