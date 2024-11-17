#include "global.h"
#include "ultra64/leo.h"

// Stubs functions, if they are still here it probably wasn't used anywhere and can remain empty
void __osPiCreateAccessQueue(void) { }
void __osPiGetAccess(void) { }
void __osPiRelAccess(void) { }
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flag) { return 0; }
void osStopThread(OSThread* thread) { }
void osViExtendVStart(u32 value) { }
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flag) { return 0; }
void osInitialize() { }
void __osEnqueueAndYield(OSThread** thread) { }
void __osEnqueueThread(OSThread** threadA, OSThread* threadB) { }
OSThread* __osPopThread(OSThread** thread) { return 0; }
void __osDispatchThread(void) { }
void __osCleanupThread(void) { }
void __osDequeueThread(OSThread** queue, OSThread* thread) { }
void osDestroyThread(OSThread* thread) { }
void osCreateThread(OSThread* thread, OSId id, void (*entry)(void*), void* arg, void* sp, OSPri pri) { }
void __osSetSR(u32 value) { }
u32 __osGetSR(void) { return 0; }
void osWritebackDCache(void* vaddr, s32 nbytes) { }
void* osViGetNextFramebuffer(void) { return 0; }
void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQueue, OSMesg* cmdBuf, s32 cmdMsgCnt) { }
void __osDevMgrMain(void* arg) { }
s32 __osPiRawStartDma(s32 dir, u32 cartAddr, void* dramAddr, size_t size) { return 0; }
u32 osVirtualToPhysical(void* vaddr) { return 0; }
void osViBlack(u8 active) { }
s32 __osSiRawReadIo(void* devAddr, u32* dst) { return 0; }
OSId osGetThreadId(OSThread* thread) { return 0; }
void osViSetMode(OSViMode* mode) { }
u32 __osProbeTLB(void* ptr) { return 0; }
u32 osGetMemSize(void) { return 0; }
void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg msg) { }
void osUnmapTLBAll(void) { }
s32 osEPiStartDma(OSPiHandle* handle, OSIoMesg* mb, s32 direction) { return 0; }
void osInvalICache(void* vaddr, s32 nbytes) { }
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msg, s32 count) { }
void osInvalDCache(void* vaddr, s32 nbytes) { }
s32 __osSiDeviceBusy(void) { return 0; }
s32 osJamMesg(OSMesgQueue* mq, OSMesg msg, s32 flag) { return 0; }
void osSetThreadPri(OSThread* thread, OSPri pri) { }
OSPri osGetThreadPri(OSThread* thread) { return 0; }
s32 __osEPiRawReadIo(OSPiHandle* handle, u32 devAddr, u32* data) { return 0; }
void osViSwapBuffer(void* frameBufPtr) { }
s32 __osEPiRawStartDma(OSPiHandle* handle, s32 direction, u32 cartAddr, void* dramAddr, size_t size) { return 0; }
OSTime osGetTime(void) { return 0; }
void osSetTime(OSTime time) { }
void __osTimerServicesInit(void) { }
void __osTimerInterrupt(void) { }
void __osSetTimerIntr(OSTime time) { }
OSTime __osInsertTimer(OSTimer* timer) { return 0; }
u32 osGetCount(void) { return 0; }
void __osSetCompare(u32 value) { }
s32 __osDisableInt(void) { return 0; }
void __osRestoreInt(s32 value) { }
void __osViInit(void) { }
void __osViSwapContext(void) { }
OSMesgQueue* osPiGetCmdQueue(void) { return 0; }
s32 osEPiReadIo(OSPiHandle* handle, u32 devAddr, u32* data) { return 0; }
void osViSetSpecialFeatures(u32 func) { }
OSPiHandle* osCartRomInit(void) { return 0; }
void __osSetFpcCsr(u32 value) { }
u32 __osGetFpcCsr(void) { return 0; }
s32 osEPiWriteIo(OSPiHandle* handle, u32 devAddr, u32 data) { return 0; }
void osMapTLBRdb(void) { }
void osYieldThread(void) { }
u32 __osGetCause(void) { return 0; }
s32 __osEPiRawWriteIo(OSPiHandle* handle, u32 devAddr, u32 data) { return 0; }
s32 __osSiRawWriteIo(void* devAddr, u32 val) { return 0; }
void osCreateViManager(OSPri pri) { }
OSViContext* __osViGetCurrentContext(void) { return 0; }
void osStartThread(OSThread* thread) { }
void osViSetYScale(f32 scale) { }
void osViSetXScale(f32 value) { }
void ViConfig_UpdateVi(u32 black) { }
void ViConfig_UpdateBlack(void) { }
void __osSetWatchLo(u32 value) { }

s32 osPfsFreeBlocks(OSPfs* pfs, s32* leftoverBytes) { return 0; }
OSTask* _VirtualToPhysicalTask(OSTask* intp) { return 0; }
void osSpTaskLoad(OSTask* intp) { }
void osSpTaskStartGo(OSTask* tp) { }
void __osSiCreateAccessQueue(void) { }
void __osSiGetAccess(void) { }
void __osSiRelAccess(void) { }
s32 osContInit(OSMesgQueue* mq, u8* ctlBitfield, OSContStatus* status) { return 0; }
void __osContGetInitData(u8* ctlBitfield, OSContStatus* data) { }
void __osPackRequestData(u8 poll) { }
s32 osContStartReadData(OSMesgQueue* mq) { return 0; }
void osContGetReadData(OSContPad* contData) { }
void __osPackReadData(void) { }
s32 __osSpRawStartDma(s32 direction, void* devAddr, void* dramAddr, u32 size) { return 0; }
s32 __osSiRawStartDma(s32 dir, void* addr) { return 0; }
void osSpTaskYield(void) { }
s32 __osPfsGetNextPage(OSPfs* pfs, u8* bank, __OSInode* inode, __OSInodeUnit* page) { return 0; }
s32 osPfsReadWriteFile(OSPfs* pfs, s32 fileNo, u8 flag, s32 offset, s32 size, u8* data) { return 0; }
s32 __osPfsGetStatus(OSMesgQueue* queue, s32 channel) { return 0; }
void __osPfsRequestOneChannel(s32 channel, u8 cmd) { }
void __osPfsGetOneChannelData(s32 channel, OSContStatus* contData) { }
s32 osPfsAllocateFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32 fileSize, s32* fileNo) { return 0; }
s32 __osPfsDeclearPage(OSPfs* pfs, __OSInode* inode, s32 fileSizeInPages, s32* startPage, u8 bank, s32* decleared,
                       s32* finalPage) { return 0; }
s32 osStopTimer(OSTimer* timer) { return 0; }
u16 __osSumcalc(u8* ptr, s32 length) { return 0; }
s32 __osIdCheckSum(u16* ptr, u16* checkSum, u16* idSum) { return 0; }
s32 __osRepairPackId(OSPfs* pfs, __OSPackId* badid, __OSPackId* newid) { return 0; }
s32 __osCheckPackId(OSPfs* pfs, __OSPackId* check) { return 0; }
s32 __osGetId(OSPfs* pfs) { return 0; }
s32 __osCheckId(OSPfs* pfs) { return 0; }
s32 __osPfsRWInode(OSPfs* pfs, __OSInode* inode, u8 flag, u8 bank) { return 0; }
s32 osPfsFindFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32* fileNo) { return 0; }
s32 osAfterPreNMI(void) { return 0; }
s32 osContStartQuery(OSMesgQueue* mq) { return 0; }
void osContGetQuery(OSContStatus* data) { }
u32 __osSpDeviceBusy(void) { return 0; }
OSYieldResult osSpTaskYielded(OSTask* task) { return 0; }
s32 osAiSetFrequency(u32 frequency) { return 0; }
OSThread* __osGetActiveQueue(void) { return 0; }
u32 osDpGetStatus(void) { return 0; }
void osDpSetStatus(u32 status) { }
s32 osPfsDeleteFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName) { return 0; }
s32 __osPfsReleasePages(OSPfs* pfs, __OSInode* inode, u8 initialPage, u8 bank, __OSInodeUnit* finalPage) { return 0; }
void osViSetEvent(OSMesgQueue* mq, OSMesg msg, u32 retraceCount) { }
s32 osPfsIsPlug(OSMesgQueue* mq, u8* pattern) { return 0; }
void __osPfsRequestData(u8 cmd) { }
void __osPfsGetInitData(u8* pattern, OSContStatus* contData) { }
s32 __osPfsSelectBank(OSPfs* pfs, u8 bank) { return 0; }
s32 osContSetCh(u8 ch) { return 0; }
s32 osPfsFileState(OSPfs* pfs, s32 fileNo, OSPfsState* state) { return 0; }
s32 osPfsInitPak(OSMesgQueue* queue, OSPfs* pfs, s32 channel) { return 0; }
s32 __osPfsCheckRamArea(OSPfs* pfs) { return 0; }
s32 osPfsChecker(OSPfs* pfs) { return 0; }
s32 func_80105788(OSPfs* pfs, __OSInodeCache* cache) { return 0; }
s32 func_80105A60(OSPfs* pfs, __OSInodeUnit fpage, __OSInodeCache* cache) { return 0; }
u32 osAiGetLength(void) { return 0; }
s32 __osContRamWrite(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer, s32 force) { return 0; }
s32 __osContRamRead(OSMesgQueue* ctrlrqueue, s32 channel, u16 addr, u8* data) { return 0; }
u8 __osContAddressCrc(u16 addr) { return 0; }
u8 __osContDataCrc(u8* data) { return 0; }
s32 osSetTimer(OSTimer* timer, OSTime countdown, OSTime interval, OSMesgQueue* mq, OSMesg msg) { return 0; }
u32 __osSpGetStatus(void) { return 0; }
void __osSpSetStatus(u32 status) { }
void osWritebackDCacheAll(void) { }
OSThread* __osGetCurrFaultedThread(void) { return 0; }
void* osViGetCurrentFramebuffer(void) { return 0; }
s32 __osSpSetPc(void* pc) { return 0; }

OSPiHandle* osDriveRomInit(void) { return 0; }

OSIntMask osGetIntMask(void) { return 0; }
OSIntMask osSetIntMask(OSIntMask mask) { return 0; }

// libc stbs
void bzero(void* __s, int __n) {
    memset(__s, 0, __n);
}
int bcmp(const void* __sl, const void* __s2, int __n) { 
    return memcmp(__sl, __s2, __n);
 }
void bcopy(const void* __src, void* __dest, int __n) {
    memcpy(__src, __dest, __n);
}

void __osSetHWIntrRoutine(OSHWIntr intr, s32 (*callback)(void), void* sp) { }
void __osGetHWIntrRoutine(OSHWIntr intr, s32 (**callbackOut)(void), void** spOut) { }

void* __builtin_alloca(size_t size) { return 0; }

// Memory
#define MEMORY_SIZE 0x400000
u8* _buffersSegmentEnd = (u8*) 0x80000000;

// Variables.h
s32 osResetType;
u32 osMemSize = MEMORY_SIZE; // 4MB mode
OSPiHandle* gCartHandle;
OSPiHandle* __osPiTable;
s32 osTvType;
u8 osAppNMIBuffer[0x40];
AudioTable gSoundFontTable;
u8 gSequenceFontTable[] = { 0 };
u8 gSequenceTable[] = { 0 };
AudioTable gSampleBankTable;
OSMesgQueue gPiMgrCmdQueue;
u8 gViConfigModeType;
f32 __libm_qnan_f = 0.0f;

s32 B_80008EE0 = 0xAD090010; // Anti piracy check

s32 gCurrentRegion = 0;

// Graphics constants
u32 gViConfigFeatures = OS_VI_GAMMA_OFF | OS_VI_DITHER_FILTER_ON;
f32 gViConfigXScale = 1.0f;
f32 gViConfigYScale = 1.0f;

extern void __puts(const char* str);

int 
_Printf(PrintCallback callback, void* arg, const char* fmt, va_list ap) {
    __puts(fmt); // TODO: no arguments printed
    return 0;
}

void
osSyncPrintf(const char* fmt, ...) {
    __puts(fmt); // TODO: no arguments printed
}

f32
__builtin_fabsf(f32 value) {
    if (value < 0.0f) return -value;
    return value;
}

f64
__builtin_fabs(f64 value) {
    if (value < 0.0) return -value;
    return value;
}

// Data tables
u64 gMojiFontTLUTs[4][4];
u64 gMojiFontTex[1];

u64 rspbootTextStart[] = { 0 }, rspbootTextEnd[] = { 0 };

u64 cic6105TextStart[] = { 0 }, cic6105TextEnd[] = { 0 };

u64 aspMainTextStart[] = { 0 }, aspMainTextEnd[] = { 0 };
u64 aspMainDataStart[] = { 0 }, aspMainDataEnd[] = { 0 };

u64 gspF3DZEX2_NoN_PosLight_fifoTextStart[] = { 0 }, gspF3DZEX2_NoN_PosLight_fifoTextEnd[] = { 0 };
u64 gspF3DZEX2_NoN_PosLight_fifoDataStart[] = { 0 }, gspF3DZEX2_NoN_PosLight_fifoDataEnd[] = { 0 };

u64 gspS2DEX2d_fifoTextStart[] = { 0 }, gspS2DEX2d_fifoTextEnd[] = { 0 };
u64 gspS2DEX2d_fifoDataStart[] = { 0 }, gspS2DEX2d_fifoDataEnd[] = { 0 };

u64 njpgdspMainTextStart[] = { 0 }, njpgdspMainTextEnd[] = { 0 };
u64 njpgdspMainDataStart[] = { 0 }, njpgdspMainDataEnd[] = { 0 };

u8 _n64ddSegmentBssStart[] = { 0 }, _n64ddSegmentBssEnd[] = { 0 };

u8 _codeSegmentBssStart[] = { 0 }, _codeSegmentBssEnd[] = { 0 };

// Memory
extern u8* _buffersSegmentEnd;
uintptr_t sSysCfbFbPtr[2];
uintptr_t sSysCfbEnd;
void SysCfb_Init(s32 n64dd) {
    sSysCfbEnd = (uintptr_t) _buffersSegmentEnd + osMemSize;
    sSysCfbFbPtr[0] = sSysCfbEnd;
    sSysCfbFbPtr[1] = sSysCfbEnd;
    
}

void SysCfb_Reset(void) {
    sSysCfbFbPtr[0] = 0;
    sSysCfbFbPtr[1] = 0;
    sSysCfbEnd = 0;
}

void* SysCfb_GetFbPtr(s32 idx) {
    if (idx < 2) {
        return (void*)sSysCfbFbPtr[idx];
    }
    return NULL;
}

void* SysCfb_GetFbEnd(void) {
    return (void*)sSysCfbEnd;
}


// Unknowns
UNK_TYPE D_06000000;
Mtx D_01000000;
UNK_TYPE D_0F000000;
u16 D_0E000000;

// LEO? (only for N64DD which I don't care about)
int LeoGetKAdr(int sjis) { return 0; }
int LeoGetAAdr(int code, int* dx, int* dy, int* cy) { return 0; }
int LeoGetAAdr2(u32 ccode, int* dx, int* dy, int* cy) { return 0; }
void LeoReset(void) { }
s32 LeoResetClear(void) { return 0; }

// Initialize routine
s32 LeoCreateLeoManager(OSPri comPri, OSPri intPri, OSMesg* cmdBuf, s32 cmdMsgCnt) { return 0; }
s32 LeoCJCreateLeoManager(OSPri comPri, OSPri intPri, OSMesg* cmdBuf, s32 cmdMsgCnt) { return 0; }
s32 LeoCACreateLeoManager(OSPri comPri, OSPri intPri, OSMesg* cmdBuf, s32 cmdMsgCnt) { return 0; }
u32 LeoDriveExist(void) { return 0; }

// Synchronous functions
s32 LeoClearQueue(void) { return 0; }
s32 LeoByteToLBA(s32 startlba, u32 nbytes, s32* lba) { return 0; }
s32 LeoLBAToByte(s32 startlba, u32 nlbas, s32* bytes) { return 0; }
s32 LeoReadCapacity(LEOCapacity* cap, s32 dir) { return 0; }
s32 LeoInquiry(LEOVersion* ver) { return 0; }
s32 LeoTestUnitReady(LEOStatus* status) { return 0; }

// Asynchronous functions
s32 LeoSpdlMotor(LEOCmd* cmdBlock, LEOSpdlMode mode, OSMesgQueue* mq) { return 0; }
s32 LeoSeek(LEOCmd* cmdBlock, u32 lba, OSMesgQueue* mq) { return 0; }
s32 LeoRezero(LEOCmd* cmdBlock, OSMesgQueue* mq) { return 0; }
s32 LeoReadWrite(LEOCmd* cmdBlock, s32 direction, u32 LBA, void* vAddr, u32 nLBAs, OSMesgQueue* mq) { return 0; }
s32 LeoReadDiskID(LEOCmd* cmdBlock, LEODiskID* vaddr, OSMesgQueue* mq) { return 0; }
s32 LeoSetRTC(LEOCmd* cmdBlock, LEODiskTime* RTCdata, OSMesgQueue* mq) { return 0; }
s32 LeoReadRTC(LEOCmd* cmdBlock, OSMesgQueue* mq) { return 0; }
s32 LeoModeSelectAsync(LEOCmd* cmdBlock, u32 standby, u32 sleep, OSMesgQueue* mq) { return 0; }

// Rumble Pak
s32 __osMotorAccess(OSPfs* pfs, s32 vibrate) { return 0; }
s32 osMotorInit(OSMesgQueue* ctrlrqueue, OSPfs* pfs, s32 channel) { return 0; }

// Cic
s32 osCicId;
void func_800014E8(void) { }
void CIC6105_AddFaultClient(void) { }
void CIC6105_RemoveFaultClient(void) { }
void func_80001640(void) { }
void func_80001720(void) { }

// Font routines
int LeoGetKAdr(int sjis);
int LeoGetAAdr(int code, int* dx, int* dy, int* cy);
int LeoGetAAdr2(u32 ccode, int* dx, int* dy, int* cy);

// Boot function
void LeoBootGame(void* entry);