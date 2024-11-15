import asyncio
import subprocess
import os

ignorefiles = [
    "missing_gcc_functions.obj",
    "ll.obj",
    "xprintf.obj",
    "z_boss_ganon.obj",
    "z_boss_ganon2.obj",
    "z_file_nameset_data.obj",
    "z_lmap_mark_data_mq.obj",
    "z_map_mark_data_mq.obj",
    # "dmadata.obj",
    # "sequence_table.obj",

    # disable _gc for N64 builds, replace with _n64 for GameCube builds
    "loadfragment2_gc.obj",
    "load_gc.obj",
    "logseverity_gc.obj",
    "relocation_gc.obj",
    "__osMalloc_gc.obj",    
]

async def compile_file(path):
    filename = os.path.basename(path).split('/')[-1].replace('.c', '.obj')
    if filename in ignorefiles:
        bfile = 'build/' + filename
        if os.path.exists(bfile):
            os.remove(bfile)
        return
    
    recomp = True
    try:
        compile_time = os.path.getmtime('build/' + filename)
        source_time = os.path.getmtime(path)
        recomp = source_time > compile_time
    except:
        pass
    
    if recomp:
        proc = subprocess.Popen(["build.bat", '../'+path, "-c", "-FS"])
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
    asyncio.create_task(compile_dir("../src"))
    asyncio.create_task(compile_dir("../extracted/pal-1.0/assets"))
    asyncio.create_task(compile_dir("code"))

    all_tasks = asyncio.all_tasks()
    current_task = asyncio.current_task()
    all_tasks.remove(current_task)
    await asyncio.wait(all_tasks)

    print("Compilation done, linking:")
    # print(' '.join(["cd", "bu ild", "&&", "cl", "build.obj"] + object_files))
    subprocess.Popen(["cl", "build/*.obj"])

asyncio.run(main())