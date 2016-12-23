#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <string.h>
#include <stack>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

int priority(string x){
    if(x == "+") return 1;
    if(x == "-") return 1;
    if(x == "*") return 2;
    if(x == "/") return 3;
    if(x == "^") return 4;
    if(x == "(") return -1;
}

int main(){
    string str("1 - ( 4 + 5 * 6 ) * 7");

    // ****************split string****************
    istringstream iss(str);
    char sub[100][100];
    char x ;
    int sum = 0;
    int count = 0;
    while(iss){
        iss >> sub[count];
        count++;
    }

    //****************Infix -> Postfix****************
    queue <string> Postfix;
    stack <string> tmp;

    for(int i = 0; i < count - 1; i++){
        if(isdigit(sub[i][0]))
            Postfix.push(sub[i]);
    
        else{
            if(strcmp(sub[i],"(") == 0)
                tmp.push(sub[i]);

            else if(strcmp(sub[i],"^") == 0)
                tmp.push(sub[i]);

            else if(strcmp(sub[i],")") == 0)
                while(1){
                    if((tmp.top()).compare("(") == 0){
                        tmp.pop();
                        break;
                    }
                    Postfix.push(tmp.top());
                    tmp.pop();
                }

            else{
                while(!tmp.empty()){
                    if(priority(sub[i]) > priority(tmp.top()))
                        break;
                    Postfix.push(tmp.top());
                    tmp.pop();                    
                }
                tmp.push(sub[i]);
            }
        }
    }

    while(!tmp.empty()){
        Postfix.push(tmp.top());
        tmp.pop();
    }    

    //****************Calculate****************
    stack <double> res;
    while(!Postfix.empty())
        if(isdigit(Postfix.front()[0])){
            res.push(atof(Postfix.front().c_str()));
            Postfix.pop();
        }
        else{
            if(Postfix.front().compare("+") == 0){
                double t2 = res.top();
                res.pop();
                double t1 = res.top();
                res.pop();
                res.push(t1+t2);
            }
            else if(Postfix.front().compare("-") == 0){
                double t2 = res.top();
                res.pop();
                double t1 = res.top();
                res.pop();
                res.push(t1-t2);
            }
            else if(Postfix.front().compare("*") == 0){
                double t2 = res.top();
                res.pop();
                double t1 = res.top();
                res.pop();
                res.push(t1*t2);
            }
            else if(Postfix.front().compare("/") == 0){
                double t2 = res.top();
                res.pop();
                double t1 = res.top();
                res.pop();
                res.push(t1/t2);
            }
            else if(Postfix.front().compare("^") == 0){
                double t2 = res.top();
                res.pop();
                double t1 = res.top();
                res.pop();
                res.push(pow(t1,t2));
            }
            Postfix.pop();
        }
    cout << str << " = " << res.top() << '\n';
}