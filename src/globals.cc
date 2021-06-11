/// 786

/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.

/// Author: inumanag

/******************************************************************************/

#include "globals.h"

/******************************************************************************/

using namespace Globals;

int Search::KMER_SIZE = 12;
int Search::WINDOW_SIZE = 16;
int Search::MIN_UPPERCASE = Search::KMER_SIZE;

double Search::MAX_ERROR = 0.30;
double Search::MAX_EDIT_ERROR = 0.15;
double Search::GAP_FREQUENCY = 0.005;
int Search::MIN_READ_SIZE = KB * (1 - Search::MAX_ERROR); // 700 by default

int Align::MATCH = 5;
int Align::MISMATCH = -4;
int Align::GAP_OPEN = -40;
int Align::GAP_EXTEND = -1;

int Chain::MAX_CHAIN_GAP = Search::MAX_ERROR * Search::MIN_READ_SIZE;

double Extend::RATIO = 5;
int Extend::MAX_EXTEND = 15 * KB;
int Extend::MERGE_DIST = 250;

int Stats::MAX_OK_GAP = -1;
int Stats::MIN_SPLIT_SIZE = KB;
int Stats::MIN_UPPERCASE = 100;
double Stats::MAX_SCALED_ERROR = 0.5;

const int Search::MAX_SD_SIZE = 1 * 1024 * 1024; /// 1MB at most
const int Align::MAX_KSW_SEQ_LEN = 60 * KB;
const int Chain::MIN_UPPERCASE_MATCH = 90;
const int Chain::MATCH_CHAIN_SCORE = 4;
const int Chain::Refine::MIN_READ = 900;       // Minimal refined read size
const int Chain::Refine::SIDE_ALIGN = 500;
const int Chain::Refine::MAX_GAP = 10 * KB; // Max gap during refining process

const int Stats::MIN_ASSEMBLY_GAP_SIZE = 100;
const int Stats::BIG_OVERLAP_THRESHOLD = 100;



const bool Internal::DoUppercase = true;
const bool Internal::DoUppercaseSeeds = true;
const bool Internal::DoQgram = true;


