#include <iostream>
#include "functions.h"
#include <regex>


using namespace std; 

unsigned char *scanp; // (init to buff)
int lin = 1; // current line, init 1
int col = 1; // current col, init 1

// for not yet resolved identifers
    const int MAXNAME = 10;
    char currName[MAXNAME];
    string currNameStr;

    int currToken = 0; // main value: token type
    float currValue; // token value: value, check if we keep this int or float

    void getToken();

int main() {

    // For debugging
    int currFile; // file index
    int currLine; // current line number
    int currCol; // current column number

    scanp = initialize(); // open files

    //cout << *scanp;
    while (currToken != 10) {
        //cout << "current char to tokenized: " << *scanp;
        getToken();
        printToken();
    }

    return 0;
}


void getToken() {
    unsigned char c;

    regex LETTER ("[a-zA-z_]");
    regex DIGIT ("[0-9]"); //TODO: double check this, does 0 work as a valid EOF_TK??
    regex PUNCT_OR_OPER ("[><({}.*\\-;=)]");
    regex QUOTE ("[']");
    regex SPACE ("[ ]");
    regex NEWLINE ("[\n]");

    c = *scanp++;
    //cout << "current char to tokenized: " << c;
    string cStr(1, c); // regex only works with string
    cout << "c: " << c;
    cout << "cStr: " << cStr;

    restart:
    // update line column here

    if(regex_match(cStr,LETTER)) { // a..z, A..Z and possibly other chars
        // return one of the keyword tokens, or TK_UNKNOWN (id, not a keyword)
        int currNameLength = 0;
        for(int i=0; i < MAXNAME; i++) { // truncate beyond MAXNAME
            if(!(regex_match(cStr, LETTER) || regex_match(cStr, DIGIT))) {
                break; // if next char not part of identifier, stop scanning
            }
            currName[i] = tolower(c); // add characters to curname (pascal is case insenstive so we take the lowercase)
            c = *scanp++; // advance scanp
            cStr = c;
            currNameLength++;
        }
        //cout << "pointer is currently at: " << c;
        for(int i=0; i<currNameLength; i++) {
            currNameStr += currName[i];
        }
        //cout << currNameStr;
        *scanp--;
        //TODO: Search the keyword symbol table and return a keyword token if a match is found with currName
                // if found, return symbol token here

        //TODO: return TK_UNKNOWN 
        //cout << "TK_UNKNOWN_OR_SYMBOL";
        //cout << currNameStr;
        currToken = TK_UNKNOWN;
        return;
    }
    else if(regex_match(cStr, DIGIT)) {
        int value = 0;
        int base = 10;
        while ('0'<=c && c<='9') {
            value = value * base + c - '0'; // get numerical value of c, append to value
            c = *scanp;
            *scanp++;
            cStr = c;
        }
        //*scanp--;
        // at this point, next char is either not related to int/real, or . or E or #
        switch(c) {
            case '#':
            {
                c = *scanp++; // double check this
                base = value;
                if(base < 10) {
                    while (regex_match(cStr, LETTER) || regex_match(cStr, LETTER)) {
                        if(regex_match(cStr, LETTER)){
                            c = tolower(c);
                            // maybe create/reference map where each letter a-z maps to their respective value (i.e a = 10, b= 11, etc..)
                            // to convert c to its correct numerical value (as a char!!)
                        }
                        value = value * base + c - '0'; // get numerical value of c, append to value
                        c = *scanp++;
                    }
                    currValue = value;
                    // return TK_INTLIT
                }
            }
            case '.':
            {
                // scan rest of the number, also check for '..'??
                float floatValue = value;
                cout << "value before .:" << floatValue << "\n";
                c = *scanp;
                *scanp++;
                int n = 1;
                while ('0'<=c && c<='9') {
                    cout << "FloatNow: " << floatValue;
                    cout << "lookingAt: " << c;
                    floatValue = (floatValue * pow(base, n) + c - '0') / pow(base, n); // divide by 10 to add new digit
                    n++;
                    c = *scanp;
                    *scanp++;
                    cout << "newFloat: " << floatValue <<  "\n";
                    }
                currValue = floatValue;
                currToken = TK_REALLIT;
                return;
                // return TK_REALLIT
            }
            default:
            {
                currValue = value;
                currToken = TK_INTLIT;
                return;
            // return TK_INTLIT
            }
        }
    }
    else if(regex_match(cStr, PUNCT_OR_OPER)) {
        // return one of the operator tokens or skip comment and restart

        switch(c) {
            case '{' :
                while(c != '}'){
                c = *scanp++;
            }
                break;
            /*case '(' :
                unsigned char cNext = *scanp + 1;
                if(cNext == '*'){
                    c = *scanp++;
                    c = *scanp++; // move 2 chars ahead so we don't accept (*) as a comment
                    while(c != '*' && cNext != ')'){ // move until we scan *)
                        c = *scanp++;
                        cNext = *scanp + 1;
                    }
                    c = *scanp++; // move another char to have c be the next char after comment
                    goto restart;
                    break;
                }
            // return TK_LFT_PARAN
            case '<':
                unsigned char cNext = *scanp + 1;
                if(cNext == '>') {
                    c = *scanp++;
                    // return TK_NOT_EQUALS
                }
                else if(cNext == '=') {
                    c = *scanp++;
                    // return TK_LESS_THAN_EQUAL
                }
                else {
                    // return TK_LESS_THAN
                }
                break;
            case '>':
                unsigned char cNext = *scanp + 1;
                if(cNext == '=') {
                    c = *scanp++;
                    // return TK_GREATER_THAN_EQUAL
                }
                else {
                    // return TK_GREATER_THAN
                }
            case '.':
                unsigned char cNext = *scanp + 1;
                if(cNext == '.') {
                    c = *scanp++;
                    // return TK_DOUBLE_DOT
                }
                else {
                    // return TK_DOT
                }
            case '+':
                // return TK_PLUS
            case '-':
                // return TK_MINUS
            case '*':
                // return TK_MULTI
            case '/':
                // return TK_DIVIDE, does pascal have // as comments?
            case '=':
                // return TK_EQUAL*/
        }

    }/*
    else if(regex_match(c, cMatch, QUOTE)) {
        string strValue = "";
        c = *scanp++;
        unsigned char cNext = *scanp + 1;

        while (c != '\'' && !(c == '\'' && cNext == '\'')) {
            if(c == '\'' && cNext == '\'') {
                strValue = strValue + "'";
            }
            else {
                strValue += c;
            }
            c = *scanp++;
        }
        // how to return string value? Do it need to?
        // return TK_STRLIT
    }
    else if(regex_match(c, cMatch, SPACE)) {
        c = *scanp++;
        goto restart;
    }
    else if(regex_match(c, cMatch, NEWLINE)) {
        // update line number here
        c = *scanp++;
        goto restart; // or return TK_EOLN
    }*/
    if(c == 0){
        currToken = 10;
        return;
        // return TK_EOF
    }

    currToken = 2;
    cout << "TK_NOTTOKEN";
    return;
}


void printToken() {
    cout << currToken;
    if(currToken == TK_INTLIT || currToken == TK_REALLIT) {
        cout << " value: " << currValue;
    }
    else if(currToken == TK_UNKNOWN) {
        cout << " value: " << currNameStr;
    }
    cout << "\n";
    // TODO: implement function to print token
    return;
}