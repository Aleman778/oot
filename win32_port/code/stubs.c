#include "global.h"

// Stubs functions, if they are still here it probably wasn't used anywhere and can remain empty
void __osPiCreateAccessQueue(void) { }
void __osPiGetAccess(void) { }
void __osPiRelAccess(void) { }
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flag) { return 0; }
void osStopThread(OSThread* thread) { }
void osViExtendVStart(u32 value) { }
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flag) { return 0; }
void __osInitialize_common(void) { }
void __osInitialize_autodetect(void) { }
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
void __osSetWatchLo(u32 value) { }

s32 osPfsFreeBlocks(OSPfs* pfs, s32* leftoverBytes) { return 0; }
void guScale(Mtx* m, f32 x, f32 y, f32 z) { }
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
void guPerspectiveF(f32 mf[4][4], u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) { }
void guPerspective(Mtx* m, u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) { }
s32 __osSpRawStartDma(s32 direction, void* devAddr, void* dramAddr, u32 size) { return 0; }
s32 __osSiRawStartDma(s32 dir, void* addr) { return 0; }
void osSpTaskYield(void) { }
s32 __osPfsGetNextPage(OSPfs* pfs, u8* bank, __OSInode* inode, __OSInodeUnit* page) { return 0; }
s32 osPfsReadWriteFile(OSPfs* pfs, s32 fileNo, u8 flag, s32 offset, s32 size, u8* data) { return 0; }
s32 __osPfsGetStatus(OSMesgQueue* queue, s32 channel) { return 0; }
void __osPfsRequestOneChannel(s32 channel, u8 cmd) { }
void __osPfsGetOneChannelData(s32 channel, OSContStatus* contData) { }
void guMtxIdentF(f32 mf[4][4]) { }
void guLookAtF(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp) { }
void guLookAt(Mtx* out, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp) { }
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
void guMtxL2F(f32 mf[4][4], Mtx* m) { }
s32 osPfsFindFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32* fileNo) { return 0; }
s32 osAfterPreNMI(void) { return 0; }
s32 osContStartQuery(OSMesgQueue* mq) { return 0; }
void osContGetQuery(OSContStatus* data) { }
void guLookAtHiliteF(f32 mf[4][4], LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt,
                     f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 hiliteWidth,
                     s32 hiliteHeight) { }
void guLookAtHilite(Mtx* m, LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp,
                    f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 hiliteWidth,
                    s32 hiliteHeight) { }
u32 __osSpDeviceBusy(void) { return 0; }
void guMtxIdent(Mtx* out) { }
void guPositionF(f32 mf[4][4], f32 rot, f32 pitch, f32 yaw, f32 scale, f32 x, f32 y, f32 z) { }
void guPosition(Mtx* out, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 zf32) { }
OSYieldResult osSpTaskYielded(OSTask* task) { return 0; }
void guRotateF(f32 m[4][4], f32 a, f32 x, f32 y, f32 z) { }
void guRotate(Mtx* out, f32 a, f32 x, f32 y, f32 z) { }
s32 osAiSetFrequency(u32 frequency) { return 0; }
OSThread* __osGetActiveQueue(void) { return 0; }
void guNormalize(f32* x, f32* y, f32* z) { }
u32 osDpGetStatus(void) { return 0; }
void osDpSetStatus(u32 status) { }
s32 osPfsDeleteFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName) { return 0; }
s32 __osPfsReleasePages(OSPfs* pfs, __OSInode* inode, u8 initialPage, u8 bank, __OSInodeUnit* finalPage) { return 0; }
void guOrthoF(f32 out[4][4], f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale) { }
void guOrtho(Mtx* out, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale) { }
void osViSetEvent(OSMesgQueue* mq, OSMesg msg, u32 retraceCount) { }
s32 osPfsIsPlug(OSMesgQueue* mq, u8* pattern) { return 0; }
void __osPfsRequestData(u8 cmd) { }
void __osPfsGetInitData(u8* pattern, OSContStatus* contData) { }
void guS2DInitBg(union uObjBg* bg) { }
s32 __osPfsSelectBank(OSPfs* pfs, u8 bank) { return 0; }
s32 osContSetCh(u8 ch) { return 0; }
s32 osPfsFileState(OSPfs* pfs, s32 fileNo, OSPfsState* state) { return 0; }
s32 osPfsInitPak(OSMesgQueue* queue, OSPfs* pfs, s32 channel) { return 0; }
s32 __osPfsCheckRamArea(OSPfs* pfs) { return 0; }
s32 osPfsChecker(OSPfs* pfs) { return 0; }
s32 func_80105788(OSPfs* pfs, __OSInodeCache* cache) { return 0; }
s32 func_80105A60(OSPfs* pfs, __OSInodeUnit fpage, __OSInodeCache* cache) { return 0; }
u32 osAiGetLength(void) { return 0; }
void guTranslate(Mtx* m, f32 x, f32 y, f32 z) { }
s32 __osContRamWrite(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer, s32 force) { return 0; }
s32 __osContRamRead(OSMesgQueue* ctrlrqueue, s32 channel, u16 addr, u8* data) { return 0; }
u8 __osContAddressCrc(u16 addr) { return 0; }
u8 __osContDataCrc(u8* data) { return 0; }
s32 osSetTimer(OSTimer* timer, OSTime countdown, OSTime interval, OSMesgQueue* mq, OSMesg msg) { return 0; }
u32 __osSpGetStatus(void) { return 0; }
void __osSpSetStatus(u32 status) { }
void osWritebackDCacheAll(void) { }
OSThread* __osGetCurrFaultedThread(void) { return 0; }
void guMtxF2L(f32 mf[4][4], Mtx* m) { }
void* osViGetCurrentFramebuffer(void) { return 0; }
s32 __osSpSetPc(void* pc) { return 0; }

OSIntMask osGetIntMask(void) { return 0; }
OSIntMask osSetIntMask(OSIntMask mask) { return 0; }

// libc stbs
void bzero(void* __s, int __n) { }
int bcmp(const void* __sl, const void* __s2, int __n) { return 0; }
void bcopy(const void* __src, void* __dest, int __n) { }

void __osSetHWIntrRoutine(OSHWIntr intr, s32 (*callback)(void), void* sp) { }
void __osGetHWIntrRoutine(OSHWIntr intr, s32 (**callbackOut)(void), void** spOut) { }

void* __builtin_alloca(size_t size) { return 0; }

f32 __builtin_fabsf(f32 value) {
    if (value < 0) return -value;
    return value;
}
