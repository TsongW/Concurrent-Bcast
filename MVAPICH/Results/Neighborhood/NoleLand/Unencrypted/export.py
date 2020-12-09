import os
import openpyxl

def write_to_spreadsheet(results, sheet_name, start_row):
	wb = openpyxl.load_workbook('../NS-Neighborhood_Allgather.xlsx')
	
	
	sheet = wb[sheet_name]
	# print(len(results), [len(x) for x in results], sheet_name, start_row)
	columns = ['B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L']
	for i in range(min([len(results), 11])):
		for j in range(len(results[i])):
			sheet[columns[i] + str(j + start_row)].value = results[i][j]
		

	wb.save('../NS-Neighborhood_Allgather.xlsx')


def read_file(path):
	with open(path) as file:
		results = []
		sub_result = []
		idx = -1
		for line in file:
			if line.startswith("Total"):
				idx = 0
				
			elif idx>=0:
				sub_result.append(float(line.strip().split()[1]))
				idx+=1

			if idx == 23:
				results.append(sub_result)
				sub_result = []
				idx = -1


	return results

if __name__ == '__main__':
	start_rows = {}
	start_rows['out_2_1'] = 5
	start_rows['out_c_2_1'] = 34
	start_rows['out_2_2'] = 63
	start_rows['out_c_2_2'] = 92
	start_rows['out_3_1'] = 122
	start_rows['out_c_3_1'] = 151
	
	

	sheet_name = input('enter Sheet name: ')

	with os.scandir(".") as it:
		for entry in it:
			if (entry.name.startswith('clean_')) and entry.name.endswith(".txt"):
				results = read_file(entry.path)

				write_to_spreadsheet(results, sheet_name, start_rows[entry.name[6:-4]])


