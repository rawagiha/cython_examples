#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <string.h>

#include "ssw_cpp.h"


void sw_aln(StripedSmithWaterman::Alignment* aln,
            const std::string& ref,
            const std::string& query,
            const uint8_t& match_score,
            const uint8_t& mismatch_penalty,
            const uint8_t& gap_open_penalty,
            const uint8_t& gap_extending_penalty);


struct ParsedVariant {
    bool is_indel;
    bool is_ins;
    bool is_del;
    uint16_t variant_len;
    std::string lt_ref;
    std::string lt_query;
    std::string lt_clipped_segment;
    std::string ins_seq;
    std::string del_seq;
    std::string ref_base;
    std::string alt_base;
    std::string rt_ref;
    std::string rt_query;
    std::string rt_clipped_segment;
    uint32_t genomic_pos; 
};


std::vector<ParsedVariant> find_variants(const StripedSmithWaterman::Alignment& alignment,
                                         const std::string& ref,
                                         const std::string& query,
                                         uint32_t genomic_pos = 0);


std::vector<std::string> decompose_cigar_string(const std::string& cigar_string);

double sequence_similarity(const char* a, const char* b); 

int main() {
    StripedSmithWaterman::Alignment aln;
    
    
    std::string ref = "CCGTGTGCGTCACGCTTGAAGACCACGTTGGTGTGCAGCACGCGGCTGAGCTCCCGCAGGAAGTGGAAGGAGCTGTTGCGCAGCTGCTCCGGCGG";
    std::string query = "CCGTGTGCGTCACGCTTGAAGACCACGTTGGTGTGCAGCACGCGGCTGAGCTCCCGCAGGGCTGCTGGGTGGAAGGAGCTGTTGCGCAGCTGCTCCGGCGN";
    
    /*
    std::string ref = "TGCTGGCTCTAAAAGCAGAGGATCCCCATGATTATAAAGACTTAATTTTTGTTTTTCATAGGCAATCAGGGAAGTTGCCTGATTTATGAGGATTCTCATAAAATCAACTGAACAGAGATCTCTGTTGCAGAA"; 
    std::string query = "TGCTGGCTCTAAAAGCAGAGGATCCCCATGATTATAAAGACTTAATTTTTGTTTTTCATAGGCAATCAGGGAAGTTGGTTGTAGTGATAAAGTTGGCAGGTCATATGAGGATTCTCATAAAATCAACTGAACAGAGATCTCTGTTGCAGAA";
    */
    sw_aln(&aln, ref, query, 3, 2, 3, 0);
    
    std::string a = "WIKIMEDIA";
    std::string b = "WIKIMANIA";
    std::cout << sequence_similarity(a.c_str(), b.c_str()) << std::endl;
    std::vector<ParsedVariant> v = find_variants(aln, ref, query, 139399308);
}

void sw_aln(StripedSmithWaterman::Alignment* alignment,
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

    aligner.Align(query.c_str(), ref.c_str(), ref.size(), filter, alignment, mask_len);
}


std::vector<std::string> decompose_cigar_string(const std::string& cigar_string) {
    std::regex cigar_pattern(R"(\d+[MIDNSHPX=])");

    std::regex_iterator<std::string::const_iterator> cigar_itr(cigar_string.begin(), cigar_string.end(), cigar_pattern);
    std::regex_iterator<std::string::const_iterator> end_of_itr;

    std::vector<std::string> cigarette;
    while (cigar_itr != end_of_itr) {
        cigarette.push_back((*cigar_itr).str());
        ++cigar_itr;
    }

    return cigarette;
}

bool is_gap(std::string cigar_itr) {
    return (
            ( cigar_itr.find("I") != std::string::npos ) 
            || 
            ( cigar_itr.find("D") != std::string::npos )
           ); 
}

bool is_complex(const std::vector<std::string>& cigarette) {
    bool prev_is_gap = false;
    for (std::vector<std::string>::const_iterator itr = cigarette.begin(); itr != cigarette.end(); ++itr) {
        if ( (prev_is_gap) && is_gap((*itr)) ) { 
            return true;
        }
        prev_is_gap = is_gap((*itr));                 
    }
    return false;
}

std::string concat_gaps(const std::vector<std::string>& cigarette, std::string  gap_type) {
    std::string gaps;
    
    if ( !cigarette.empty() ) {
        uint16_t total_gap_len = 0;
        
        for (std::vector<std::string>::const_iterator itr = cigarette.begin(); itr != cigarette.end(); ++itr) {
            total_gap_len += std::stoi((*itr).substr(0, (*itr).length() - 1));
        }
    
        gaps = std::to_string(total_gap_len) + gap_type;
    }

    return gaps;
}


void edit_cigar(std::vector<std::string>& cigarette) {
    std::vector<std::string> tmp, ins, del;
    
    bool prev_is_gap = false;
    for (std::vector<std::string>::const_iterator itr = cigarette.begin(); itr != cigarette.end(); ++itr) {
        if ( is_gap((*itr)) ) {
            if ( (*itr).find("I") != std::string::npos ) {
                ins.push_back(*itr);
            }
            else {
                del.push_back(*itr);
            }
            prev_is_gap = true; 
        }
        else {
            if ( prev_is_gap ) {
                std::string merged_ins = concat_gaps(ins, "I");
                if ( !merged_ins.empty() ) {
                    tmp.push_back(merged_ins);
                }
                std::string merged_del = concat_gaps(del, "D");
                if ( !merged_del.empty() ) {
                    tmp.push_back(merged_del);
                }
                tmp.push_back(*itr);
                ins.clear();
                del.clear();
            }
            else {
                tmp.push_back(*itr);
            }
            
            prev_is_gap = false; 
        }    
    }
    std::swap(cigarette, tmp);
}


std::vector<ParsedVariant> find_variants(const StripedSmithWaterman::Alignment& alignment, 
                                         const std::string& ref, 
                                         const std::string& query,
                                         uint32_t genomic_pos) {
 
    std::vector<std::string> cigarette = decompose_cigar_string(alignment.cigar_string);
    std::vector<ParsedVariant> variants;
    
    if ( is_complex(cigarette) ) {
        edit_cigar(cigarette);
    }
    
    genomic_pos = (genomic_pos > 0) ? genomic_pos - 1 : 0;

    uint32_t ref_idx = alignment.ref_begin, query_idx = alignment.query_begin;
    
    std::cout << alignment.cigar_string << std::endl;
     
    for (std::vector<std::string>::iterator itr = cigarette.begin(); itr != cigarette.end(); ++itr) {

        char operation = (*itr).back(); // cigar operation 
        uint16_t op_len = std::stoi((*itr).substr(0, (*itr).length() - 1)); // operation length

        if (operation == 'I') {
            ParsedVariant ins;
            
            ins.is_indel = true;
            ins.is_ins = true;
            ins.is_del = false;
            
            ins.lt_ref = ref.substr(0, ref_idx);
            ins.lt_query = query.substr(0, query_idx);
            ins.ins_seq = query.substr(query_idx, op_len);
            ins.variant_len = op_len;
            ins.rt_ref = ref.substr(ref_idx);
            ins.rt_query = query.substr(query_idx + op_len);
            
            ins.lt_clipped_segment = query.substr(0, alignment.query_begin);
            ins.rt_clipped_segment = query.substr(alignment.query_end + 1, 
                                                  query.length() - alignment.query_end);

            ins.genomic_pos = genomic_pos;

            std::cout << ins.ins_seq << " at " << ins.genomic_pos << std::endl;
            variants.push_back(ins);

            query_idx += op_len;
            
        }
        else if (operation == 'D') {
            ParsedVariant del;

            del.is_indel = true;
            del.is_ins = false;
            del.is_del = true;

            del.lt_ref = ref.substr(0, ref_idx);
            del.lt_query = query.substr(0, query_idx);
            del.del_seq = ref.substr(ref_idx, op_len);
            del.variant_len = op_len;
            del.rt_ref = ref.substr(ref_idx + op_len);
            del.rt_query = query.substr(query_idx);

            del.lt_clipped_segment = query.substr(0, alignment.query_begin);
            del.rt_clipped_segment = query.substr(alignment.query_end + 1,
                                                  query.length() - alignment.query_end);
            
            del.genomic_pos = genomic_pos;

            std::cout << del.del_seq << " at " << del.genomic_pos << std::endl;
            variants.push_back(del);

            ref_idx += op_len;
            genomic_pos += op_len;
        }
        else if (operation == 'X') {
            ParsedVariant smv;      // single or multi-nucleotide variant 

            smv.is_indel = false;
            smv.is_ins = false;
            smv.is_del = false;
            
            smv.lt_ref = ref.substr(0, ref_idx);
            smv.lt_query = query.substr(0, query_idx);
            smv.ref_base = ref.substr(ref_idx, op_len);
            smv.alt_base = query.substr(query_idx, op_len);
            smv.variant_len = op_len;   
            smv.rt_ref = ref.substr(ref_idx + op_len);
            smv.rt_query = query.substr(query_idx + op_len);

            smv.lt_clipped_segment = query.substr(0, alignment.query_begin);
            smv.rt_clipped_segment = query.substr(alignment.query_end + 1,
                                                  query.length() - alignment.query_end);

            smv.genomic_pos = genomic_pos;   
            
            variants.push_back(smv);

            ref_idx += op_len;
            query_idx += op_len;
            genomic_pos += op_len;
        }
        else {
            ref_idx += op_len;
            query_idx += op_len;
            genomic_pos += op_len;
        }

    }
    
    return variants;   
}

/*
 The Ratcliff-Obershelp algorithm copied from https://github.com/wernsey/miscsrc 
*/  
uint16_t seq_smlrty_recursive(const char* a, int alen, const char* b, int blen) {
    uint16_t i, j, k, l, p = 0, q = 0, len =0, left = 0, right = 0;
    
    for (i = 0; i < alen - len; i++) {
        for (j = 0; j < blen - len; j++) {
            if (a[i] == b [j] && a[i + len] == b[j + len]) {
                for (k = i + 1, l = j + 1; a[k] == b[l] && k < alen && l < blen; k++, l++);
                
                if (k - i > len) {
                    p = i;
                    q = j;
                    len = k - i;
                }  
            }
        }
    }
    
    if (len == 0) {
        return 0;
    }
    
    if (p != 0  && q != 0) {
        left = seq_smlrty_recursive(a, p, b, q);
    }
    
    i = (p + len);
    alen -= i;
    j = (q + len);
    blen -= j;
    
    if (alen != 0 && blen != 0) {
        right = seq_smlrty_recursive(a + i, alen, b + j, blen);
    }
   
    return len + left + right;
} 


double sequence_similarity(const char* a, const char* b) {
     
     uint32_t alen, blen;

     alen = strlen(a);
     blen = strlen(b);

     if (alen == 0 || blen == 0) {
         return 0;
     }

     return (seq_smlrty_recursive(a, alen, b, blen) * 2.0) / (alen + blen);
}





