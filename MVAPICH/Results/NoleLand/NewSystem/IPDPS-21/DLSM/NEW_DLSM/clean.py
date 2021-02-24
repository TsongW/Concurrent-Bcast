import os
import re


pattern = r"\s+"
cpat = re.compile(pattern)
with os.scandir(".") as it:
    for entry in it:
        if (not entry.name.startswith('clean_')) and entry.name.endswith(".txt") and entry.is_file():
            with open(entry.path) as file:
            	out = open('clean_'+entry.name, 'w')
            	for line in file:
            		m = cpat.search(line)
            		if m is not None:
            			start, end = m.span()
            			newline = line[:start+1]+line[end:]
            			out.write(newline)
            	out.close()