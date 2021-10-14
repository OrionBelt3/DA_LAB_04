#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

int main(){
    std::ios_base::sync_with_stdio(false);

    std::vector<std::pair<long, long>> answer; // array for storage answers
    std::vector<std::string> pattern; // substring
    std::vector<std::string> text; // all text divaded on words
    std::vector<std::pair<long, long>> mapText; // map of text for quick finding of positions of words

    // substring reading unit
    std::string word;
    char c;
    c = getchar();
    while(c != '\n'){
        if(c == ' ' || c == '\t'){
            if(!word.empty()){
                pattern.push_back(word);
                word.clear();
            }
        }else {
            word += std::tolower(c);
        }
        c = getchar();
    }
    if(!word.empty()){
        pattern.push_back(word);
        word.clear();
    }

    // text reading unit and filling of text map
    long numStr = 1, posWord = 0;
    c = getchar();
    while(c != EOF){
        if(c == ' ' || c == '\t'){
            if(!word.empty()){
                text.push_back(word);
                posWord++;
                mapText.push_back(std::make_pair(numStr, posWord));
                word.clear();
            }
            
        } else if(c == '\n'){
            if(!word.empty()){
                text.push_back(word);
                posWord++;
                mapText.push_back(std::make_pair(numStr, posWord));
                word.clear();
            }
            numStr++;
            posWord = 0;
        } else {
            word += std::tolower(c);
        }
        c = getchar();
    }
    if(!word.empty()){
        text.push_back(word);
        posWord++;
        mapText.push_back(std::make_pair(numStr, posWord));
        word.clear();
    }

    //algorithm KMP
    // first part: template creating 
    //0 1 2 3 4 5 6 7 8
    //a b b a a b b a b
    //0 0 0 1 1 2 3 4 2
    long sizePattern = pattern.size();
    long arr[sizePattern];
    arr[0] = 0;
    long j = 0;
    long i = 1;
    while(i < sizePattern) {
        if(pattern[i] == pattern[j]) { // a_i == a_j
            arr[i] = j+1; i++; j++;
        } else if(j == 0) { // a_i != a_j & j == 0
            arr[i] = 0; i++;
        } else {
            j = arr[j-1];
        }
    } 

    //second part
    long sizeText = text.size();
    long k = 0;
    long l = 0;
    i = 0;
    while(k < sizeText) {
        if(text[k] == pattern[l]) {
            k++; l++; 
            if(l == sizePattern){ // end: -> patern is finded
                answer.push_back(mapText[k-l]);
                l = arr[l-1];
            } 
        } else if(l == 0) {
            k++; 
        } else {
            l = arr[l-1];
        } 
    }

    //print all answers
    for(long i = 0; i < answer.size(); ++i){
        std::cout << answer[i].first << ", " << answer[i].second << "\n";
    }

    return 0;
}