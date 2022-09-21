# put all .ipynb files in the current directory into a single .ipynb file called  f"{argv.name}.ipynb"
import json
import os
import argparse

parser = argparse.ArgumentParser(description="Put all .ipynb files in the current directory into a single .ipynb file called ipynb file")
parser.add_argument("-n", "--name", help="Name of the new .ipynb file", type=str, default= "all")
parser.add_argument("-r", "--recursive", help="Include all subdirectories", action="store_true")
parser.add_argument("-i", "--ignore", help="Ignore files", type=str, nargs="+")
argv = parser.parse_args()

pattern = ".ipynb"

def filter_files(file):
    # filter out files that are not .ipynb files
    if argv.ignore is not None:
        return file.endswith(pattern) and file not in argv.ignore and file != argv.name + pattern
    else:
        return file.endswith(pattern) and file != argv.name + pattern

all_files = []
if argv.recursive:
    # add all files to the list
    for root, dirs, files in os.walk(os.getcwd()):
        for file in files:
            if filter_files(file):
                all_files.append(os.path.join(root, file))
else:
    all_files = [ file for file in os.listdir ( os.getcwd () ) if filter_files(file)]

all_files.sort()
    
if len(all_files) == 0:
    print("No .ipynb file found")
    exit()

def get_all_cells(file):
    with open(file, "r") as f:
        data = json.load(f)
        try:
            return data["cells"]
        except:
            return [] # the file is empty

def create_new_ipynb_file(file):
    # create a new .ipynb file
    # the metadata is referenced from the file(argument)
    with open(file, "r") as f:
        data = json.load(f)
        metadata = data["metadata"]
        new_ipynb = {
            "cells": [],
            "metadata": metadata,
            "nbformat": 4,
            "nbformat_minor": 2
        }
        with open(f"{argv.name}.ipynb", "w") as f:
            json.dump(new_ipynb, f)

def create_markdown_cells(title):
    # create a markdown cell
    return {
        "cell_type": "markdown",
        "metadata": {},
        "source": [
            "# " + title.split("/")[-1].split(".")[0]
        ]
    }

def append_cells_to_all_ipynb_file(file):
    # append all the cells from the file(argument) to the f"{argv.name}.ipynb file
    all_cells = get_all_cells(file)
    with open(f"{argv.name}.ipynb", "r") as f:
        data = json.load(f)
        data["cells"].append(create_markdown_cells(file))
        data["cells"] += all_cells
        with open(f"{argv.name}.ipynb", "w") as f:
            json.dump(data, f, indent=4)

if not os.path.exists( f"{argv.name}.ipynb"):
    create_new_ipynb_file(all_files[0])
else:
    os.remove( f"{argv.name}.ipynb")
    create_new_ipynb_file(all_files[0])

for file in all_files:
    if file ==  f"{argv.name}.ipynb":
        continue
    print(f"Apend cells from {file} to {argv.name}.ipynb")
    append_cells_to_all_ipynb_file(file)

    