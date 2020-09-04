import os
import openpyxl

def write_to_spreadsheet(results, sheet_name, start_row):
	wb = openpyxl.load_workbook('../BWs.xlsx')
	
	
	sheet = wb[sheet_name]
	# print(len(results), [len(x) for x in results], sheet_name, start_row)
	columns = ['B', 'C', 'D', 'E', 'F']
	for i in range(min([len(results), 6])):
		for j in range(len(results[i])):
			sheet[columns[i] + str(j + start_row)].value = results[i][j]
		

	wb.save('../BWs.xlsx')


def read_file(path):
	with open(path) as file:
		results = []
		sub_result = []
		idx = -1
		for line in file:
			if line.startswith("# Size"):
				
				idx = 0
				
			elif idx>=0:
				sub_result.append(float(line.strip().split()[1]))
				idx+=1

			if idx == 14:
				results.append(sub_result)
				sub_result = []
				idx = -1


	return results

if __name__ == '__main__':
	start_rows = {}
	start_rows['bw_1_2'] = 5
	start_rows['bw_1_4'] = 27
	start_rows['bw_1_8'] = 48
	start_rows['bw_1_16'] = 69
	start_rows['bw_2_2'] = 5
	start_rows['bw_2_4'] = 27
	start_rows['bw_2_8'] = 48
	start_rows['bw_2_16'] = 69
	start_rows['bw_2_32'] = 90
	

	with os.scandir(".") as it:
		for entry in it:
			if (entry.name.startswith('clean_')) and entry.name.endswith(".txt"):
				results = read_file(entry.path)
				if entry.name.startswith('clean_bw_1'):
					sheet_name = 'NS-Intra'
				else:
					sheet_name = 'NS-Inter'
				write_to_spreadsheet(results, sheet_name, start_rows[entry.name[6:-4]])


