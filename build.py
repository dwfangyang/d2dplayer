import subprocess
import os
import sys

destdir = os.path.join(os.getcwd(),'../build')
#print destdir
if not os.path.exists(destdir):
    os.makedirs(destdir)
command_list = [
	'qmake',
	'-r',
	'-tp',
	'vc'
]
command_list.append(os.path.join(os.getcwd(),'./cpp/d2dplayer.pro'))
subprocess.call(command_list, cwd="../build")
os.chdir("../d2dplayer")
subprocess.call('cd & xcopy cpp\\dependency\\* ..\\build\\mainapp\\release /Y', shell = True);   #execute dos cmd, /Y implies to overwrite file with no warning
##subprocess.Popen("qmake -r -tp vc d2dplayer.pro")