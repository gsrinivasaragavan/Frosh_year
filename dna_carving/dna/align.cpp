//
//  align.cpp
//  dna_alignment
//
//  Created by Erika DeBenedictis on 1/27/13.
//  Copyright (c) 2014 California Institute of Technology. All rights reserved.
//
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// scoring values
#define GAP_SCORE -5
#define MISMATCH -1
#define MATCHING 2

/**
 * @brief Packages the score and instruction string the align function returns
 */
struct align_result {
    int score;      // score of this alignment
    string inst;    // instruction on how to align the inputs

    align_result(int s, string i) {
        this->score = s;
        this->inst = i;
    }
    align_result() {
        this->score = 0;
        this->inst = "";
    }
};

// memo_type will allow us to hash the string input to align
// with its output for memoization
typedef unordered_map<string, align_result> memo_type;

/**
 * @brief Function takes two strings, s and t, and produces an align_result
 * of the highest alignment score and its corresponding instruction str.
 */
align_result align(string s, string t, memo_type &memo) {
    // if this result is memoized, use recorded result
    string key = s + "," + t;
    if (memo.count(key) > 0){
      return memo[key];
    }

    if (s == "") //base case 1
    {
        //create the string using a for loop 
        string gap = "";
        for(unsigned i = 0; i < t.size(); i++)
        {
            gap += "t";
        }
        return align_result(GAP_SCORE * t.size(), gap);
    }

    else if (t == "") //base case 2
    {
        string gap = "";
        for(unsigned i = 0; i < s.size(); i++)
        {
            gap += "s";

        }
        return align_result(GAP_SCORE * s.size(), gap);
    }
    align_result gap_S = align(s.substr(1), t, memo); //defining the first object as a result of taking out characters from s
    align_result gap_T = align(t.substr(1), s, memo); //defining second object as result of taking out characters from t
    align_result no_gap = align(s.substr(1), t.substr(1), memo); //defining third object as a result of no gaps, taking out characters at same time
    gap_S.score += GAP_SCORE; //every time function runs, update Gap score for s
    gap_T.score += GAP_SCORE;//update Gap score for t
    gap_S.inst = "s" + gap_S.inst; //update string for s 
    gap_T.inst = "t" + gap_T.inst; //update string for t
    if (s[0] == t[0]) //if first value at s and t are equal
    {
        no_gap.inst = "|" + no_gap.inst; //update no gap string
        no_gap.score += MATCHING; //add the matching score
    }
    else if (s[0] != t[0])
    {
        no_gap.inst = "*" + no_gap.inst; //update no gap string
        no_gap.score += MISMATCH; //add mismatching score
    } 
    align_result answer; //create an align-result object called answer
    if (no_gap.score > gap_S.score && no_gap.score > gap_T.score) //check to see which score is the greatest
    {
        answer = no_gap;
    }
    else if (gap_S.score > no_gap.score && gap_S.score > gap_T.score)
    {
        answer = gap_S;
    }
    else if (gap_T.score > no_gap.score && gap_T.score > gap_S.score)
    {
        answer = gap_T;
    }



    /* Before you return your calculated  align_result object,
       memoize it like so:*/
    memo[key] = answer;
    return answer; //return the highest score
}

/**
 * @brief Wrapper function to print the results of align
 */
void DNA_align(string s, string t) {
    cout << endl << "Calling DNA align on strings " << s << ", " << t << endl;

    // create the memoization system
    memo_type memo;

    align_result answer = align(s, t, memo);
    string ans = answer.inst;
    int score = answer.score;

    // Printing section
    // line where string s will be printed, spaces inserted
    string line1 = "";
    // line where string t will be printed, spaces inserted
    string line2 = "";
    // description of the relationship between s and t here (* | s t)
    string line3 = "";

    int j = 0;      // running index in s
    int k = 0;      // running index in t

    for (unsigned int m = 0; m < ans.length(); m++) {
        // i is the next element in our instruction string ans
        string i = ans.substr(m, 1);

        // only in s
        if(i.compare("s") == 0){
            line1 += s[j]; j++;
            line2 += " ";
            line3 += "s";
        }

        // only in t
        else if (i.compare("t") == 0){
            line1 += " ";
            line2 += t[k]; k++;
            line3 += "t";
        }

        // mismatch
        else if (i.compare("*") == 0){
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "*";
        }

        // match
        else {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "|";
        }
    }
    cout << line1 << endl << line2 << endl << line3 << endl;
    cout << "Score for this alignment: " << score << endl;
}

int main(){
    // some test cases to begin with
    DNA_align("",   "a");
    DNA_align("b",  "");
    DNA_align("a", "a");
    DNA_align("b",  "a");
    DNA_align("b",  "ba");
    DNA_align("ab", "ba");
    DNA_align("ab", "b");
    DNA_align("agcgaaagcaggtcaaatatattcaatatggagagaataaaagaactgagagatctaatgtcgcagtcccgcactcgcgagatactcactaagaccactgtggaccatatggccataatcaaaaagtacacatcaggaaggcaagagaagaaccccgcactcagaatgaagtggatgatggcaatgagatacccaattacagcagacaagagaataatggacatgattccagagaggaat", "atggagagaataaaagaactgagagatctaatgtcgcagtcccgcactcgcgagatactcactaagaccactgtggaccatatggccataatcaaaaagtacacatcaggaaggcaagagaagaaccccgcactcagaatgaagtggatgatggcaatgagatacccaattacagcagacaagagaataatggacatgattccagagaggaatgaacaaggacaaaccctctggagcaaa");
    return 0;
}
