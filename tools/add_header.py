#!/bin/python2.7
#
# add_header.py: This script is reponsible for adding headers to cpp and hpp
# files without a prexisting header. This script will not recurse without the
# -r switch
#
# TODO: add -i switch for manual check
#
# File created by : Corentin Gay
# File modified by : Corentin Gay
# File was created at : 14/09/2017
#

import sys
import os
import re
import argparse

header = """/*
 * File : sourcefilename
 *
 * File created by : Python
 * File modified by : Python
 * File was created at : 01/01/2042
 */"""

header_pattern = """/\*
 \* File : .*
 \*
 \* File created by : .*
 \* File modified by : .*
 \* File was created at : .*
 \*/"""

# Checks if the given source_file(as a buffer) contains the header
def file_has_header(source_file):
	global header_pattern
	match_obj =  re.match(header_pattern, source_file, re.M|re.I)
	return match_obj

# Checks if a filename represents a C++ source file
def is_source_file(path):
	pattern = ".*.[hc]pp"
	match_obj =  re.match(pattern, path, re.M|re.I)
	if match_obj:
		print "Source file is:", match_obj.group()
	else:
		print "No match"
	return match_obj

def is_dir(path):
	return os.path.isdir(path)

def is_usable(path):
	return os.access(path, os.W_OK|os.R_OK)

def check_source_file(arg):
	return is_source_file(arg) and not(is_dir(arg)) and is_usable(arg)

EDITOR = os.environ["VISUAL"]

# Create a parser object that has a -r option
def set_args():
	parser = argparse.ArgumentParser(description="""Add header to a file
					 that does not possess that header""")
	parser.add_argument("-r", "--recurse", action="store_true",
			help="enables recursion into directories")

	parser.add_argument('files', metavar='files', action='store',
	nargs='+', help='the list of files/directories on which to run the script')

	return parser

def is_recursive(args):
	return args.recurse

# Apply the script to a given usable source file
def apply_header_file(arg):
	global EDITOR
	f = open(arg, 'r+')
	lines = f.readlines()
	buf = ''.join(str(x) for x in lines)
	if (file_has_header(buf)):
		print "File has header"
	else:
		print "File doesnt have header"
		f.seek(0,0)
		f.write(header + '\n\n' + buf)
		print "Wrote header template to file:", arg
		f.close()
		os.system(EDITOR+" "+arg)
	f.close()

# Try to apply the script to all files in a directory recursively
def apply_header_dir(arg):
#	os.chdir(arg)
	print "arg is", arg

	for root, dirs, files in os.walk(arg, topdown=False):
		for f in files:
			name = os.path.join(root, f)
			print"File:", name
			if (check_source_file(name)):
				apply_header_file(name)

# Traverse the given files passed as arguments
def traverse_arguments(parser, argv):
	for arg in argv:
		if (check_source_file(arg)):
			apply_header_file(arg)
		elif (is_dir(arg) and is_recursive(args)):
			apply_header_dir(arg)
		elif (is_dir(arg) and not(is_recursive(args))):
			print "Will not recurse into directory without -r switch."

parser = set_args()
args = parser.parse_args()

traverse_arguments(parser, args.files)

