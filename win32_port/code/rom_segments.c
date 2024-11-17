#include "global.h"

// #include "z64dma.h"
// #include "attributes.h"
// #include "z64audio.h"
// #include "versions.h"

// DMA data
#define DEFINE_DMA_ENTRY(name, _1)        \
    u8 _##name##SegmentRomStart[] = { 0 }; \
    u8 _##name##SegmentRomEnd[] = { 0 }; \
    u8 _##name##SegmentStart[] = { 0 }; \
    u8 _##name##SegmentEnd[] = { 0 };

#include "tables/dmadata_table.h"

#undef DEFINE_DMA_ENTRY

// Sequences
#define DEFINE_SEQUENCE(name, seqId, storageMedium, cachePolicy, seqFlags) \
    u8 name##_Start[] = { 0 };                                              \
    u8 name##_Size[] = { 0 };
#define DEFINE_SEQUENCE_PTR(seqIdReal, seqId, storageMediumReal, cachePolicyReal, seqFlags) /*empty*/

#include "tables/sequence_table.h"

#undef DEFINE_SEQUENCE
#undef DEFINE_SEQUENCE_PTR


// Soundfont
#define DEFINE_SOUNDFONT(name, medium, cachePolicy, sampleBankNormal, sampleBankDD, nInstruments, nDrums, nSfx) \
    u8 name##_Start[] = { 0 };                                                                                   \
    u8 name##_Size[] = { 0 };

#include "assets/audio/soundfont_table.h"

#undef DEFINE_SOUNDFONT

// Samplebank
#define DEFINE_SAMPLE_BANK(name, medium, cachePolicy) \
    u8 name##_Start[] = { 0 };                         \
    u8 name##_Size[] = { 0 };
#define DEFINE_SAMPLE_BANK_PTR(index, medium, cachePolicy) /*empty*/

#include "assets/audio/samplebank_table.h"

#undef DEFINE_SAMPLE_BANK
#undef DEFINE_SAMPLE_BANK_PTR



#if 0

// dmadata Table definition
#define DEFINE_DMA_ENTRY(name, _1)           \
    {                                        \
        ROM_FILE(name),                      \
        (uintptr_t)_##name##SegmentRomStart, \
        0,                                   \
    },

DmaEntry gDmaDataTable[] = {
#include "tables/dmadata_table.h"
    { 0 },
};

#undef DEFINE_DMA_ENTRY

// Additional padding?
u8 sDmaDataPadding[0xF0] = { 0 };

// Symbol definition

extern AudioTable gSequenceTable;
#pragma weak gSequenceTable = sSequenceTableHeader

// Externs for table

#define DEFINE_SEQUENCE(name, seqId, storageMedium, cachePolicy, seqFlags) \
    u8 name##_Start[] = { 0 };                                              \
    u8 name##_Size[] = { 0 };
#define DEFINE_SEQUENCE_PTR(seqIdReal, seqId, storageMediumReal, cachePolicyReal, seqFlags) /*empty*/

#include "tables/sequence_table.h"

#undef DEFINE_SEQUENCE
#undef DEFINE_SEQUENCE_PTR

// Table header

NO_REORDER AudioTableHeader sSequenceTableHeader = {
// The table contains the number of sequences, count them with the preprocessor
#define DEFINE_SEQUENCE(name, seqId, storageMedium, cachePolicy, seqFlags) 1 +
#define DEFINE_SEQUENCE_PTR(seqIdReal, seqId, storageMediumReal, cachePolicyReal, seqFlags) 1 +

#include "tables/sequence_table.h"

#undef DEFINE_SEQUENCE
#undef DEFINE_SEQUENCE_PTR
    0,

    0,
    0x00000000,
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

// Table body

NO_REORDER AudioTableEntry sSequenceTableEntries[] = {
#define DEFINE_SEQUENCE(name, seqId, storageMedium, cachePolicy, seqFlags) \
    { (u32)name##_Start, (u32)name##_Size, (storageMedium), (cachePolicy), 0, 0, 0 },
#define DEFINE_SEQUENCE_PTR(seqIdReal, seqId, storageMediumReal, cachePolicyReal, seqFlags) \
    { (seqIdReal), 0, (storageMediumReal), (cachePolicyReal), 0, 0, 0 },

#include "tables/sequence_table.h"

#undef DEFINE_SEQUENCE
#undef DEFINE_SEQUENCE_PTR
};

#endif