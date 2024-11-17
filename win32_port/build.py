import asyncio
import subprocess
import hashlib
import os

obj_files = []

ignorefiles = [
    "missing_gcc_functions.c",
    "ll.c",
    "xprintf.c",
    "ovl_Boss_Ganon.c",
    "ovl_Boss_Ganon2.c",
    "z_file_nameset_data.c",
    "z_lmap_mark_data_mq.c",
    "z_map_mark_data_mq.c",
    "getmemsize.c",
    "initialize.c",
    "sys_cfb.c",
    "sqrtf.c", # use cruntime instead

    # disable _gc for N64 builds, replace with _n64 for GameCube builds
    "loadfragment2_gc.c",
    "load_gc.c",
    "logseverity_gc.c",
    "relocation_gc.c",
    "__osMalloc_gc.c",    
]

async def compile_file(path):
    suffix = '_' + hashlib.sha1(str.encode(path)).hexdigest()[:6] + '.obj'
    orig_filename = os.path.basename(path).split('/')[-1]
    filename = orig_filename.replace('.c', suffix)
    
    if orig_filename in ignorefiles:
        bfile = 'build/' + filename
        if os.path.exists(bfile):
            os.remove(bfile)
        return

    if filename in obj_files:
        print(filename + " is already compiled")
        exit()
    obj_files.append(filename)
    
    recomp = True
    try:
        compile_time = os.path.getmtime('build/' + filename)
        source_time = os.path.getmtime(path)
        recomp = source_time > compile_time
    except:
        pass
    
    if recomp:
        proc = subprocess.Popen(["build.bat", '../'+path, "-c", "-FS", "-Fo" + filename])
        proc.wait()
        if proc.returncode:
            print(path + ": compilation exited with code " + str(proc.returncode))
            exit()


async def compile_dir(directory):
    for dirpath, dnames, fnames in os.walk(directory):
        for f in fnames:
            if not f.endswith(".inc.c") and f.endswith(".c"):
                path = os.path.join(dirpath, f)
                asyncio.create_task(compile_file(path))
    

async def main():
    asyncio.create_task(compile_dir("../src/audio"))
    asyncio.create_task(compile_dir("../src/buffers"))
    asyncio.create_task(compile_dir("../src/code"))
    asyncio.create_task(compile_dir("../src/dmadata"))
    asyncio.create_task(compile_dir("../src/elf_message"))
    asyncio.create_task(compile_dir("../src/n64dd"))
    asyncio.create_task(compile_dir("../src/libc"))
    asyncio.create_task(compile_dir("../src/libc64"))
    asyncio.create_task(compile_dir("../src/libu64"))
    asyncio.create_task(compile_dir("../src/libultra/gu"))
    asyncio.create_task(compile_dir("../src/libultra/libc"))
    asyncio.create_task(compile_dir("../src/overlays"))
    asyncio.create_task(compile_file("../src/boot/z_std_dma.c"))
    asyncio.create_task(compile_file("../src/boot/yaz0.c"))
    asyncio.create_task(compile_file("../src/libultra/io/vimodepallan1.c"))
    asyncio.create_task(compile_file("../src/libultra/io/vimodentsclan1.c"))
    asyncio.create_task(compile_file("../src/libultra/io/vimodefpallan1.c"))
    asyncio.create_task(compile_dir("../extracted/pal-1.0/assets/misc"))
    asyncio.create_task(compile_dir("../extracted/pal-1.0/assets/objects"))
    asyncio.create_task(compile_dir("../extracted/pal-1.0/assets/n64dd"))
    asyncio.create_task(compile_dir("../extracted/pal-1.0/assets/overlays"))
    asyncio.create_task(compile_dir("../extracted/pal-1.0/assets/scenes"))
    asyncio.create_task(compile_dir("../extracted/pal-1.0/assets/textures"))
    asyncio.create_task(compile_dir("code"))

    all_tasks = asyncio.all_tasks()
    current_task = asyncio.current_task()
    all_tasks.remove(current_task)
    await asyncio.wait(all_tasks)

    print("Compilation done, linking:")
    # print(' '.join(["cd", "bu ild", "&&", "cl", "build.obj"] + object_files))
    subprocess.Popen(["cl", "build/*.obj", "-Feoot.exe", "-Od", "-Zi", "-link user32.lib gdi32.lib opengl32.lib winmm.lib"])

asyncio.run(main())