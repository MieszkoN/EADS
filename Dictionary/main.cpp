#include <iostream>
#include "dictionary.h"
using namespace std;

int main() {
    Dictionary<string, string> d1;
    d1.insert("plumber", "whose job is to fit and repair water pipes");
    d1.insert("engineer", "a person trained and skilled in the design, construction, and use of engines or machines, or in any of various branches of engineering");
    d1.insert("dentist", "a person whose profession is dentistry");
    d1.insert("architect", "the deviser, maker, or creator of anything");
    d1.insert("dentist", "a person whose profession is dentistry");  //inserting the same element
    d1.insert("actor", "a person who acts in stage plays, motion pictures, television broadcasts, etc.");
    d1.insert("financier", "a person skilled or engaged in managing large financial operations, whether public or corporate.");
    d1.insert("hairdresser", "a person who arranges or cuts hair.");
    d1.insert("baker", "a person whose job is to make bread and cakes for sale, or to sell bread and cakes");
    d1.insert("hairdresser", "a person who arranges or cuts hair.");
    d1.remove("hairdresser");
    Dictionary <string, string>d2(d1);
    d2.print();
    cout << "Height of dictionary: " << d2.dictionaryHeight() << endl;
    cout << "Number of nodes in Dictionary: " << d2.dictionaryNodeCount() << endl;
    d1.destroyDictionary();
    d2.destroyDictionary();
}