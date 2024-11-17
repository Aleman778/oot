@echo off

IF NOT EXIST build mkdir build
pushd build

set compiler_flags=

rem ROM configration
set baserom=pal-1.0
set compiler_flags=-DOOT_VERSION=PAL_1_0 -DPLATFORM_GC=0 -DPLATFORM_N64=1 %compiler_flags%

rem General compiler flags
set compiler_flags=-std:c11 -nologo %compiler_flags%
set compiler_flags=-D_LANGUAGE_C -DF3DEX_GBI_2 -D_SIZE_T %compiler_flags%

rem Debug compiler flags
set compiler_flags=-Od -Zi -MT %compiler_flags%

rem Release compiler flags
rem set compiler_flags=-DOOT_DEBUG=1 %compiler_flags%
set compiler_flags=-DOOT_DEBUG=0 %compiler_flags%

rem Include directives
set compiler_flags=-I ../../ -I ../../src -I ../../include -I ../../include/libc %compiler_flags%
set compiler_flags=-I ../../extracted/%baserom% -I ../../build/%baserom% %compiler_flags%

rem Disable compiler complaints
set compiler_flags=-wd4311 -wd4700 -wd4312 -wd4716 -wd4068 -wd4715 %compiler_flags%

rem Make DMA data (only needed once)
rem cl ../tools/mkdmadata.c ../tools/spec.c ../tools/util.c
rem cl -EP ../spec > spec2
rem mkdmadata.exe spec2 test.h test.txt

rem Make relocation tool (only needed once
rem cl ../tools/reloc_prereq.c ../tools/spec.c ../tools/util.c

cl %* %compiler_flags%

popd

EXIT /B %ERRORLEVEL%