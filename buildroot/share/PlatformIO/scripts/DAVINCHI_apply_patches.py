from os.path import join, isfile
from shutil import copyfile

Import("env")
# access to global construction environment
ROOT_DIR = join(env['PROJECT_DIR'], "buildroot", "share", "PlatformIO", "variants")
FRAMEWORK_DIR = env.PioPlatform().get_package_dir("framework-arduino-sam")
patchflag_path = join(FRAMEWORK_DIR, ".patching-done")

#print("ROOT_DIR: "+ROOT_DIR)
#print("FRAMEWORK_DIR"+join(FRAMEWORK_DIR, ".patching-done"))
#print("patchflag_path "+patchflag_path)

print("Patching files")

# patch file only if we didn't do it before
if not isfile(join(FRAMEWORK_DIR, ".patching-done")):
  target_file = join(FRAMEWORK_DIR, "cores","arduino","USB", "USBCore.cpp")
  patched_file = join(ROOT_DIR, "MARLIN_DAVINCI_PIOPatches", "USBCore.cpp")
  #print("patched_file " + patched_file)
  #print("target_file " + target_file)
  assert isfile(target_file) and isfile(patched_file)
  copyfile(patched_file, target_file)
  target_file = join(FRAMEWORK_DIR, "variants", "arduino_due_x", "variant.cpp")
  patched_file = join(ROOT_DIR, "MARLIN_DAVINCI_PIOPatches", "variant.cpp")
  #print("patched_file " + patched_file)
  #print("target_file " + target_file)
  assert isfile(target_file) and isfile(patched_file)
  copyfile(patched_file, target_file)

  def _touch(path):
    with open(path, "w") as fp:
      fp.write("")

  _touch(patchflag_path)
else:
  print("Files already patched")