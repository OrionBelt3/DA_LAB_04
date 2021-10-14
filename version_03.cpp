#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

/* void ToLower(std::string& token) {
        for(int64_t i=0; i < token.size(); ++i) {
            if('A' <= token[i] && token[i] <= 'Z') {
                token[i] = token[i] + 'a' - 'A';
            }
        }
    }
 */
// проверить на выход из вектора, где то утечка памяти
int main(){

    std::ios_base::sync_with_stdio(false);

    std::vector<std::pair<long, long>> answer;
    std::vector<std::string> pattern;
    std::vector<std::string> text;
    std::vector<std::pair<long, long>> mapText;

    std::string input, token;
    std::getline(std::cin, input);
    std::stringstream patternSS(input);

    

    while(patternSS >> token){
        std::transform(token.begin(),token.end(), token.begin(), tolower);
        pattern.push_back(std::string(token));
    }

    long numStr = 0, posWord;
    while(std::getline(std::cin, input)) {
        std::stringstream textSS(input);
        numStr++;

        posWord = 0;
        while(textSS >> token){
            posWord++;
            mapText.push_back(std::make_pair(numStr, posWord));
            std::transform(token.begin(),token.end(), token.begin(), tolower);
            text.push_back(std::string(token));
        }
    }

    //algorithm KMP
    // first part
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
            //std::cout << "OK1: " << k << " " << l << "\n";
            k++; l++; 
            if(l == sizePattern){
                answer.push_back(mapText[k-l]);
                l = arr[l-1];
            } 
        } else if(l == 0) {
            k++; 
            //std::cout << "OK2: " << k << " " << l << "\n";
            /*
            if(k == sizeText) {
                std::cout << "It's done!" << "\n";
            }
            */ 
        } else {
            l = arr[l-1];
            //std::cout << "OK3: " << k << " " << l << "\n";
        } 
    }

    for(long i = 0; i < answer.size(); ++i){
        std::cout << answer[i].first << ", " << answer[i].second << "\n";
    }

    return 0;
}