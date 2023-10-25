#!/bin/env python3

import os,sys,re 
import shutil
import struct
import argparse
import subprocess

def read_gnu_triple(library):
  #TODO: Support Non ELF Binaries use 
  # objdump -h build-aarch64-linux-gnuA/artifacts/bin/mohses_module_manager  | grep format
  # Call the appropriate read_<format> function based on results
  # Ensure all subsequenet libraries match format

  f=open(library, "rb")
  f.seek(18)
  e_machine = f.read(2);
  e_machine = struct.unpack('h',e_machine)[0]
  f.close()
 
  EM_X86_64 = 62
  EM_ARM = 40
  EM_AARCH64 = 183 

  triple = ("x86_64" if EM_X86_64 == e_machine else "armv7" 
                     if EM_ARM == e_machine else "aarch64"
                     if EM_AARCH64 == e_machine  else "unknown")
  triple += f"-{sys.platform}"
  triple += f"-gnu"

  return triple

def read_library_rpath(library):
  #TODO: Support Non ELF Binaries use 
  # objdump -h build-aarch64-linux-gnuA/artifacts/bin/mohses_module_manager  | grep format
  # Call the appropriate read_<format> function based on results
  # Ensure all subsequenet libraries match format

  #readelf  -h -d build-aarch64-linux-gnu/artifacts/bin/mohses_module_manager | grep NEEDED  | awk '{ match($5, /\[(.*)\]/, m);  if(m[1] != "") print m[1] }'
  objdump = subprocess.run(["readelf", "-d", f"{library}"], 
                           universal_newlines=True, capture_output=True, text=True)
  if objdump.stderr:
   print (f"Error running objdump on this system.\n Error:\n {objdump.stderr}")
   return set()
  #TODO: Handle systems that use REQUIRED instead of NEEDED
  grep = subprocess.run(['grep', 'RUNPATH'], 
                        universal_newlines=True, capture_output=True, input=objdump.stdout)
  if grep.stderr:
   print (f"Error running grep on this system.\n Error:\n {grep.stderr}")
   return set()
  #TODO: Regex Test output and process according to format
  paths = set()
  rex = re.compile('\[(.*)\]', re.IGNORECASE)
  for line in grep.stdout.splitlines():
      columns= re.split('\s+', line)
      path = rex.match(columns[5])
      if path[1]:
          runtime_path  = path[1]
          runtime_path_segments = re.split(r'[:;]', runtime_path)
          for segment in runtime_path_segments:
              possible_entry = segment.replace("$ORIGIN", os.path.basename(library))
              if os.path.exists(possible_entry) and os.path.isdir(possible_entry):
                  paths.add(possible_entry)
  return paths

def read_needed_libraries(library):
  #TODO: Support Non ELF Binaries use 
  # objdump -h build-aarch64-linux-gnuA/artifacts/bin/mohses_module_manager  | grep format
  # Call the appropriate read_<format> function based on results
  # Ensure all subsequenet libraries match format

  #readelf  -h -d build-aarch64-linux-gnu/artifacts/bin/mohses_module_manager | grep NEEDED  | awk '{ match($5, /\[(.*)\]/, m);  if(m[1] != "") print m[1] }'
  objdump = subprocess.run(["readelf", "-d", f"{library}"], 
                           universal_newlines=True, capture_output=True, text=True)
  if objdump.stderr:
   print (f"Error running objdump on this system.\n Error:\n {objdump.stderr}")
   return set()
  #TODO: Handle systems that use REQUIRED instead of NEEDED
  grep = subprocess.run(['grep', 'NEEDED'], 
                        universal_newlines=True, capture_output=True, input=objdump.stdout)
  if grep.stderr:
   print (f"Error running grep on this system.\n Error:\n {grep.stderr}")
   return set()

  libs = set()
  rex = re.compile('\[(.*)\]', re.IGNORECASE)
  for line in grep.stdout.splitlines():
      split = re.split('\s+', line)
      lib = rex.match(split[5])

      if lib[1]:
          libs.add(lib[1])
  return libs

def find_library(library, paths, triple):
  if os.path.isfile(library):
    return library
  for path in paths:
    test_path = f"{path}/{library}"
    if os.path.isfile(test_path) and triple == read_gnu_triple(test_path):
       return test_path
  return None

def fixup_bundle(app, libs, paths, destination, dryrun):
  if not os.path.isfile(app) :
    print(f"Cannot fixup non existant {app}")
    return


  required_libraries = [] 
  work_queue = read_needed_libraries(app)
  toolchain  = read_gnu_triple(app)

  path_queue = set()
  if paths:
    path_queue = set(re.split(r'[:;]',paths))
    path_queue = path_queue.union(read_library_rpath(app))
    path_queue = path_queue.union([
        f"/usr/{toolchain}/lib",
        f"/usr/lib/{toolchain}/",
        f"/usr/local/{toolchain}/lib",
        f"/usr/local/lib/{toolchain}/",
        ])

  if libs:
   work_queue.union(set(libs))

  print(f"""
  -- app='{app}'
  -- libs='{work_queue}'
  -- dirs='{path_queue}'
  """)

  while work_queue:
     library_name = work_queue.pop() 
     library_location = find_library(library_name,path_queue,toolchain)
     if library_location:
       path_queue = path_queue.union(read_library_rpath(library_location))

       additional_libraries = read_needed_libraries(library_location)
       additional_libraries.discard(library_location)
       work_queue.union(additional_libraries)
       required_libraries.append(library_location)
     else:
       print(f"Error unable to find {library_name}")

  for library in required_libraries:
    print (f"\t {library} --> {destination}")
    if not dryrun:
     shutil.copy2( library, destination)
    

def main(argc, argv):
  print (f"{argc} {argv}")
  parser = argparse.ArgumentParser(prog='fixup_bundle', 
       description= f"""
       fixup_bundle is designed to work like CMakes fixup_bundle script for cross compilation
       process like ldd and otool used by CMake only work for native applications. This process instead
       leans on objdump to validate the NEEDED and REQUIRED libraries and place them in the appropriate
       dirs. 
       """,
       usage='%(prog)s [options]')
  parser.add_argument('app',  nargs='+', help="List of objdump-able files to be fixedup")
  parser.add_argument('--libs', nargs='+', help="List of libraries that must be found even if not found by objdump")
  parser.add_argument('--dirs', help="List of alternative non standard search locations. be provided as a UNIX concatinated path.")
  parser.add_argument('-d', '--dryrun',  action='store_true', help="Show libraries that would be copied, but do not actually preform the fixup.")
  parser.add_argument('--outdir', help="Allows overriding the default bundle location." )
  parser.add_argument('--hints', nargs='+', help="Foreach dir in dirs. Each hint provided will be appended and tested as well.  Useful for testing architecture subdirectories" )
  args = parser.parse_args()

  dirs = args.dirs #TODO: Support Hints
  libs = args.libs

  if not args.app:
      print (parser.print_help())

  #TODO: Support output_dir
  for app in  args.app:
    if args.outdir:
     if os.isabs(args.outdir):
        destination = args.outdir
     else:
        destination = f"{os.path.dirname(app)}/{args.outdir}/" 
    else:
     destination = f"{os.path.dirname(app)}/"
    fixup_bundle(app, libs, dirs, destination, args.dryrun)
  pass

if __name__ == "__main__":
  main(sys.argv[0], sys.argv[1:])
