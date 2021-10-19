#include <iostream>
#include <string>
#include <string.h>

#include "ssw_cpp.h"


void sw_aln(StripedSmithWaterman::Alignment& aln,
            const std::string& ref,
            const std::string& query,
            const uint8_t& match_score,
            const uint8_t& mismatch_penalty,
            const uint8_t& gap_open_penalty,
            const uint8_t& gap_extending_penalty);



int main() {
    StripedSmithWaterman::Alignment aln;
    sw_aln(aln, "CAGCCTTTCTGACCCGGAAATCAAAATAGGCACAACAAA", "CTGAGCCGGTAAATC", 3, 2, 2, 0);
    
    std::cout << aln.cigar_string << std::endl;
}

void sw_aln(StripedSmithWaterman::Alignment& alignment,
           const std::string& ref, 
           const std::string& query, 
           const uint8_t& match_score, 
           const uint8_t& mismatch_penalty,
           const uint8_t& gap_open_penalty,
           const uint8_t& gap_extending_penalty){

    int32_t mask_len = strlen(query.c_str()) / 2;
    mask_len = mask_len < 15 ? 15 : mask_len;

    StripedSmithWaterman::Aligner aligner(match_score, 
                                          mismatch_penalty, 
                                          gap_open_penalty, 
                                          gap_extending_penalty);

    StripedSmithWaterman::Filter filter;

    aligner.Align(query.c_str(), ref.c_str(), ref.size(), filter, &alignment, mask_len);
}
