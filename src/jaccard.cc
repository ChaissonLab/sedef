/// 786 

#include <bits/stdc++.h>
#include "common.h"
#include "search.h"
using namespace std;

inline void TIME(string msg, auto &start)
{
    auto end = chrono::high_resolution_clock::now();
    eprn("{}: {:.2f}s", 
        msg, 
        chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.00);
    start = end;
}

// 2    chr1    88000   121417  chr1:235525 0   +   chr1    235525  267707  32182   ... 32150   31941   209 133 76  0.993499    0.992727    0.006529    0.006532    33417
// 4    chr1    91256   92392   chr1:521369 0   +   chr1    521369  522487  1118    ... 1117    1092    25  18  7   0.977619    0.974130    0.022722    0.022781    1136
// *rea2 6  chr1    92387   104808  chr1:573869 0   +   chr1    573869  586415  12546   ... 12359   12175   184 121 63  0.985112    0.983679    0.015038    0.015056    12421
// *rea2 10 chr1    92387   135370  chr1:224095998  0   +   chr1    224095998   224139533   43535   ... 42819   42180   639 417 222 0.985077    0.983377    0.015074    0.015091    42983
// *rea2 12 chr1    92387   136258  chr1:243174377  0   +   chr1    243174377   243218157   43780   ... 43446   42679   767 507 260 0.982346    0.980338    0.017865    0.017891    43871

int main(int argc, char **argv)
{
    if (argc < 3) exit(1);

    eprn("* Sedef (Jaccard idea), ver {} *", GITVER);
    
    auto t_start = chrono::high_resolution_clock::now();

    string ref_path = argv[1];
    string query_path = argv[2];
    bool is_complement = (argc > 3 && tolower(argv[3][0]) == 'y');

    string line, reference, query;

    ifstream fin;

    fin.open(ref_path.c_str());
    string ref_chr;
    while (getline(fin, line)) {
        if (line[0] != '>') reference += line;
        else ref_chr = line.substr(1);
    }
    fin.close();
    fin.clear();

    transform(reference.begin(), reference.end(), reference.begin(), ::toupper);
    if (is_complement) {
        reverse(reference.begin(), reference.end());
        for (auto &c: reference) c = (c == 'A' ? 'T' : (c == 'C' ? 'G' : (c == 'G' ? 'C' : (c == 'T' ? 'A' : c))));
    }

    fin.open(query_path.c_str());
    string query_chr;
    while (getline(fin, line)) {
        if (line[0] != '>') query += line;
        else query_chr = line.substr(1);
    }
    fin.close();
    transform(query.begin(), query.end(), query.begin(), ::toupper);
        TIME("Reading time", t_start);

    auto ref_hash = Hash(reference);
        TIME("Reference hashing time", t_start);

    /// TODO optimize if ref == query
    auto query_hash = Hash(query);
        TIME("Query hashing time", t_start);

    // auto pos = {121350751, 121361171};
    // #   (121361171-121418375, 121418376, 121472478),
    // #   (121350751, 121391239, 121444958, 121485446)), 40k-->57k

    //for (auto i: pos) {
    //for (int i = 121000000; i < 121370000; i += 250) {

    bool allow_overlaps = (ref_path != query_path) || is_complement;
    eprn("Allowing overlaps: {}", allow_overlaps);

    for (int i = 0; i < query.size(); i += 250) {
        while (query[i] == 'N') i++;
        while (i % 250 != 0) i++;

        auto mapping = search(i, ref_hash, query_hash, allow_overlaps);
        //    TIME("Mapping time", t_start);

        // prn("{} mappings in total", mapping.size()); //3654?
        for (auto &pp: mapping) /*if (p.second > .5)*/ {    
            // BEDPE
            if (is_complement) {
                pp.i = ref_hash.seq.size() - pp.i + 1;
                pp.j = ref_hash.seq.size() - pp.j + 1;
                swap(pp.i, pp.j);
            }
            prn("{}\t{}\t{}\t{}\t{}\t{}\t\t{}\t{}\t{}\t{}\t{}\t{}",
                query_chr, pp.p, pp.q, 
                ref_chr, pp.i, pp.j,
                pp.id, 
                "+", is_complement ? "-" : "+",
                // Optional fields
                int(pp.break_criteria),
                pp.q - pp.p, pp.j - pp.i
            );
        }
        // prnn("\n");
    }

    return 0;
}