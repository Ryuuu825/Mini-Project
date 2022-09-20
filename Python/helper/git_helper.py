import argparse
import subprocess
import sys

def colorize(color:str) -> str:
    if color == "red":
        return "\033[31m"
    elif color == "green":
        return "\033[32m"
    elif color == "yellow":
        return "\033[33m"
    elif color == "blue":
        return "\033[34m"
    elif color == "magenta":
        return "\033[35m"
    elif color == "cyan":
        return "\033[36m"
    elif color == "white":
        return "\033[37m"
    elif color == "reset":
        return "\033[0m"
    else:
        return ""

def get_repo_http_url(remote):
    url =  subprocess.check_output(f"git -C {git_path} remote get-url {remote}", shell=True).decode("utf-8").strip()
    if url.startswith("git@"):
        url = url.replace(":", "/")
        url = url.replace("git@", "https://")
        url = url.replace(".git", "")
    return url

def commit(commit_msg):
    subprocess.call(f"git -C {git_path} add .", shell=True)
    subprocess.call(f"git -C {git_path} commit -m \"{commit_msg}\"", shell=True)

def git_add():
    subprocess.call(f"git -C {git_path} add .", shell=True)

def push():
    for remote in remote_name:
        print(f"Pushing to remote {colorize('green')}{remote}{colorize('reset')}")
        print(f"{colorize('yellow')}")
        if argv.branch is None:
            subprocess.call(f"git -C {git_path} push {remote} {current_branch}", shell=True)
        else:
            subprocess.call(f"git -C {git_path} push {remote} {argv.branch}", shell=True)
        print(f"{colorize('reset')}")
        print(f"Pushed to {colorize('green')}{get_repo_http_url(remote)}{colorize('reset')}\n")
        print(f"{colorize('reset')}{'-'*15}{colorize('reset')}")

    

parser = argparse.ArgumentParser(description="Push to all git remotes with one command" )
parser.add_argument("-p", "--push", help="Push to all remotes", action="store_true")
parser.add_argument("-s", "--status", help="Show the status of all remotes", action="store_true")
parser.add_argument("-b", "--branch", help="Specify the branch to push to. (Default current branch)", type=str)
parser.add_argument("-l", "--list", help="List out remote / branch", type=str , choices=["r" , "remote", "b" , "branch"])
parser.add_argument("-c" , "--commit" , help="Commit all changes" , type=str , nargs="+" )
parser.add_argument("-cp" , "--commit_push" , help="Commit all changes and push to all remote" , type=str , nargs="+" )
parser.add_argument("-a" , "--all" , help="All. Add, Commit, Push" , type=str , nargs="+" )


argv = parser.parse_args( args=None if sys.argv[1:] else ['--help'])

remote_name = subprocess.check_output("git remote", shell=True).decode("utf-8").split("\n")
remote_name.pop() # remove the last empty element

git_path = subprocess.check_output("git rev-parse --show-toplevel", shell=True).decode("utf-8").strip()
git_path = git_path.replace(" ", "\ ")

repo_name = subprocess.check_output("basename -s .git `git config --get remote.origin.url`", shell=True).decode("utf-8").strip()

current_branch = subprocess.check_output("git rev-parse --abbrev-ref HEAD", shell=True).decode("utf-8").strip()
if argv.branch is not None:
    current_branch = argv.branch

if argv.status is True:
    print("Repo name: ", colorize("green") , repo_name , colorize("reset"))
    print("Current branch: ", colorize("green") , current_branch , colorize("reset"))
    print("Remotes: ", colorize("green") , remote_name , colorize("reset"))
    print("Git path: ", colorize("green") , git_path , colorize("reset"))
    print(f"{colorize('reset')}{'-'*15}")
    for remote in remote_name:
        print(f"Status of [{remote}]" , colorize("yellow") )
        subprocess.call(f"git -C {git_path} remote show {remote}", shell=True)
        print(f"{colorize('reset')}{'-'*15}")
    print("Changes: ", colorize("red"))
    subprocess.call(f"git -C {git_path} status | grep 'modified' ", shell=True)
    print(f"{colorize('reset')}")
    exit()

if argv.push is True:
    push()
    exit()

if argv.list is not None:
    if argv.list == "r" or argv.list == "remote":
        for remote in remote_name:
            print(remote)
    elif argv.list == "b" or argv.list == "branch":
        # list out all the branches
        subprocess.call(f"git -C {git_path} branch -a | cat", shell=True)

    exit()


if argv.commit is not None:
    commit(argv.commit[0])
    exit()

if argv.commit_push is not None:
    commit(argv.commit_push[0])
    push()
    exit()

if argv.all is not None:
    git_add()
    commit(argv.all[0])
    push()
    exit()