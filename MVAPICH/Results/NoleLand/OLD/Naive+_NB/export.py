import os
import openpyxl

def write_to_spreadsheet(results, sheet_name, start_row):
	wb = openpyxl.load_workbook('../Allgather-MVAPICH-NoleLand.xlsx')
	
	
	sheet = wb[sheet_name]

	columns = ['B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L']
	for i in range(len(results)):
		for j in range(len(results[i])):
			sheet[columns[i] + str(j + start_row)].value = results[i][j]
		

	wb.save('../Allgather-MVAPICH-NoleLand.xlsx')


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

			if idx == 21:
				results.append(sub_result)
				sub_result = []
				idx = -1


	return results

if __name__ == '__main__':
	start_rows = {}
	start_rows['out_2_32'] = 5
	start_rows['out_3_48'] = 33
	start_rows['out_4_20'] = 61
	start_rows['out_4_32'] = 89
	start_rows['out_4_36'] = 117
	start_rows['out_4_64'] = 145
	start_rows['out_cyclic_4_64'] = 173
	

	sheet_name = input('enter Sheet name: ')

	with os.scandir(".") as it:
		for entry in it:
			if (entry.name.startswith('clean_')) and entry.name.endswith(".txt"):
				results = read_file(entry.path)

				write_to_spreadsheet(results, sheet_name, start_rows[entry.name[6:-4]])


