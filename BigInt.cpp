#include<iostream>
#include<string.h>
#include<vector>
#include<cstring>
using namespace std;
#define MAX_BITS 1024
void showvec(vector<int> vec){
    for(int i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
}
bool OF(vector<int> &binnum){
    bool of = 0;
    if(binnum.size()>MAX_BITS ){
        int i = MAX_BITS;

        for( ;i<binnum.size();i++){
            if(binnum[i]==1){
                of = 1;
                break;
            }
        }
        binnum.erase(binnum.begin()+MAX_BITS,binnum.end());
    }
    return of;
}
bool isConvOf(vector<int> &binnum){
    bool ret_val = (binnum.size() > MAX_BITS-1);
    while(binnum.size() > MAX_BITS-1){
        binnum.pop_back();
    }
    return ret_val;
}
void revStr(char* s){
    int i = 0, j = strlen(s)-1;
    while(i<j){
        swap(s[i],s[j]);
        i++,j--;
    }
}
void readNumber(FILE*ptr, char* num){
    fscanf(ptr,"%s",num);
    int i=0, j=strlen(num)-1;
} 
void twos_comp(vector<int>& binnum){
    int i = 0;
    while( i <binnum.size() && binnum[i]!=1){
        i++;
    }
    i++;
    while(i<binnum.size()){
        binnum[i] = !binnum[i];
        i++;
    }
}
// binary conversion -------------
bool divideBy2(char* num) {
    int carry = 0;
    bool isZero = true;
    for (int i = strlen(num) - 1; i >= 0; --i) {
        int current = carry * 10 + (num[i] - '0');
        num[i] = (char)(current / 2) + '0' ;
        carry = current % 2;
        if ((num[i] - '0')!= 0){
            isZero = false;
        }
    }
    return isZero;
}

vector<int> convertToBinary(char* num, bool& of) {
    vector<int> binary;
    revStr(num);
    bool flag = false;
    if(num[strlen(num)-1] == '-'){
        flag = 1;
        num[strlen(num)-1] = '\0';
    }

    int bit = ((num[0]-'0') % 2 == 0 ? 0 : 1);
    binary.push_back(bit);  

    while (!divideBy2(num)) { 
        bit = ((num[0]-'0') % 2 == 0 ? 0 : 1);
        binary.push_back(bit);  
    }
    while(binary.size()<MAX_BITS-1){
        binary.push_back(0);
    }
    of = isConvOf(binary);
    int count = 0;
    for(int i:binary){
        if(i==1){
            count++;
        }
    }
    if(flag){
        twos_comp(binary);
    }
    binary.push_back(flag);
    return binary;
}
// decimal conversion ------------
string addStrings(const string& a, const string& b) {
    string result = "";
    int carry = 0, i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i--] - '0';
        }
        if (j >= 0){
             sum += b[j--] - '0';
        }
        result = char((sum % 10) + '0') + result;
        carry = sum / 10;
    }
    return result;
}

string multiplyBy2(const string& num) {
    string result = "";
    int carry = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        int prod = (num[i] - '0') * 2 + carry;
        result = char((prod % 10) + '0') + result;
        carry = prod / 10;
    }
    if (carry){ 
        result = char(carry + '0') + result;
    }
    return result;
}

string convertToDecimal(vector<int> bin) {
    bool flag = 0;
    if(bin.back()==1){
        twos_comp(bin);
        flag = 1;
    }
    string decimal = "0";
    string currentPower = "1"; 
    int i;
    for (i=0;i<bin.size()-1;i++) {
        if (bin[i] == 1) {
            decimal = addStrings(decimal, currentPower);
        }
        currentPower = multiplyBy2(currentPower);
    }
    if(flag){
        decimal.insert(0,"-");
        // decimal += '-';
    }
    return decimal;
}
// binary operations
vector<int> binAdd(vector<int> n1, vector<int> n2){
    int i=0,j=0;
    int carry = 0;
    int sum;
    vector<int> ans;
    while(i<n1.size() && j<n2.size()){
        sum = n1[i]^n2[j]^carry;
        carry = (n1[i]&n2[j]) | (n2[j]&carry) | (carry&n1[i]);
        ans.push_back(sum);
        i++,j++;
    }
    while(i<n1.size()){
        sum = n1[i]^carry;
        carry = (carry&n1[i]);
        ans.push_back(sum);
        i++;
    }
    while(j<n2.size()){
        sum = n2[j]^carry;
        carry = (carry&n2[j]);
        ans.push_back(sum);
        j++;
    }
    return ans;
}

vector<int> binSub(vector<int> n1, vector<int> n2){
    twos_comp(n2);
    vector<int> ans = binAdd(n1,n2);
    return ans;
}

vector<int> binMult(vector<int> n1, vector<int> n2){
    vector<int> prev(1,0);
    for( int i:n1 ){
        if(i==1){
            prev = binAdd(prev, n2);
        }
        n2.insert(n2.begin() , 0);
    }
    return prev;
}
// wrapper for arithmetic operations
string add(char* num1, char* num2, bool& of){
    vector<int> bin1,bin2;
    of = 0;
    bin1 = convertToBinary(num1,of);
    bin2 = convertToBinary(num2,of);
    vector<int> ans = binAdd(bin1,bin2);
    of = OF(ans);
    string decimalAns = convertToDecimal(ans);
    return decimalAns;
}

string sub(char* num1, char* num2, bool& of){
    vector<int> bin1,bin2;
    of = 0;
    bin1 = convertToBinary(num1,of);
    bin2 = convertToBinary(num2,of);
    vector<int> ans = binSub(bin1,bin2);
    of = OF(ans);
    string decimalAns = convertToDecimal(ans);
    return decimalAns;
}

string mult(char* num1, char*num2, bool&of){
    vector<int> bin1,bin2;
    of = 0;
    bin1 = convertToBinary(num1,of);
    bin2 = convertToBinary(num2,of);
    vector<int> ans = binMult(bin1,bin2);
    //showvec(ans);
    of = OF(ans);
    string decimalAns = convertToDecimal(ans);
    return decimalAns;
}
int main(){
    bool of = 0;
// additon
    FILE* ptr = fopen("data.txt","r");
    char num1[310], num2[310];
    readNumber(ptr,num1);
    readNumber(ptr,num2);
    string dec= add(num1,num2,of);
    cout<<dec<<" of:"<<of<<endl;
// subtraction
    ptr = fopen("data.txt","r");
    readNumber(ptr,num1);
    readNumber(ptr,num2);
    string subdec = sub(num1,num2,of);
    cout<<subdec<<" of:"<<of<<endl;
// multiplication
    ptr = fopen("data.txt","r");
    readNumber(ptr,num1);
    readNumber(ptr,num2);
    string multdec = mult(num1,num2,of);
    cout<<multdec<<" of:"<<of<<endl;
}