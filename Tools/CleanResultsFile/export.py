import os


pattern = r"\s+"
cpat = re.compile(pattern)
with os.scandir(".") as it:
    for entry in it:
        if (entry.name.startswith('clean_')) and entry.name.endswith(".txt"):
            with open(entry.path) as file:
            	results = []
            	sub_result = []
            	for line in file:
            		if line.startswith("# Size"):
            			if(len(sub_result)>0):
            				results.append(sub_result)
            			idx=0
            			sub_result=[]
            		elif idx>=0:
            			sub_result.append(line.strip().split()[1])


            print(results)