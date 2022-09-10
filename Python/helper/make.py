import subprocess
import argparse

def compile(path : str , exe : str = "Main"):
    # redirect stdout, stderr to a file
    subprocess.call(f"javac {path}/*.java", shell=True)
    subprocess.call(f"java {path}/{exe}.java", shell=True)

def clean(path : str = "*" ):
    subprocess.call(f"rm -rf {path}/*.class", shell=True)

parser = argparse.ArgumentParser(description="A simple python script to compile and run java files")
parser.add_argument("path", help="The path to the java file" , type=str , nargs="?" )
parser.add_argument("-c", "--clean", help="Clean the directory",  action="store_true")
parser.add_argument("-e", "--executable", help="The name of the executable file", type=str)
parser.add_argument("-z", "--zip", help="zip current directory for handle in the assignment" , action="store_true" )
args = parser.parse_args()


if args.zip is True:
    clean()
    subprocess.call(f"zip -r {args.path} . -x .DS_Store" , shell=True)
    exit()

clean(args.path)

if args.executable == None:
    compile(args.path )
else:
    compile(args.path, args.executable)


if args.clean is True:
    clean(args.path)